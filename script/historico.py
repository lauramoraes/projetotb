#!/usr/bin/env python

import cgi;
import cgitb; cgitb.enable(); #Remove after debuging.
import xml.dom.minidom;
import fcntl;
import shutil;
import os;
from datetime import datetime, date;

import functions;

xmlEncoding = 'ISO-8859-1';

motivoEditForm = "histMotivo";
versionHist = "versao";
dateHistorico = "data";
rootElement = "pacientes";
rootChild = "paciente";
generalNumber = "numeroGeral";

#Getting the HTML form input data.
form = cgi.FieldStorage()

value = form.getvalue("form")
if((value == "consultaMedica") or (value == "followUp") or (value == "triagem")):
    xmlEncoding = 'utf-8'

#Pegando ID (na triagem o campo de ID se chama antigoNumeroGeral)
if value == "triagem":
  pid = "antigoNumeroGeral";
else:
  pid = "pid";

#Creating the XML document that will hold the new data.
doc = xml.dom.minidom.Document();
data = doc.createElement(form['form'].value);
for k in form.keys():
  if k in ['form', pid]: continue;
  valueList = form.getlist(k)
  for value in valueList:
      val = doc.createElement(k);
      val.appendChild(doc.createTextNode(unicode(value, xmlEncoding)));
      data.appendChild(val);

#Opening the xml file and locking it to prevent access from other processes.
xmlData = open(functions.PATIENTS_FILE_NAME, 'r+');
fcntl.flock(xmlData, fcntl.LOCK_EX);

#Opening the file used for backup and locking it.
bckData = open(functions.PATIENTS_FILE_NAME + '~', 'w');
fcntl.flock(bckData, fcntl.LOCK_EX);

#Generating the backup.
shutil.copyfileobj(xmlData, bckData);
bckData.close(); #Realeasing the backup file (unlock).

#Parsing the XML file
xmlData.seek(0); #Going to the beginning of the file
dom = xml.dom.minidom.parse(xmlData);

#Pega motivo e retira do documento, para que nao entre no xml original
if len(data.getElementsByTagName(motivoEditForm)) != 0:
  histMotivo = data.getElementsByTagName(motivoEditForm)[0];
  data.removeChild(data.getElementsByTagName(motivoEditForm)[0]);
else:
  histMotivo = None;

#Verifica nome do avaliador (no followUp, o campo se chama avaliadorMedicoFollowUp)
if form['form'].value == "followUp":
  avaliador = "avaliadorMedicoFollowUp";
else:
  avaliador = "avaliador";

#Pega avaliador que fez a modificacao
if len(data.getElementsByTagName(avaliador)) != 0:
  histUsuario = data.getElementsByTagName(avaliador)[0];
else:
  histUsuario = None;

#Retrieving the correct user.
patient = functions.getPatientInfo(dom, form[pid].value);

#Checking whether the form already exists. If so, we remove it first.
#Salva formulario antigo para ser usado no historico
if len(patient.getElementsByTagName(form['form'].value)) != 0:
  formularioOld = patient.getElementsByTagName(form['form'].value)[0];
  patient.removeChild(patient.getElementsByTagName(form['form'].value)[0]);

#Garante que o formulario de triagem seja o primeiro filho de <paciente>
if form['form'].value == "triagem":
  patient.insertBefore(data,patient.firstChild);
else:
  patient.appendChild(data);

#Saving the new data to the XML file.
xmlData.seek(0); #Going to the beginning of the file.
xmlData.write(dom.toxml(encoding = xmlEncoding));
xmlData.truncate();
xmlData.close(); #Releasing the file (calls also unlock).

functions.autoBackup()

#Se o arquivo de historico nao existir, cria documento novo.
if (os.access(functions.HIST_FILE_NAME,os.F_OK) == False):
  histData = open(functions.HIST_FILE_NAME, 'w');
  fcntl.flock(histData, fcntl.LOCK_EX);
  docHist = xml.dom.minidom.Document();
  pacientes = docHist.createElement(rootElement);
  docHist.appendChild(pacientes);
  existe = 0;
#Se o arquivo existir, procura se o paciente existe
else:
  histData = open(functions.HIST_FILE_NAME, 'r+');
  fcntl.flock(histData, fcntl.LOCK_EX);
  histData.seek(0);
  docHist = xml.dom.minidom.parse(histData);
  patientHist = functions.getPatientInfoHistorico(docHist, form[pid].value);
  pacientes = docHist.getElementsByTagName(rootElement)[0];
  if (patientHist == None):
    existe = 0;
  else:
    existe = 1;

#formando a tag formInfo
formInfo = form['form'].value + 'Info';

#Se paciente existir, verifica se ja existe historico do formulario
if (existe != 0):
  formulario = 0;
  listafilho = patientHist.childNodes;
  for filho in listafilho:
    if (filho.nodeName == formInfo):
      formulario = 1;
#Se paciente nao existir, cria historico do formulario
else:
  patientHist = docHist.createElement(rootChild);
  numeroGeral = docHist.createElement(generalNumber);
#Caso seja o formulario de triagem, e preciso procurar as informacoes pelo numero geral antigo porem guarda-las no novo (caso o numero geral mude)
  if (form['form'].value == "triagem"):
    pacienteID = "numeroGeral";
  else:
    pacienteID = pid;
  numeroGeral.appendChild(docHist.createTextNode(unicode(form[pacienteID].value, xmlEncoding)));
  patientHist.appendChild(numeroGeral);
  pacientes.appendChild(patientHist);
  formulario = 0;

#Se historico do formulario nao existir, cria um novo
if (formulario == 0):
  histInfo = docHist.createElement(formInfo);
  patientHist.appendChild(histInfo);
#Se historico do formulario existir, recupera os dados do formulario
else:
  histInfo = patientHist.getElementsByTagName(formInfo)[0];

#Cria tag para a versao e data da modificacao do formulario
version = docHist.createElement(versionHist);
dateHist = docHist.createElement(dateHistorico);
dt = datetime.now();
dateHist.appendChild(docHist.createTextNode(unicode(dt.strftime("%d/%m/%y %H:%M:%S"), xmlEncoding)));
version.appendChild(dateHist);

#Coloca o formulario, avaliador e motivo dentro da versao do historico
version.appendChild(formularioOld);
if histUsuario != None:
  version.appendChild(histUsuario);
if histMotivo != None:
  version.appendChild(histMotivo);

#Coloca a versao dentro do historico
histInfo.appendChild(version);

#Grava arquivo do historico
histData.seek(0);
histData.write(docHist.toxml(encoding = xmlEncoding));
histData.close();

returnPage = "busca.cgi?uid=%s" % functions.fmt2GetMethod(os.environ["REMOTE_USER"]);
if functions.isMobile(os.environ): returnPage = "palm.psp";

print "Content-Type: text/html\n\n"     # HTML is following

htmlPage = """
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html" charset="ISO-8859-1" />
  <title>Projeto Neural TB</title>
  <style type="text/css">
"""

htmlPage += open(functions.PROJECT_PATH + "css/search_palm.css", "r").read();

htmlPage += """
  </style>
</head>

<body>
"""

htmlPage += 'Formul&aacute;rio salvo com sucesso! Clique <a href="%s" target=\"_parent\">aqui</a> para retornar &agrave; p&aacute;gina de busca.' % returnPage;

htmlPage += """
</body>
</html>
""";

print htmlPage;

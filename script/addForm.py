#!/usr/bin/env python

import cgi;
import cgitb; cgitb.enable(); #Remove after debuging.
import xml.dom.minidom;
import fcntl;
import shutil;
import os;

import functions;

xmlEncoding = 'ISO-8859-1';

#Getting the HTML form input data.
form = cgi.FieldStorage()

value = form.getvalue("form")
if((value == "consultaMedica") or (value == "followUp") or (value == "triagem")):
    xmlEncoding = 'utf-8'

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

#Retrieving the correct user.
patient = functions.getPatientInfo(dom, form[pid].value);

#Checking whether the form already exists. If so, we remove it first.
if len(patient.getElementsByTagName(form['form'].value)) != 0:
  patient.removeChild(patient.getElementsByTagName(form['form'].value)[0]);
patient.appendChild(data);

#Saving the new data to the XML file.
xmlData.seek(0); #Going to the beginning of the file.
xmlData.write(dom.toxml(encoding = xmlEncoding));
xmlData.truncate();
xmlData.close(); #Releasing the file (calls also unlock).

functions.autoBackup()

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

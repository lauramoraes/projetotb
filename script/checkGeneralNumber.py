#!/usr/bin/env python

import cgi;
import xml.dom.minidom;
import fcntl;

import functions;

#Getting the HTML form input data.
form = cgi.FieldStorage()

numeroGeral = form["pid"].value

#Opening the xml file and locking it to prevent access from other processes.
xmlData = open(functions.PATIENTS_FILE_NAME, 'r+');
fcntl.flock(xmlData, fcntl.LOCK_EX);

#Parsing the XML file
xmlData.seek(0); #Going to the beginning of the file
dom = xml.dom.minidom.parse(xmlData);

#Retrieving the correct user.
result = functions.getPatientInfo(dom, numeroGeral);

#Closing the xml file
xmlData.close()

print "Content-Type: text/html\n\n"     # HTML is following

if result == None:
# Numero geral valido
    print '0'

else:
# Numero geral jah existente
    print '1'
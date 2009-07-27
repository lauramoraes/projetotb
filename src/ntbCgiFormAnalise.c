/*
	Universidade Federal do Rio de Janeiro
	Escola Politecnica
	Departamento de Engenharia Eletronica e de Computacao
	
	Laboratorio de Processamento de Sinais
	Projeto Neural TB
	Autor: Igor Bragança

	$Author$
	$Date$
	$Log$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "cgi.h"

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

int main (int argc, char **argv)
{
	char *username;
	
	cgi_init();
	cgi_process_form();
	
	if(!(username= getenv("REMOTE_USER"))) //verifica se string lida é null
	{
		printf("Content-type: text/html\n\n");
		printf("<html>\n");
		printf("<head>\n");
		printf("<title>Resultado</title>\n");
		printf("</head>\n");
		printf("<body>\n");
		printf("Erro ao verificar o usuário.");
		printf("</body>\n");
		printf("</html>\n");
		exit(0);
	}

	cgi_init_headers();

/************** pagina html analise ********************/
printf("<html>\n");
printf("	<head>\n");
printf("		<title>Neural TB - Analise</title>\n");
printf("		<link rel=\"stylesheet\" type=\"text/css\" href=\"css/main.css\" />\n");
printf("		<link rel=\"stylesheet\" type=\"text/css\" href=\"css/menu.css\" />\n");
printf("		<link rel=\"stylesheet\" type=\"text/css\" href=\"css/form.css\" />\n");
printf("		<script charset=\"ISO-8859-1\" language=javascript src=\"js/funcoes.js\"></script>\n");
printf("\n");
printf("	</head>\n");
printf("	<body>\n");
printf("\n");

showMenu("analise",username);

printf("\n");
printf("		<form action=\"analise.cgi\" method=\"get\">\n");
printf("		<br></br>\n");
printf("		<center>\n");
printf("			<table style=\"width:230\">\n");
printf("				<tr>\n");
printf("					<td colspan=\"2\" align=\"left\" style=\"color: white; font-weight: bold;\">\n");
printf("					Sinais e Sintomas\n");
printf("					</td>\n");
printf("				</tr>\n");
printf("				<tr>\n");
printf("					<td>\n");
printf("					<select name=\"campo\">\n");
printf("							<option value=\"tosse\" selected=\"selected\">Tosse</option>\n");
printf("							<option value=\"expectoracao\">Expectora&ccedil;&atilde;o</option>\n");
printf("							<option value=\"hemoptoico\">Hemopt&oacute;ico</option>\n");
printf("							<option value=\"hemoptise\">Hemoptise</option>\n");
printf("							<option value=\"sudorese\">Sudorese Noturna</option>\n");
printf("							<option value=\"febre\">Febre</option>\n");
printf("							<option value=\"dispneia\">Dispn&eacute;ia</option>\n");
printf("							<option value=\"perdaApetite\">Perda de apetite</option>\n");
printf("							<option value=\"dorToracica\">Dor Tor&aacute;cica</option>\n");
printf("						</select>\n");
printf("					</td>\n");
printf("					<td>\n");
printf("						<input type=\"submit\" value=\"Analisar\">\n");
printf("					</td>\n");
printf("				</tr>\n");
printf("			</table>\n");
printf("		</center>\n");
printf("		</form>\n");
printf("	</body>\n");
printf("</html>\n");


/*****************************************************/

	cgi_end();
	
	return 0;
}

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

/* $RCSfile$ */
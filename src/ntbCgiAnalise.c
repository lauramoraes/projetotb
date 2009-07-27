/*
	Universidade Federal do Rio de Janeiro
	Escola Politecnica
	Departamento de Engenharia Eletronica e de Computacao
	
	Laboratorio de Processamento de Sinais
	Projeto Neural TB (Guadalupe)
	Autor: Igor Cunha Braganca

	$Author$
	$Date$
	$Log$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

#include "cgi.h"
#include "ntbError.h"
#include "ntbConfig.h"
#include "ntbConsts.h"
#include "ntbTypes.h"
#include "ntbFunctions.h"
#include "functions.h"

#define XML_FILE_PATH "./xml/pacientesGuadalupe.xml"

void usualFreeMemory (xmlDocPtr doc, listaAnalise *primeiro)
{
	listaAnalise *aux;
	if(primeiro != NULL)
		for(aux = primeiro; aux != NULL; aux = primeiro)
		{
			primeiro = primeiro->proximo;
			free(aux);
		}

	cgi_end();
	if (doc)
		xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
}

void printSuccess (char *username)
{
	cgi_init_headers();
	
	printf ("<html>\n");
	printf ("\t<head>\n");
	printf ("\t\t<title>Usu&aacute;rio Editado</title>\n");
	printf ("\t\t<meta http-equiv=\"refresh\" content=\"2; URL=busca.cgi?uid=%s\" />\n",username);
	printf ("\t</head>\n");
	printf ("\t</body>\n");
	printf ("<span style=\"background-color:green; color: white; font-family: Verdana, Arial; font-size:15pt; padding: 5px\">");
	printf ("Formul&aacute;rio editado com sucesso. Aguarde...</span>");
	printf ("\t</body>\n");
	printf ("</html>");
}

void printError (char *msg)
{
	cgi_init_headers();
	
	printf ("<html><head><title>Erro</title></head><body><h2>%s</h2></body></html>", msg);
}

int main (void)
{
	listaAnalise *primeiro, *aux;
	char *username, *campo, campoAux[128+1];
	FILE *document;
	boolean found_field = false;
	/*
	 * 0 - Sim
	 * 1 - Nao
	 * 2 - Ignorado
	 * 3 - Total
	 */
	double qtd[4];

	qtd[0] = qtd[1] = qtd[2] = qtd[3] = 0;

	/* libxml2 declarations */
	xmlDocPtr doc;
	xmlNodePtr root_element, cur_node, aux_node;
	
	/*
	 * this initialize the library and check potential ABI mismatches
	 * between the version it was compiled for and the actual shared
	 * library used.
	 */
	LIBXML_TEST_VERSION
	
/******************************************************************************
 *				READ CONTENT STRING FROM SERVER.		*
 *				PROCESS DATA.							*
 *				CREATE A LINKED LIST.					*
 ******************************************************************************/

	cgi_init();
	cgi_process_form();
	campo = cgi_param("campo");
	strcpy(campoAux,campo);
	primeiro = malloc(sizeof(listaAnalise));
	strcpy(primeiro->campo, campoAux);
	primeiro->proximo = NULL;

	/*if(!(username= getenv("REMOTE_USER"))) //verifica se string lida é null
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
		cgi_end();
		exit(0);
	}*/

	if(strlen(primeiro->campo) == 0)
	{
		printError("Erro ao enviar o campo para ser analisado");
		cgi_end();
		exit(0);
	}

/******************************************************************************
 *            OPENING AND PARSING AN XML FILE TO A TREE                       *
 ******************************************************************************/

	document = fopen(XML_FILE_PATH, "r");
	
	if (document == NULL)
	{
		printError("O arquivo de pacientes n&atilde;o pode ser aberto");
		cgi_end();
		exit(0);
	}

	if(flock(fileno(document), LOCK_EX)) {
		printError("Erro ao trancar o arquivo");
		fclose(document);
		cgi_end();
		exit(0);
	}

	doc = xmlReadFd(fileno(document), XML_FILE_PATH, NULL, XML_PARSE_NOBLANKS);
	if (doc == NULL)
	{
		printError("Failed to parse doc");
		usualFreeMemory(NULL, primeiro);
		flock(fileno(document), LOCK_EX);
		fclose(document);
		exit(0);
	}
	
	root_element = xmlDocGetRootElement(doc);
	
/******************************************************************************
 *				Procunrando as tags com os nomes desejados					  *
 ******************************************************************************/

	aux = primeiro;
	cur_node = root_element->children;

	while(aux != NULL)
	{
		while(cur_node != NULL)
		{
			aux_node = cur_node->children;//triagem
/*
			while((aux_node != NULL) && ((xmlStrEqual(aux_node->name, BAD_CAST "triagem")) == 0))
				aux_node = aux_node->next;

			if((xmlStrEqual(aux_node->name, BAD_CAST "triagem")) == 0)
			{
				printError("Erro ao tentar encontrar a tag triagem");
				usualFreeMemory(doc, primeiro);
				flock(fileno(document), LOCK_EX);
				fclose(document);
				exit(0);
			}
*/
			aux_node = aux_node->children;
			found_field = false;
			while((found_field == false) && (aux_node != NULL))
			{
				if((xmlStrEqual(aux_node->name, BAD_CAST aux->campo)) == 1)
				{
					if(aux_node->children != NULL)
					{
						if((xmlStrEqual(aux_node->children->content, BAD_CAST "sim")) == 1)
							qtd[0] ++;
						if((xmlStrEqual(aux_node->children->content, BAD_CAST "nao")) == 1)
							qtd[1] ++;
						if((xmlStrEqual(aux_node->children->content, BAD_CAST "ignorado")) == 1)
							qtd[2] ++;
					}
					qtd[3]++;
					found_field = true;
				}

				aux_node = aux_node->next;
			}

			cur_node = cur_node->next;
		}
		
		aux = aux->proximo;
	}

cgi_init_headers();
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
printf("							<option value=\"tosse\">Tosse</option>\n");
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
printf("			<br></br>\n");
printf("			<table style=\"width:400; font-size:11pt\" border=0>\n");
printf("				<tr style=\"background-color:#FFFF99\">\n");
printf("					<td style=\"align:center\">Sintoma</td>\n");
printf("					<td style=\"align:center\">Sim</td>\n");
printf("					<td style=\"align:center\">N&atilde;o</td>\n");
printf("					<td style=\"align:center\">Ignorado</td>\n");
printf("				</tr>\n");
printf("				<tr style=\"background-color: rgb(192, 217, 217);\">\n");
printf("					<td style=\"align:center; width:40%%\">%s</td>\n",campo);
printf("					<td style=\"align:center; width:20%%\">%.2lf%%</td>\n",((qtd[0]/qtd[3])*100));
printf("					<td style=\"align:center; width:20%%\">%.2lf%%</td>\n",((qtd[1]/qtd[3])*100));
printf("					<td style=\"align:center; width:20%%\">%.2lf%%</td>\n",((qtd[2]/qtd[3])*100));
printf("				</tr>\n");
printf("			</table>\n");
printf("		</center>\n");
printf("		</form>\n");
printf("	</body>\n");
printf("</html>\n");

	usualFreeMemory(doc, primeiro);
	flock(fileno(document), LOCK_EX);
	fclose(document);
	return 0;
}
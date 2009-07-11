/*
 * Igor Cunha Bragança
 * Laboratório de Processamento de Sinais
 * Universidade Federal do Rio de Janeiro
 */
 
/*
gcc -Wall -c calculoRedesNeurais.c -I/usr/include/libxml2
gcc -Wall -o calculoRedesNeurais.cgi calculoRedesNeurais.c nnet.c nnet2.c geraGraficoDeGrupo2.c -I/usr/include/libxml2 -L/usr/lib -L../src/libs -lxml2 -lgd -lcgi
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
#include "tiposModif.h"
#include "consts.h"
#include "nnet.h"
#include "nnet2.h"
#include "geraGraficoDeGrupo.h"

#define XML_FILE_PATH "xml/pacientesGuadalupe.xml"

void usualFreeMemory (xmlDocPtr);
void usualFreeMemory (xmlDocPtr doc)
{
	if (doc)
		xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
}

void printError (char *);
void printError (char *msg)
{
	cgi_init_headers();
	
	printf ("<html><head><title>Erro</title></head><body><h2>%s</h2></body></html>", msg);
}

/*
 * Esta função procura no xml o paciente com o numero geral desejado
 * Ela pega os campos necessários para o calculo na redes nerais, que são:
 * idade; tosse; hemoptoico; sudorese; febre; emagrecimento; dispneia; anorexia; fuma_atualmente; tb_extrapulmonar; internacao_hospitalar; sida;
 * E converte os falores destes campos para -1.0;0.0;1.0 de acordo com seu valor origianl
 * É devovido um ponterio para o primeiro elemento de uma lista encadeada da estrutura chainType
 */
chainType_2 *converterParaCalculoRedesNeurais (char *);
chainType_2 *converterParaCalculoRedesNeurais (char *pid)
{
	boolean found_patient;
	FILE *document;
	chainType_2 *aux, *other, *first;
	short unsigned indice;

	LIBXML_TEST_VERSION

	/* libxml2 declarations */
	xmlDocPtr doc;
	xmlNodePtr root_element, cur_node, old_patient;

	if(!(document = fopen(XML_FILE_PATH, "r+")))
		return NULL;

	if(flock(fileno(document), LOCK_EX))
	{
       	fclose(document);
        return NULL;
    }

	if(!(doc = xmlReadFd(fileno(document), XML_FILE_PATH, NULL, XML_PARSE_NOBLANKS)))
	{
		usualFreeMemory(NULL);
		flock(fileno(document), LOCK_EX);
		fclose(document);
		return NULL;
	}
	
	root_element = xmlDocGetRootElement(doc);

/******************************************************************************
 *           Procurando paciente pelo numero geral                            *
 ******************************************************************************/

	cur_node = root_element->children;	/* Get the node <paciente> if file isn't empty */
	if (!cur_node) //test!!!! printf!! pode-se tb na remocao exigir a remocao do arquivo se o paciente excluido for o unico do arquivo
		found_patient = false;
	
	else
	{
		/* looping through patients looking for the right patient */
		
		for (found_patient = false; ((!found_patient) && (cur_node)); cur_node = cur_node->next)
		{
			cur_node = cur_node->children; /* <triagem> */
			cur_node = cur_node->children; /* <numeroGeral> ? */
			
			while ((!xmlStrEqual(cur_node->name, BAD_CAST "numeroGeral")) && (cur_node))
				cur_node = cur_node->next;
			
			if (xmlStrEqual(cur_node->name, BAD_CAST "numeroGeral"))
			{
				if (xmlStrEqual(cur_node->children->content, BAD_CAST pid))
				{
					found_patient = true;
					old_patient = cur_node->parent; /*old_paciente recebe o noh <triagem> do paciente que possui o numeroGeral procurado */
				}
				else
				{
					cur_node = cur_node->parent; /* <triagem> */
					cur_node = cur_node->parent; /* <paciente> */
				}
			}
			else
			{
				usualFreeMemory(doc);
				flock(fileno(document), LOCK_EX);
				fclose(document);
				return NULL;
			}
		}
	}

/******************************************************************************
 *            Checando se paiente foi encontrado		*
 *            Se true continuo      					*
 ******************************************************************************/

	if(!found_patient)
	{
		usualFreeMemory(doc);
		flock(fileno(document), LOCK_EX);
		fclose(document);
		return NULL;
	}
	
	//old_patient esta em triagem do paciente com o numero geral
/******************************************************************************
 *           Criando variavel que será mandada para a redes neural            *
 ******************************************************************************/
	root_element = old_patient;
	old_patient = old_patient->children;//nivel das informacoes de triagem
	
	first = NULL;
	
	while((old_patient != NULL) && (indice < 12))
	{
		if((xmlStrEqual(old_patient->name, BAD_CAST "idade")) || (xmlStrEqual(old_patient->name, BAD_CAST "tosse")) || (xmlStrEqual(old_patient->name, BAD_CAST "hemoptoico")) || (xmlStrEqual(old_patient->name, BAD_CAST "sudorese")) || (xmlStrEqual(old_patient->name, BAD_CAST "febre")) || (xmlStrEqual(old_patient->name, BAD_CAST "emagrecimento")) || (xmlStrEqual(old_patient->name, BAD_CAST "dispneia")) || (xmlStrEqual(old_patient->name, BAD_CAST "anorexia")) || (xmlStrEqual(old_patient->name, BAD_CAST "fuma_atualmente")) || (xmlStrEqual(old_patient->name, BAD_CAST "tb_extrapulmonar")) || (xmlStrEqual(old_patient->name, BAD_CAST "internado")) || (xmlStrEqual(old_patient->name, BAD_CAST "sida")))
		{
			if((other = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
				return NULL;
			
			if(!(strcmp((char *)old_patient->name,"internado")))
				strcpy(other->attribute,"internacao_hospitalar");
			else
				strcpy(other->attribute, (char *)old_patient->name);
			
			strcpy(other->value, (char *)old_patient->children->content);
			
			if(!(strcmp(other->value,"sim")))
				other->entry = 1.0;
			if(!(strcmp(other->value,"nao")))
				other->entry = -1.0;
			if(!(strcmp(other->value,"ignorado")))
				other->entry = 0.0;
			
			other->next = NULL;
			
			if(first == NULL)
				first = other;
			else
				aux->next = other;
			
			aux = other;
			indice ++;
		}
	
		old_patient = old_patient->next;
	}
	
	/* Esta parte eh temporaria enquanto falta definocoes para a integracao */
	if((other = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;
	strcpy(other->attribute,"emagrecimento");
	strcpy(other->value,"ignorado");
	other->entry = 0.0;
	other->next = NULL;
	aux->next = other;
	aux = other;
	
	if((other = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;
	strcpy(other->attribute,"anorexia");
	strcpy(other->value,"ignorado");
	other->entry = 0.0;
	other->next = NULL;
	aux->next = other;
	aux = other;
	
	if((other = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;
	strcpy(other->attribute,"fuma_atualmente");
	strcpy(other->value,"ignorado");
	other->entry = 0.0;
	other->next = NULL;
	aux->next = other;
	aux = other;
	
	if((other = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;
	strcpy(other->attribute,"tb_extrapulmonar");
	strcpy(other->value,"ignorado");
	other->entry = 0.0;
	other->next = NULL;
	aux->next = other;
	aux = other;
	
	if((other = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;
	strcpy(other->attribute,"sida");
	strcpy(other->value,"ignorado");
	other->entry = 0.0;
	other->next = NULL;
	aux->next = other;
	aux = other;
	/* ******************************************************************** */

	usualFreeMemory(doc);
	flock(fileno(document), LOCK_EX);
	fclose(document);

	return first;
}

int main (void)
{
	char *pid;
	chainType_2 *aux_2, *first_2;
	chainType *aux, *first, *other;
	double response,raioOriginal;
	int grupo;

	cgi_init();
	cgi_process_form();
	if(!(pid = cgi_param("pid")))
	{
		printError("Erro obtendo numero geral.");
		cgi_end();
		exit(0);
	}

	/******************************************************** 
	 *      Pegando os dados necessario do arquivo xml      *
	 ********************************************************/
	if(!(first_2 = converterParaCalculoRedesNeurais (pid)))
	{
		printError("Erro convertendo os dados para a entrada da Rede Neural.");
		cgi_end();
		exit(0);
	}

	/******************************************************** 
	 * Copiando os dados para o tipo que a rede neural pede *
	 ********************************************************/
	aux_2 = first_2;
	first = NULL;
	while(aux_2 != NULL)
	{
		if((other = (chainType*)malloc(sizeof(chainType))) == NULL)
			exit(0);
		other->attribute = aux_2->attribute;
		other->value = aux_2->value;
		other->entry = aux_2->entry;
		other->next = NULL;
		
		if(first == NULL)
			first = other;
		else
			aux->next = other;
			
		aux = other;
		
		aux_2 = aux_2->next;
	}

	/****************************************************** 
	 *     Utilizando as funções da rede neural           *
	 ******************************************************/
	aux = first;
	if((nnet(aux, &response)))
	{
		printError("Erro utilizando nnet.");
		cgi_end();
		exit(0);
	}
//	printf("- %f -\n",response);

	aux = first;
	if((nnet2(aux, &grupo, &raioOriginal)))
	{
		printError("Erro utilizando nnet2.");
		cgi_end();
		exit(0);
	}
//	printf("- %i - %f -\n",grupo,raioOriginal);

	aux = first;
	geraGrafico(grupo, raioOriginal, response, pid, aux_2);


	/****************************************************** 
	 *               Liberando a Memória                  *
	 ******************************************************/
	aux = first;
	while(aux != NULL)
	{
//		printf("%s - %s - %f\n",aux->attribute,aux->value,aux->entry);
		first = aux;
		aux = aux->next;
		free(first);
	}

	aux_2 = first_2;
	while(aux_2 != NULL)
	{
//		printf("%s - %s - %f\n",aux_2->attribute,aux_2->value,aux_2->entry);
		first_2 = aux_2;
		aux_2 = aux_2->next;
		free(first_2);
	}


	cgi_end();
	
	return 0;
}

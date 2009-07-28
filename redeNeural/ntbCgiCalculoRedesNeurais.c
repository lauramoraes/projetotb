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
#include "ntbFunctions.h"

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
 * FUNCAO RESPONSAVEL POR CRIAR/ADICIONAR UM TERMO A UMA LISTA ENCADEADA DO TIPO "chainType_2"
 */
void adicionarNaListaEncadeada(chainType_2 *, xmlNodePtr, char *, char *);
void adicionarNaListaEncadeada(chainType_2 *first, xmlNodePtr noPai, char *tag, char *nameAtribute)
{
	if(tag == NULL)
		return;

	if(nameAtribute == NULL)
		return;

	chainType_2 aux, new;

	if((new = malloc(sizeof(chainType_2))) == NULL)
		return;

	if(first == NULL)
	{
		first = new;
	}
	else
	{
		for(aux = first; aux->next != NULL; aux = aux->next);

		aux->next = new;
	}

	strcpy(new->attribute, nameAtribute);
	strcpy(new->value, pegaValorDaTag(noPai, tag));

	if(!(strcmp(new->value,"sim")))
		new->entry =  1.0;
	if(!(strcmp(new->value,"nao")))
		new->entry = -1.0;
	if(!(strcmp(new->value,"ignorado")))
		new->entry =  0.0;

	new->next = NULL;
}

/*
 * Esta função procura no xml o paciente com o numero geral desejado
 * Ela pega os campos necessários para o calculo na redes nerais, que são:
 * idade; tosse; hemoptoico; sudorese; febre; emagrecimento; dispneia; anorexia; fuma_atualmente; tb_extrapulmonar; internacao_hospitalar; sida;
 * E converte os falores destes campos para -1.0;0.0;1.0 de acordo com seu valor origianl
 * É devovido um ponterio para o primeiro elemento de uma lista encadeada da estrutura chainType
 */
chainType_2 *converterParaCalculoRedesNeurais(char *);
chainType_2 *converterParaCalculoRedesNeurais(char *pid)
{
	FILE *document;
	chainType_2 *first, *aux, *new;

	LIBXML_TEST_VERSION

	xmlDocPtr doc;
	xmlNodePtr noPaciente, noTriagem;

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

	if((noPaciente = pegaPacientePorNumeroGeral(doc, pid)) == NULL)
	{
		usualFreeMemory(NULL);
		flock(fileno(document), LOCK_EX);
		fclose(document);
		return NULL;
	}

	if((noTriagem = pegarFilhoPorNome(noPaciete, "triagem")) == NULL)
	{
		usualFreeMemory(NULL);
		flock(fileno(document), LOCK_EX);
		fclose(document);
		return NULL;
	}

/******************************************************************************
 *           Criando variavel que será mandada para a redes neural            *
 ******************************************************************************/

	first = NULL;

	adicionarNaListaEncadeada(first, noTriagem, "idade", "idade");

	adicionarNaListaEncadeada(first, noTriagem, "tosse", "tosse");

	adicionarNaListaEncadeada(first, noTriagem, "hemoptoico", "hemoptoico");

	adicionarNaListaEncadeada(first, noTriagem, "sudorese", "sudorese");

	adicionarNaListaEncadeada(first, noTriagem, "febre", "febre");

	/* Esta parte eh temporaria enquanto falta definocoes para a integracao */
	if((new = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;

	for(aux = first; aux->next != NULL; aux = aux->next);
		aux->next = new;

	strcpy(new->attribute,"emagrecimento");
	strcpy(new->value,"ignorado");
	new->entry = 0.0;
	new->next = NULL;
	/* ******************************************************************** */

	adicionarNaListaEncadeada(first, noTriagem, "dispneia", "dispneia");

	/* Esta parte eh temporaria enquanto falta definocoes para a integracao */
	if((new = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;

	for(aux = first; aux->next != NULL; aux = aux->next);
		aux->next = new;

	strcpy(new->attribute,"anorexia");
	strcpy(new->value,"ignorado");
	new->entry = 0.0;
	new->next = NULL;
	/* ******************************************************************** */

	/* Esta parte eh temporaria enquanto falta definocoes para a integracao */
	if((new = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;

	for(aux = first; aux->next != NULL; aux = aux->next);
		aux->next = new;

	strcpy(new->attribute,"fuma_atualmente");
	strcpy(new->value,"ignorado");
	new->entry = 0.0;
	new->next = NULL;
	/* ******************************************************************** */

	/* Esta parte eh temporaria enquanto falta definocoes para a integracao */
	if((new = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;

	for(aux = first; aux->next != NULL; aux = aux->next);
		aux->next = new;

	strcpy(new->attribute,"tb_extrapulmonar");
	strcpy(new->value,"ignorado");
	new->entry = 0.0;
	new->next = NULL;
	/* ******************************************************************** */

	adicionarNaListaEncadeada(first, noTriagem, "internado", "internacao_hospitalar");

	/* Esta parte eh temporaria enquanto falta definocoes para a integracao */
	if((new = (chainType_2*)malloc(sizeof(chainType_2))) == NULL)
		return NULL;

	for(aux = first; aux->next != NULL; aux = aux->next);
		aux->next = new;

	strcpy(new->attribute,"sida");
	strcpy(new->value,"ignorado");
	new->entry = 0.0;
	new->next = NULL;
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
	*           Recuperando o nome do paciente              *
	*********************************************************/
/*	aux_2 = first_2;
	if (!strcmp("nomeCompleto", first_2->attribute))
	{
			strcpy(nome,first_2->value);
			first_2 = first_2->next;
	}
	else
		while (aux_2->next)
		{
			if (!strcmp("nomeCompleto", aux_2->next->attribute))
			{
				strcpy(nome,aux_2->next->value);
				aux_2->next = aux_2->next->next;
			}
			aux_2 = aux_2->next;	
		}
	*/

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

	aux_2 = first_2;
	geraGrafico(grupo, raioOriginal, response, pid, aux_2);


	/****************************************************** 
	 *               Liberando a Memória                  *
	 ******************************************************/
	aux = first;
	while(aux != NULL)
	{
		//printf("%s - %s - %f\n",aux->attribute,aux->value,aux->entry);
		first = aux;
		aux = aux->next;
		free(first);
	}

	aux_2 = first_2;
	while(aux_2 != NULL)
	{
		//printf("%s - %s - %f\n",aux_2->attribute,aux_2->value,aux_2->entry);
		first_2 = aux_2;
		aux_2 = aux_2->next;
		free(first_2);
	}


	cgi_end();
	
	return 0;
}

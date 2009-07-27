/*
	Universidade Federal do Rio de Janeiro
	Escola Politecnica
	Departamento de Engenharia Eletronica e de Computacao
	
	Laboratorio de Processamento de Sinais
	Projeto Neural TB
	Autor: Patrick Svaiter

	$Author$
	$Date$
	$Log$
 */

#ifndef NTB_FUNCTIONS
#define NTB_FUNCTIONS "@(#)ntbFunctions.h $Revision$"

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
#include "ntbTypes.h"

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

void getUserPublicPath (char *address);

char *to_uppercase (char *);

int convertISO88591toUTF8 (unsigned char *, unsigned char **);

unsigned char *fixCgiStr (unsigned char *);

void getTagNameAndTextContent (char *, parsedvars *);

char* translate_escape_character (char*);

void autoBackup(void);

/*
 * FUNCAO QUE BUSCA UM PACIENTE PELO NUMERO GERAL USANDO A LIBXML2
 * RETORNA O NO DO PACIENTE SE O ENCOTRAR
 * RETORNA NULL CASO CONTRARIO
 */
xmlNodePtr pegaPacientePorNumeroGeral(xmlDocPtr, char *);

/*
 * FUNCAO QUE RETORNA O NO DO FORMULARIO CUJO NOME CORRESPONDE A CONST CHAR
 * RETORNA NULL CASO NAO O ACHE
 *
 * OBS: ESTA FUNCAO RECEBE O NO DO PACIENTE QUE EH O MESMO RETORNADO PELA FUNCAO pegaPacientePorNumeroGeral
 */
xmlNodePtr pegaFormulario(xmlNodePtr, const char *);

/*
 * FUNCAO QUE RETORNA O VALOR DA TAG CUJO O NOME ESTA CONTIDO EM "TAG", E ESTA DENTRO DO FOMULARIO "FORMULARIO"
 * RETORNA NULL CASO NAO ACHE A TAG OU CASO O VALOR DA TAG SEJA NULL
 *
 * noPai - no do paciente o qual quer ser procurado a tag e seu valor
 ****** obs: a estrutura deste no eh a mesma retornada pela funcao pegaPacientePorNumeroGeral
 * formulario - nome do fomulario onde quer ser procurado a tag; ex: triagem
 ****** obs: caso formulario == null sera buscada a tag em todos os formularios do paciente, sendo retornado o valor da primeira tag encontrada
 * tag - nome da tag cujo valor eh esperado
 * 
 */
char *pegaValorDaTag(xmlNodePtr noPai, const char *formulario, const char *tag);

#endif

/* $RCSfile$ */

/*
	Universidade Federal do Rio de Janeiro
	Escola Politecnica
	Departamento de Engenharia Eletronica e de Computacao
	
	Laboratorio de Processamento de Sinais
	Projeto Neural TB
	
	Autor: Patrick Svaiter
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
#include <libxml/encoding.h>

/* Headers for stat(), fork(), wait() and execl() */
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cgi.h"
#include "ntbError.h"
#include "ntbTypes.h"
#include "ntbFunctions.h"
/*
Gets current-user's public html path
*/

void getUserPublicPath (char *address)
{
	const char* path = getenv("SCRIPT_FILENAME");
	char* pos = strrchr(path, '/');
	
	strncpy(address,path,(size_t)(pos - path));
	address[(size_t)(pos - path)]=0;
	
//	return;
}

/*
	Convert lowercase letters to uppercase in a string
	Returns the new string keeping the original one intact
	
	A void function that replace the original string with the uppercase one
	is easily achieved by removing malloc and its error treatment.
*/
char *to_uppercase (char *str)
{
	int i, len;
	char *STR;
	
	i=0;
	len = strlen (str);
	STR = (char *) malloc(len +1);
	if (!STR)
		return NULL;
	
	while (i < len)
	{
		STR[i] = (char) toupper (str[i]);
		i++;
	}
	
	STR[i] = '\0';
	
	return STR;
}


/**
 * Check if a string is an UTF-8.
 * If it is, a new string, copy of @in, is returned.
 * If not, a conversion is made from ISO Latin 1 to UTF-8 and the new string is
 * returned.
 * That's because an enconding detection is not performed and the former has
 * a large use in web.
 * This routine is intended to make use of the same variable whether it was
 * converted or not.
 *
 * Input
 *	@in: a pointer to an array of ISO Latin 1 chars
 * Output
 *	-
 * Returns:
 *	NULL in case of error
 *	A new string if success
 *
 * Notes: Returned string may be freed by the caller if != NULL
 *
 * use:
 *	char *str_in, *str_out;
 *	str_out = fixCgiStr (str_in); 
 */
xmlChar *fixCgiStr (xmlChar *in)
{
	int utf8;
	xmlChar *out = NULL;
	
	if (in == NULL) return NULL;
	
	utf8 = xmlCheckUTF8 (in);
	if (!utf8)
	{
		if (convertISO88591toUTF8(in, &out) < 0)
			return NULL;
		return (out);
	}
	
	return (xmlStrdup(in));
}

/**
 * Convert a string from ISO-8859-1 to UTF-8
 * Allocates double of ISO string size for UTF-8 string size
 * Input
 *	@strISO: a pointer to an array of ISO Latin 1 chars
 * Output
 *	@*strUTF: a pointer to an array of UTF-8 chars
 *
 * Returns:
 * -2 if any of char pointers are NULL
 * Otherwise, returns isolat1ToUTF8 return
 * Notes: strUTF may be freed by the caller if return >= 0
 */
int convertISO88591toUTF8 (unsigned char *strISO, unsigned char **strUTF)
{	
	int lenISO, lenUTF, rc;
	
	if (strISO == NULL || strUTF == NULL)
		return(-2);
	
	lenISO = strlen((char *)strISO);
	lenUTF = 2 * lenISO;
	*strUTF = BAD_CAST malloc ((size_t) (lenUTF + 1));
	
	rc = isolat1ToUTF8 (*strUTF, &lenUTF, strISO, &lenISO);
	(*strUTF)[lenUTF] = '\0';
	
	if (rc < 0)
		free(*strUTF);
	
	return rc;
}

/*
	It gets the tag name and the text content between 2 tags.
	
	This is not a general parsing function.
	It does not verify several conditions to avoid unexpected behaviors,
	like checking if end of string was reached.
	Thus, it is a custom-made for a specific xml doc, which must contain
	in a line a starting tag and at least another starting tag, where it
	will stop getting text content. The tag name returned belongs to the
	first starting tag found.
	In the future, this may disappear to make way for an expat function.
	
	Expat is a C library for XML manipulation
*/
void getTagNameAndTextContent (char *str, parsedvars *parsed)
{
	int i,j;
	
	for (i=0; str[i] != '<'; i++);
	
	i++;
	for (j=0; ((str[i] != ' ') && (str[i] != '>')); i++, j++)
		parsed->name[j] = str[i];
	
	parsed->name[j] = '\0';
	
	if (str[i] == ' ')
		for ( ; str[i] != '>'; i++);	//skipping attributes
	
	i++;
	for (j=0; ((str[i] != '<') && (str[i] != '\0') && (str[i] != '\n')); i++, j++)
		parsed->text[j] = str[i];
	
	parsed->text[j] = '\0';
	
	return;
}

char* translate_escape_character (char*);

char* translate_escape_character (char* palavra)
{
	char* temp;
	int indice1, indice2;

	if(!(temp = malloc(2*strlen(palavra))))
		exit(1); // erro na alocação de memoria
	
	for(indice1 = indice2 = 0; palavra[indice1] != '\0'; indice1 ++, indice2 ++)
	{
		if(palavra[indice1] == '\r')
		{
			temp[indice2] = '\\';
			temp[indice2 + 1] = 'r';
			indice2 ++;
		}
		else
		{
			if(palavra[indice1] == '\n')
			{
				temp[indice2] = '\\';
				temp[indice2 + 1] = 'n';
				indice2 ++;
			}
			else
			{
				if(palavra[indice1] == '\'')
				{
					temp[indice2] = '\\';
					temp[indice2 + 1] = '\'';
					indice2 ++;
				}
				else
				{
					if(palavra[indice1] == '\"')
					{
						temp[indice2] = '\\';
						temp[indice2 + 1] = '\"';
						indice2 ++;
					}
					else
					{
						if(palavra[indice1] == '\\')
						{
							temp[indice2] = '\\';
							temp[indice2 + 1] = '\\';
							indice2 ++;
						}
						else
							temp[indice2] = palavra[indice1];
					}
				}
			}
		}	
	}
	
	temp[indice2] = '\0';
	
	return temp;
}

char* translate_escape_character_xsl (char *);
/*
char* translate_escape_character_xsl (char* palavra)
{
	char* temp;
	int indice1, indice2;

	if(!(temp = malloc(10*strlen(palavra))))
		exit(1); // erro na alocação de memoria
	
	memset(temp,0,10*strlen(palavra));
	
	for(indice1 = 0; palavra[indice1] != '\0'; indice1 ++)
	{
		switch (palavra[indice1])
		{
			case '\'':
				strcat(temp, "&apos;");
				break;
				
			case '\"':
				strcat(temp, "&#34;");
				break;
			
			case '&':
				strcat(temp, "&#38;");
				break;
				
			case 'á':
				strcat(temp, "&#225;");
				break;
				
			case 'à':
				strcat(temp, "&#224;");
				break;
				
			case 'â':
				strcat(temp, "&#226;");
				break;
				
			case 'ã':
				strcat(temp, "&#227;");
				break;
			
			case 'Á':
				strcat(temp, "&#193;");
				break;
				
			case 'À':
				strcat(temp, "&#192;");
				break;
				
			case 'Â':
				strcat(temp, "&#194;");
				break;
				
			case 'Ã':
				strcat(temp, "&#195;");
				break;
			
			case 'é':
				strcat(temp, "&#233;");
				break;
				
			case 'è':
				strcat(temp, "&#232;");
				break;
				
			case 'ê':
				strcat(temp, "&#234;");
				break;
				
			case 'É':
				strcat(temp, "&#201;");
				break;
				
			case 'È':
				strcat(temp, "&#200;");
				break;
				
			case 'Ê':
				strcat(temp, "&#202;");
				break;
				
			case 'í':
				strcat(temp, "&#237;");
				break;
				
			case 'ì':
				strcat(temp, "&#236;");
				break;
				
			case 'î':
				strcat(temp, "&#238;");
				break;

			case 'Í':
				strcat(temp, "&#205;");
				break;
				
			case 'Ì':
				strcat(temp, "&#204;");
				break;
				
			case 'Î':
				strcat(temp, "&#206;");
				break;

			case 'ó':
				strcat(temp, "&#243;");
				break;
				
			case 'ò':
				strcat(temp, "&#242;");
				break;
				
			case 'ô':
				strcat(temp, "&#244;");
				break;
				
			case 'õ':
				strcat(temp, "&#245;");
				break;
				
			case 'Ó':
				strcat(temp, "&#211;");
				break;
				
			case 'Ò':
				strcat(temp, "&#210;");
				break;
				
			case 'Ô':
				strcat(temp, "&#212;");
				break;
				
			case 'Õ':
				strcat(temp, "&#213;");
				break;
			
			case 'ú':
				strcat(temp, "&#250;");
				break;
				
			case 'ù':
				strcat(temp, "&#249;");
				break;
				
			case 'û':
				strcat(temp, "&#251;");
				break;

			case 'Ú':
				strcat(temp, "&#218;");
				break;
				
			case 'Ù':
				strcat(temp, "&#217;");
				break;
				
			case 'Û':
				strcat(temp, "&#219;");
				break;
			
			case 'ü':
				strcat(temp, "&#252;");
				break;
			
			case 'Ü':
				strcat(temp, "&#220;");
				break;
				
			case 'ç':
				strcat(temp, "&#231;");
				break;
				
			case 'Ç':
				strcat(temp, "&#199;");
				break;
				
			case 'ñ':
				strcat(temp, "&#241;");
				break;
				
			case 'Ñ':
				strcat(temp, "&#209;");
				break;
				
			case '<':
				strcat(temp, "&#60;");
				break;
				
			case '>':
				strcat(temp, "&#62;");
				break;
				
			case '/':
				strcat(temp, "&#47;");
				break;
				
			case '\\':
				strcat(temp, "&#92;");
				break;
			
			default:
				temp[strlen(temp)] =  palavra[indice1];
				break;
			
		}
	}
	
	temp[strlen(temp)] = '\0';
	
	return temp;
}*/

char* translate_escape_character_xsl (char* palavra)
{
	char* temp;
	int indice1, indice2;

	if(!(temp = malloc(2*strlen(palavra))))
		exit(1); // erro na alocação de memoria
	
	for(indice1 = indice2 = 0; palavra[indice1] != '\0'; indice1 ++, indice2 ++)
	{
		if(palavra[indice1] == '\'')
		{
			temp[indice2] = '&';
			temp[++indice2] = 'a';
			temp[++indice2] = 'p';
			temp[++indice2] = 'o';
			temp[++indice2] = 's';
			temp[++indice2] = ';';
		}
		else
		{
			if(palavra[indice1] == '\"')
			{
				temp[indice2] = '&';
				temp[++indice2] = 'q';
				temp[++indice2] = 'u';
				temp[++indice2] = 'o';
				temp[++indice2] = 't';
				temp[++indice2] = ';';
			}
			else
			{
				if(palavra[indice1] == '&')
				{
				temp[indice2] = '&';
				temp[++indice2] = 'a';
				temp[++indice2] = 'm';
				temp[++indice2] = 'p';
				temp[++indice2] = ';';
				}
				else
					temp[indice2] = palavra[indice1];
			}
		}	
	}
	
	temp[indice2] = '\0';
	
	return temp;
}

/* Automated backup code */
#define AUTOBACKUP_SCRIPT "/usr/lib/projetotb/tbbackup/tbbackup"

/**
 * Check if the script for automatic backup exists, and call it.
 */
void autoBackup(void)
{
    struct stat statBuf;
    pid_t childPid;
    int childStatus;

    if (stat(AUTOBACKUP_SCRIPT, &statBuf) != 0) {
        // Backup script not found.
        return;
    }

    // Fork and execute the script
    if (childPid = fork()) {
        // We're the parent process
        wait(&childStatus);
    } else {
        // We're th children process.
        // Silence stdout and stderr
        close(1);
        close(2);
        execl(AUTOBACKUP_SCRIPT,
                AUTOBACKUP_SCRIPT,
                "xml/pacientesGuadalupe.xml",
                "../guadalupeXMLRepo",
                (char *)NULL);
        // Will only reach here if can't execute the script.
        exit(-1);
    }
}

/*
 * FUNCAO QUE BUSCA UM PACIENTE PELO NUMERO GERAL USANDO A LIBXML2
 * RETORNA O NO DO PACIENTE SE O ENCOTRAR
 * RETORNA NULL CASO CONTRARIO
 */
xmlNodePtr pegaPacientePorNumeroGeral(xmlDocPtr doc, char *numeroGeral)
{
	if(doc == NULL)
		return NULL;

	if(numeroGeral == NULL)
		return NULL;

	xmlNodePtr noBuscado, aux;

	aux = xmlDocGetRootElement(doc);/* AUX RECEBE NO ROOT DA ARVORE */

	aux = aux->children;/* AUX RECEBE O NO DO PACIENTE */
	while(aux != NULL)
	{
		noBuscado = aux;

		/* BUSCA PELA TAG "TRIAGEM" */
		noBuscado = noBuscado->children;/* triagem? */
		while(((xmlStrEqual(noBuscado->name, BAD_CAST "triagem")) != 1) && (noBuscado != NULL))
			noBuscado = noBuscado->next;

		if(noBuscado == NULL)/* TAG "TRIAGEM" NAO ENCONTRADA */
			return NULL;

		/* BUSCA PELA TAG "NUMERO GERAL" */
		noBuscado = noBuscado->children;/* numeroGeral? */
		while(((xmlStrEqual(noBuscado->name, BAD_CAST "numeroGeral")) != 1) && (noBuscado != NULL))
			noBuscado = noBuscado->next;

		if(noBuscado == NULL)/* TAG "NUMERO GERAL" NAO ENCONTRADA */
			return NULL;

		if((xmlStrEqual(noBuscado->children->content, BAD_CAST numeroGeral)) == 1)
			return noBuscado->parent->parent;/* RETORNA O NO DO PACIENTE */

		aux =  aux->next;
	}

	return NULL;
}

/*
 * FUNCAO QUE RETORNA O NO DO FORMULARIO CUJO NOME CORRESPONDE A CONST CHAR
 * RETORNA NULL CASO NAO O ACHE
 */
xmlNodePtr pegarFilhoPorNome(xmlNodePtr noPai, const char *nome)
{
	if(noPai == NULL)
		return NULL;

	if(nome == NULL)
		return NULL;

	xmlNodePtr noBuscado, aux;

	if((xmlStrEqual(noPai->name, BAD_CAST nome)) == 1)
		return noPai;

	noBuscado = noPai->children;
	while(noBuscado != NULL)
	{
		if((xmlStrEqual(noBuscado->name, BAD_CAST nome)) == 1)
			return noBuscado;

		for(aux = noBuscado->children; aux != NULL; aux = aux->next)
			if((xmlStrEqual(aux->name, BAD_CAST nome)) == 1)
				return aux;

		noBuscado = noBuscado->next;
	}

	return NULL;
}

/*
 * FUNCAO QUE RETORNA O VALOR DA TAG CUJO O NOME ESTA CONTIDO EM "TAG"
 * RETORNA NULL CASO NAO ENCONTRE A TAG
 */
char *pegaValorDaTag(xmlNodePtr noPai, const char *tag)
{
	if(noPai == NULL)
		return NULL;

	if(tag == NULL)
		return NULL;

	xmlNodePtr tagBuscada;

	if((tagBuscada = pegarFilhoPorNome(noPai, tag)) == NULL)
		return NULL;

	if(tagBuscada->children == NULL)
		return NULL;

	return tagBuscada->children->content;
}

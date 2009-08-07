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
#include <time.h>

#include "cgi.h"

#include "ntbError.h"
//#include "ntbConfig.h"
//#include "ntbConsts.h"
#include "ntbFunctions.h"

//#include "ntbSearchPatient.h"


//#define PATHFILE "xml/xsl/resultado.xsl"

void printError (char *msg)
{
	cgi_init_headers();
	
	printf ("<html><head><title>Erro</title></head><body><h2>%s</h2></body></html>", msg);
}

int main (void)
{
	char tempname [L_tmpnam];
	char comando[100];
	char address[100];

	FILE *xsl;
	//size_t len;
	//char xmlSearchResultFilePath[FILE_NAME_MAX];
	//char healthCenter[HEALTH_CENTER_NAME_MAX];
	formvars *first;
	char *pid;
	

	cgi_init();
	cgi_init_headers();
	fflush(stdout);
	
/******************************************************************************
 *            READ CONTENT STRING FROM SERVER.                                *
 *            PROCESS DATA.                                                   *
 *            CREATE A LINKED LIST.                                           *
 ******************************************************************************/
	
	first = cgi_process_form();
	
/******************************************************************************
 *            ACQUIRE VALUES CHOSEN BY USER                                   *
 ******************************************************************************/
	
	pid = cgi_param("pid");
	
/******************************************************************************
 *            CREATE XSL SEARCH FILE                                          *
 ******************************************************************************/
 
if (tmpnam(tempname) != NULL)
{

//	sprintf(comando,"arquivo: %s", tempname);
//	printError(comando);

	xsl = fopen(tempname, "w");
	
	fprintf(xsl,"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"<xsl:stylesheet xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" version=\"1.0\">\r\n");
//	fprintf(xsl,"				xmlns:fo=\"http://www.w3.org/1999/XSL/Format\"\r\n");
//	fprintf(xsl,"				xmlns=\"http://www.w3.org/1999/xhtml\">\r\n");
	fprintf(xsl,"<xsl:output omit-xml-declaration=\"yes\" encoding=\"ISO-8859-1\" method=\"xml\"/>\r\n"); 
	fprintf(xsl,"\r\n");
	
	getUserPublicPath(address);
	
	fprintf(xsl,"<xsl:include href=\"%s/xml/xsl/fullPatientDetails2.xsl\" />\r\n",address);
//	printf("%s",address);
	
	fprintf(xsl,"\r\n");
	fprintf(xsl,"<xsl:template match=\"/\">\r\n");
	fprintf(xsl,"	<xsl:variable name=\"contador\">");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"		0");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"		<xsl:for-each select=\"pacientes/paciente\">");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"		<xsl:if test=\"numeroGeral = '%s'\">\r\n", translate_escape_character_xsl(pid));
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"				<xsl:number count=\"paciente\" />");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"			</xsl:if>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"		</xsl:for-each>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"	</xsl:variable>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"	<xsl:choose>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"		<xsl:when test=\"$contador != 0\">");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"			<xsl:apply-templates select=\"pacientes\" />");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"		</xsl:when>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"		<xsl:otherwise>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"			<p>&#160;&#160;&#160;&#160;&#160;<b>O paciente não possui histórico.</b></p>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"		</xsl:otherwise>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"	</xsl:choose>");
	fprintf(xsl,"		\r\n");
	fprintf(xsl,"</xsl:template>\r\n");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"<xsl:template match=\"pacientes\">\r\n");
	fprintf(xsl,"	<!-- Tags' values -->\r\n");
	fprintf(xsl,"	<xsl:for-each select=\"paciente\">\r\n");
	fprintf(xsl,"	<xsl:sort select=\"descendant::nomeCompleto\" />\r\n");
	fprintf(xsl,"		<xsl:if test=\"numeroGeral = '%s'\">\r\n", translate_escape_character_xsl(pid));

	fprintf(xsl,"			<p align=\"right\"><a target=\"blank\" href=\"imprimir.cgi?pid=%s\">Versão para Impressão</a></p>\r\n", translate_escape_character_xsl(pid));
	fprintf(xsl,"			<p>TRIAGEM</p>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<xsl:apply-templates select=\"triagemInfo\" />");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			<p></p>\r\n");
	
	fprintf(xsl,"			<p>CONSULTA M&#201;DICA</p>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<xsl:apply-templates select=\"consultaMedicaInfo\" />");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			<p></p>\r\n");
	
	fprintf(xsl,"			<p>FOLLOW-UP</p>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<xsl:apply-templates select=\"followUpInfo\" />");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			<p></p>");

	/*fprintf(xsl,"			<table>\r\n");
	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<th colspan=\"2\">Critério Inicial de Triagem para TB</th>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			<xsl:apply-templates select=\"triagem\" />\r\n");


	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<td colspan=\"2\" height=\"10\"></td>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			\r\n");
	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<th colspan=\"2\">Question&#225;rio de Custos - Parte A</th>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			<xsl:apply-templates select=\"custosA\" />\r\n");
	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<td colspan=\"2\" height=\"10\"></td>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			\r\n");
	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<th colspan=\"2\">Consulta M&#233;dica</th>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			<xsl:apply-templates select=\"consultaMedica\" />\r\n");
	fprintf(xsl,"			<tr>\r\n");	
	fprintf(xsl,"				<td class=\"title3\" colspan=\"2\" height=\"10\"></td>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			\r\n");
	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<th class=\"title3\" colspan=\"2\">Question&#225;rio de Custos - Partes B e C</th>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			<xsl:apply-templates select=\"custosBeC\" />\r\n");
	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<td class=\"title3\" colspan=\"2\" height=\"10\"></td>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			\r\n");
	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<th colspan=\"2\">Follow Up - 90 dias</th>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			<xsl:apply-templates select=\"followUp\" />\r\n");

/*	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<td colspan=\"2\" height=\"10\"></td>\r\n");
	fprintf(xsl,"			</tr>\r\n");
	fprintf(xsl,"			\r\n");
	fprintf(xsl,"			<tr>\r\n");
	fprintf(xsl,"				<th class=\"title3\">Gr&#225;fico de Grupo</th>\r\n");
	fprintf(xsl,"				<td><!--<a href=\"{concat(graficoGrupo, triagem/numeroGeral)}\" target=\"_blank\">Visualizar</a>--></td>\r\n");
	fprintf(xsl,"			</tr>\r\n");

	fprintf(xsl,"			</table>\r\n");*/
	fprintf(xsl,"			<br /><br />\r\n");
	fprintf(xsl,"		</xsl:if>\r\n");
	fprintf(xsl,"	</xsl:for-each>\r\n");
	fprintf(xsl,"	\r\n");
	fprintf(xsl,"</xsl:template>\r\n");
	fprintf(xsl,"\r\n");
	
	fprintf(xsl,"<xsl:template match=\"triagemInfo\">");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"		<xsl:for-each select=\"versao\">");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			<table name=\"tabelaTriagem\" >");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<tr onclick=\"exibirTabela(this, 'tabelaTriagem')\"\n>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<td>	<xsl:number count=\"versao\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td class='link'>Ver detalhes</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td>Vers&#227;o de:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"data\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"					<td>Quem modificou:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"avaliador\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td>Motivo:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"histMotivo\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<th colspan=\"2\">Critério Inicial de Triagem para TB</th>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<xsl:apply-templates select=\"triagem\" />");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			</table>");
	fprintf(xsl,"			<p></p>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"		</xsl:for-each>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"</xsl:template>\r\n");
	
	fprintf(xsl,"<xsl:template match=\"consultaMedicaInfo\">");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"		<xsl:for-each select=\"versao\">");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			<table name=\"tabelaConsulta\" >");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<tr onclick=\"exibirTabela(this, 'tabelaConsulta')\"\n>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<td>	<xsl:number count=\"versao\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td class='link'>Ver detalhes</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td>Vers&#227;o de:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"data\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
		fprintf(xsl,"\r\n");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td>Quem modificou:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"avaliador\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td>Motivo:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"histMotivo\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<th colspan=\"2\">Consulta M&#233;dica</th>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<xsl:apply-templates select=\"consultaMedica\" />");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			</table>");
	fprintf(xsl,"			<p></p>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"		</xsl:for-each>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"</xsl:template>\r\n");
	
	fprintf(xsl,"<xsl:template match=\"followUpInfo\">");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"		<xsl:for-each select=\"versao\">");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			<table name=\"tabelaFollowUp\" >");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<tr onclick=\"exibirTabela(this, 'tabelaFollowUp')\"\n>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<td>	<xsl:number count=\"versao\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td class='link'>Ver detalhes</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td>Vers&#227;o de:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"data\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"					<td>Quem modificou:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"avaliadorMedicoFollowUp\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td>Motivo:</td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<td><xsl:value-of select=\"histMotivo\" /></td>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"					<th colspan=\"2\">Follow-up:</th>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				</tr>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"				<xsl:apply-templates select=\"followUp\" />");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"			</table>");
	fprintf(xsl,"			<p></p>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"		</xsl:for-each>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"</xsl:template>");
	fprintf(xsl,"\r\n");
	fprintf(xsl,"</xsl:stylesheet>\r\n");
	fclose(xsl);

}
else
	printError("Erro ao criar arquivo temporário!\n");
	
	
	
/******************************************************************************
 *            XSL TRANSFORM                                                *
 ******************************************************************************/

//		sprintf(comando,"xsltproc %s xml/pacientesGuadalupe.xml 2>&1 --encoding ISO-8859-1",tempname);
		sprintf(comando,"xsltproc %s xml/pacientesHistorico.xml 2>&1",tempname);

		printf("<html>\n");
		printf("<head>\n");
		printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"css/main.css\" />\n");
		printf("	<script src=\"js/jquery.js\"></script>\n");
		printf("	<script src=\"js/colors.js\"></script>\n");		
		printf ("	<script>\n");
		printf ("\n");
		printf ("	function inicializaOcultos(tabela)\n");
		printf ("	{\n");
		printf ("		totalTabela = document.getElementsByName(tabela);\n");
		printf ("		for (i=0; i<totalTabela.length; i++)\n");
		printf ("		{\n");
		printf ("			totalLinha = totalTabela[i].rows;\n");
		printf ("			for (j=2; j< totalLinha.length; j++)\n");
		printf ("			{\n");
		printf ("				totalLinha[j].style.display = \"none\";\n");
		printf ("			}\n");
		printf ("		}\n");
		printf ("	}\n");
		printf ("	\n");
		printf ("	function exibirTabela(linha, tabela)\n");
		printf ("	{\n");
		printf ("		identificacao = linha.cells[0].innerHTML - 1;\n");
		printf (" 	operacao = linha.cells[1].innerHTML;\n");
		printf ("		totalTabela = document.getElementsByName(tabela)[identificacao];\n");
		printf ("		for (i=2; i<totalTabela.rows.length; i++)\n");
		printf ("		{\n");
		printf ("			if (operacao == 'Ver detalhes')\n");
		printf ("			{\n");
		printf ("				totalTabela.rows[i].style.display = \"\";\n");
		printf ("			}\n");
		printf ("			else\n");
		printf ("			{\n");
		printf ("				totalTabela.rows[i].style.display = \"none\";\n");
		printf ("			}\n");
		printf ("		}\n");
		printf ("		if (operacao == 'Ver detalhes')\n");
		printf ("		{\n");
		printf ("				linha.cells[1].innerHTML = \"Esconder detalhes\";\n");
		printf ("		}\n");
		printf ("		else\n");
		printf ("		{\n");
		printf ("				linha.cells[1].innerHTML = \"Ver detalhes\";\n");
		printf ("		}\n");
		
	//	printf (" alert(identificacao);\n");
		printf ("	}\n");
		printf ("	\n");
		printf ("	</script>\n");
		printf("<title>Resultado</title>\n");
		printf("</head>\n");
		printf ("<body  onLoad=\"inicializaOcultos('tabelaTriagem'); inicializaOcultos('tabelaConsulta'); inicializaOcultos('tabelaFollowUp');\">\n");

//debugin ... YEP
		fflush(stdout);		
		
//		system("xsltproc xml/xsl/listar.xsl xml/pacientesGuadalupe.xml 2>&1");
		system(comando);
		sprintf(comando,"rm %s 2>&1",tempname);
		system(comando);
		printf("</body>\n");
		printf("</html>\n");



/******************************************************************************
 *            FREE MEMORY AND EXIT                                            *
 ******************************************************************************/
	
	cgi_end();
	
	return (ok);
}
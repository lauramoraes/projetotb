/*
	Universidade Federal do Rio de Janeiro
	Escola Politecnica
	Departamento de Engenharia Eletronica e de Computacao
	
	Laboratorio de Processamento de Sinais
	Projeto Neural TB (Guadalupe)
	Autor: Igor Cunha Braganca
	Atualiza��o: Laura Moraes

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
#include "functions.h"
#include "const.h"

#define XML_FILE_PATH "./xml/pacientesGuadalupe.xml"
#define USUARIO_ANONIMO "anonimo"

void usualFreeMemory (xmlDocPtr doc)
{
	if (doc)
		xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
}

void printError (char *msg)
{
	/*cgi_init_headers();
	
	printf ("<html><head><title>Erro</title></head><body><h2>%s</h2></body></html>", msg);*/
	printf ("</script></head><body><h2>%s</h2></body></html>", msg);
}

int main (void)/*(int argc,char**argv)*/
{
	int indice1;
	char *username, *numeroGeral, fraseFinal[FIELD_MAX], fraseFinal2[FIELD_MAX], *temp, *pid;
	FILE* document;
	int estado;
	/** 
	*	se estado = 0 (verdadeiro)
	*	se estado = 1 (falso)
	*/
	
	/* variaveis usadas pela libxml2 */
	xmlDocPtr doc;
	xmlNodePtr root_element, cur_node, cur_node_children;
	
	
	cgi_init();
	cgi_process_form();
	
	numeroGeral = pid = cgi_param("pid");
	username = cgi_param("uid");

	if(username == NULL)
		username = USUARIO_ANONIMO;
	
	// cgi_init_headers();
	// Funcao criada por Felipe para fazer com que o browser interprete o
	// HTML como utf-8.
	cgi_init_headers_with_content_type("text/html; charset=utf-8");

	/* HTML */
	printf ("<html>\n");
	printf ("<head>\n");
	printf ("	<title>Projeto TB Adapt - Preencha todos os campos do formul&aacute;rio abaixo</title>\n");
	printf ("	<link rel=\"stylesheet\" type=\"text/css\" href=\"css/main.css\">\n");
	printf ("	<link rel=\"stylesheet\" type=\"text/css\" href=\"css/menu.css\">\n");
	printf ("	<link rel=\"stylesheet\" type=\"text/css\" href=\"css/form.css\">\n");
	printf ("	<script charset=\"ISO-8859-1\" language=javascript src=\"js/funcoes.js\"></script>\n");
	if(!(strcmp(username,"digitador")))
		printf ("	<script charset=\"ISO-8859-1\" language=javascript src=\"js/validar_.js\"></script>\n");
	else
		printf ("	<script charset=\"ISO-8859-1\" language=javascript src=\"js/validar.js\"></script>\n");
	printf ("\n");
	printf ("	<script>/* Funcao que  oculta as linhas do formulario que nao deverao se vistas em seu carregamento inicial */\n");
	printf ("\n");
	printf ("	tabFields= new Array(26);\n");
	printf ("	tabFields[0] = [\"inclusao\", \"Crit&eacute;rios de inclus&atilde;o:\"];\n");
	printf ("	tabFields[1] = [\"especimes_respiratorios\", \"Data da coleta dos DOIS esp&eacute;cimes respirat&oacute;rios:\"];\n");
	printf ("	tabFields[2] = [\"cicatriz_bcg\", \"Cicatriz de BCG presente?(Checar delt&oacute;ide direito):\"];\n");
	printf ("	tabFields[3] = [\"resultado_leitura\", \"Resultado da leitura (mil&iacute;metros de endura&ccedil;&atilde;o):\"];\n");
	printf ("	tabFields[4] = [\"aplicacao_data\", \"Data da aplica&ccedil;&atilde;o da prova tubercul&iacute;nica (dia/m&ecirc;s/ano):\"];\n");
	printf ("	tabFields[5] = [\"leitura_data\", \"Data da leitura (dia/m&ecirc;s/ano):\"];\n");
	printf ("	tabFields[6] = [\"pt_1dose\", \"PT 1&170; dose Leitor:\"];\n");
	printf ("	tabFields[7] = [\"tb_anterior\", \"01 - Tratamento de TB anterior: (Verificar no questionario Triagem)\"];\n");
	printf ("	tabFields[8] = [\"inh\", \"01.1 - INH:\"];\n");
	printf ("	tabFields[9] = [\"rif\", \"01.2 - RIF:\"];\n");
	printf ("	tabFields[10] = [\"esquema\", \"01.3 - Qual esquema?\"];\n");
	printf ("	tabFields[11] = [\"quimio\", \"02 - Quimioprofilaxia:\"];\n");
	//printf ("	tabFields[12] = [\"cage_positivo\",\"03 - Cage positivo:\"];\n");
	printf ("	tabFields[13] = [\"inh1\", \"02.1 - INH:\"];\n");
	printf ("	tabFields[14] = [\"rif1\", \"02.2 - RIF:\"];\n");
	printf ("	tabFields[15] = [\"data_quimio\", \"02.3 - Data da Quimioprofilaxia:\"];\n");
	printf ("	tabFields[16] = [\"desfecho\", \"02.4 - Desfecho:\"];\n");
	printf ("	tabFields[17] = [\"hiv_teste\", \"03 - HIV teste:\"];\n");
	printf ("	tabFields[18] = [\"data_antihiv\", \"04 - Data do anti-HIV:\"];\n");
	printf ("	tabFields[19] = [\"exame_fisico\", \"06 - Exame f&iacute;sico normal:\"];\n");
	printf ("	tabFields[20] = [\"exame_fisico_anormal\", \"06.1 - Descreva as altera&ccedil;&otilde;es:\"];\n");
	printf ("	tabFields[21] = [\"prob_tb_ativa\", \"07 - Probabilidade de TB ativa:\"];\n");
	printf ("	tabFields[22] = [\"prob_tb_ativa_sem_rx_baar\", \"08 - Qual a probabilidade do diagn&oacute;stico de TB pulmonar ativa sem avaliar RX de t&oacute;rax ou BAAR?\"];\n");
	printf ("	tabFields[23] = [\"prob_tb_ativa_rx\", \"09 - Probabilidade de TB ativa ao avaliar o RXT:\"];\n");
	printf ("	tabFields[24] = [\"cavitacao\", \"09.1 - Cavita&ccedil;&atilde;o:\"];\n");
	printf ("	tabFields[25] = [\"padrao_tipico\", \"09.2 - Padr&atilde;o t&oacute;pico (infiltrado em lobo(s) superior(es) e/ou segmento apical de lobo inferior):\"];\n");
	printf ("	tabFields[26] = [\"compativel\", \"09.3 - Compat&iacute;vel (alargamento mediastinal ou linf.  hilar , padr&atilde;o miliar,ou derrame pleural):\"];\n");
	printf ("	tabFields[27] = [\"atipico\", \"09.4 - At&iacute;pico (qualquer outro padr&atilde;o):\"];\n");
	printf ("	tabFields[28] = [\"nsa\", \"09.4 - At�pico (qualquer outro padr�o):\"];\n");
	printf ("	tabFields[29] = [\"baixa_prioridade\", \"09.1 - Em caso de baixa probabilidade de TB ativa responda:\"];\n");
	printf ("	tabFields[30] = [\"data_rx\", \"10 - Data do RX:\"];\n");
	printf ("	tabFields[31] = [\"prob_rx_sem_bacterio\", \"11 - Diagn&oacute;stico de probabilidade tendo informa&ccedil;&atilde;o sobre o RX de t&oacute;rax mas sem conhecimento dos resultados bacteriol&oacute;gicos:\"];\n");
	printf ("	tabFields[32] = [\"prob_tb_ativa_com_rx_sem_baar\", \"12 - Qual a probabilidade do diagn&oacute;stico de TB pulmonar ativa com a avalia&ccedil;&atilde;o do RX de t&oacute;rax e sem o BAAR?\"];\n");
	printf ("	tabFields[33] = [\"bacilos_negativas\", \"15 - Caso as duas baciloscopias iniciais sejam negativas, qual seria o diagn&oacute;stico de probabilidade de TB?\"];\n");
	printf ("	tabFields[34] = [\"prob_tb_ativa_com_rx_baar\", \"16 - Qual a probabilidade do diagn&oacute;stico de TB pulmonar ativa com a avalia&ccedil;&atilde;o do RX de t&oacute;rax e do BAAR?\"];\n");
	printf ("	tabFields[35] = [\"desfecho_consulta_inicial\", \"17 - Desfecho da consulta inicial:\"];\n");
	printf ("	tabFields[36] = [\"caso_tratamento_tb\", \"18 - Em caso de tratamento para TB(marque qual):\"];\n");
	printf ("	tabFields[37] = [\"fatores_de_risco\", \"19 - Fatores de risco para TBP MDR:\"];\n");
	printf ("	tabFields[38] = [\"comorbidades\", \"05 - Comorbidades:\"];\n");
	printf ("	tabFields[39] = [\"pid\",\"N&#186; Geral (TB Adapt): \"];\n");
	printf ("	tabFields[40] = [\"dia_inclusao\",\"Data da consulta&nbsp;:&nbsp;\"];\n");
	printf ("	tabFields[41] = [\"mes_inclusao\",\"Data da consulta&nbsp;:&nbsp;\"];\n");
	printf ("	tabFields[42] = [\"ano_inclusao\",\"Data da cosulta&nbsp;:&nbsp;\"];\n");
	printf ("	tabFields[43] = [\"resultadoBaciloscopia1\",\"13 - #1:\"];\n");
	printf ("	tabFields[44] = [\"casoPositivo1\",\"13.1 - Se positivo (1):\"];\n");
	printf ("	tabFields[45] = [\"resultadoBaciloscopia2\",\"14 - #2:\"];\n");
	printf ("	tabFields[46] = [\"casoPositivo2\",\"14.1 - Se positivo:\"];\n");
	printf ("	tabFields[47] = [\"observacoes\",\" 20 - Observa&ccedil;&otilde;es: \"];\n");
	printf ("	tabFields[48] = [\"avaliador\",\"Avaliado por: \"];\n");
	printf ("	tabFields[49] = [\"quemCadastrou\",\"Cadastrado por: \"];\n");
	printf ("	tabFields[50] = [\"histMotivo\",\" 21 - Motivo da altera&ccedil;&atilde;o: \"];\n");
	printf ("\n");
	printf ("	var tabValores= new Array(\"Masculino\", \"Feminino\", \"Presente\", \"Ausente\", \"Ignorado\",\"Sim\", \"N&atilde;o\", \"Branco\", \"N&atilde;o-branco\", \"Negro\", \"Mulato\", \"&Iacute;ndio\", \"Asi&aacute;tico\", \"Outro\", \"Casado\", \"Solteiro\", \"Separado\", \"Vi&uacute;vo\", \"Pulm&atilde;o\", \"Pleura\", \"G&acirc;nglio\");\n");
	printf ("\n");
	printf ("	function inicializaOcultos(tabela)\n");
	printf ("	{\n");
	printf ("		document.getElementById(tabela).rows[2].style.display = \"none\";//INH\n");
	printf ("		document.getElementById(tabela).rows[3].style.display = \"none\";//RIF\n");
	printf ("		document.getElementById(tabela).rows[4].style.display = \"none\";//esquema\n");
	/*
	if(cagePositivo != NULL)
	{
		if(strcmp(cagePositivo,"Sim") != 0)
		{
		printf ("	document.getElementById(tabela).rows[8].style.display = \"none\";//INH\n");
		printf ("	document.getElementById(tabela).rows[9].style.display = \"none\";//RIF\n");
		printf ("	document.getElementById(tabela).rows[10].style.display = \"none\";//data da quimio\n");
		printf ("	document.getElementById(tabela).rows[11].style.display = \"none\";//desfecho\n");
		}
	}
	else
	{
		printf ("	document.getElementById(tabela).rows[8].style.display = \"none\";//INH\n");
		printf ("	document.getElementById(tabela).rows[9].style.display = \"none\";//RIF\n");
		printf ("	document.getElementById(tabela).rows[10].style.display = \"none\";//data da quimio\n");
		printf ("	document.getElementById(tabela).rows[11].style.display = \"none\";//desfecho\n");
	}
	*/
	printf ("		document.getElementById(tabela).rows[8].style.display = \"none\";//INH\n");
	printf ("		document.getElementById(tabela).rows[9].style.display = \"none\";//RIF\n");
	printf ("		document.getElementById(tabela).rows[10].style.display = \"none\";//data da quimio\n");
	printf ("		document.getElementById(tabela).rows[11].style.display = \"none\";//desfecho\n");
	printf ("		document.getElementById(tabela).rows[16].style.display = \"none\";//Comorbidades\n");
	printf ("		document.getElementById(tabela).rows[17].style.display = \"none\";//Comorbidades\n");
	printf ("		document.getElementById(tabela).rows[18].style.display = \"none\";//Comorbidades\n");
	printf ("		document.getElementById(tabela).rows[19].style.display = \"none\";//Comorbidades\n");
	printf ("		document.getElementById(tabela).rows[22].style.display = \"none\";//alteracao exame fixico\n");
	printf ("		document.getElementById(tabela).rows[27].style.display = \"none\";//cavitacao\n");
	printf ("		document.getElementById(tabela).rows[28].style.display = \"none\";//padrao topico\n");
	printf ("		document.getElementById(tabela).rows[29].style.display = \"none\";//compativel\n");
	printf ("		document.getElementById(tabela).rows[30].style.display = \"none\";//atipico\n");
	printf ("		document.getElementById(tabela).rows[31].style.display = \"none\";//NSA\n");
	printf ("		document.getElementById(tabela).rows[32].style.display = \"none\";//caso baixa probabilidade\n");
	printf ("		document.getElementById(tabela).rows[33].style.display = \"none\";//caso baixa probabilidade\n");
	printf ("		document.getElementById(tabela).rows[39].style.display = \"none\";//baar positivo\n");
	printf ("		document.getElementById(tabela).rows[41].style.display = \"none\";//baar positivo\n");
	printf ("		document.getElementById(tabela).rows[45].style.display = \"none\";//caso tratamento TB\n");
	printf ("		document.getElementById(tabela).rows[46].style.display = \"none\";//fatores de risco para tbp mdr\n");
	printf ("		document.getElementById(tabela).rows[47].style.display = \"none\";//fatores de risco para tbp mdr*\n");
	printf ("	}\n");
	printf ("\n");
	printf ("	function desabilitarRadio (name, num)\n");
	printf ("	{\n");
	printf ("		for(indice=0; indice< num; indice++)\n");
	printf ("			name[indice].disabled = true;\n");
	printf ("	}\n");
	printf ("\n");
	printf ("	function habilitarRadio (name, num)\n");
	printf ("	{\n");
	printf ("		for(indice=0; indice< num; indice++)\n");
	printf ("			name[indice].disabled = false;\n");
	printf ("	}\n");
	printf ("\n");
	/*******************************************************************************************************************************************************************************************/
	/*** funcao em javascipt que atribui valores aos campos do formulario ***/
	printf ("	function preencherCampos (form)\n");
	printf ("	{\n");
	printf ("		var tabela = new Array ();\n");
	
	/*** Funcao em c, usando a libxml2, que escreve o nome do input e o valor para ser inserido no formulario pela funcao em javascript ***/

	LIBXML_TEST_VERSION

	/******************************************************************************
		*            OPENING AND PARSING AN XML FILE TO A TREE                       *
	 ******************************************************************************/

	document = fopen(XML_FILE_PATH, "r");
 	
 	if (document == NULL) {
        printError("O arquivo de pacientes n�o pode ser aberto");
        exit(0);
    }
    
	if(flock(fileno(document), LOCK_EX)) {
        printError("Erro ao trancar o arquivo");
       	fclose(document);
        exit(0);
    }
    
   //printWait("Trancado!");
   //sleep(20);
    
	doc = xmlReadFd(fileno(document), XML_FILE_PATH, NULL, 256);
		if (doc == NULL)
		{
			usualFreeMemory(NULL);
			flock(fileno(document), LOCK_EX);
			fclose(document);
			exit(0);
		}

		/*** Procurando o paciente pelo Numero Geral ***/

		root_element = xmlDocGetRootElement(doc);

		cur_node = root_element->children; /* vai para a tag <pacientes> */

		estado = 1;

		while((cur_node != NULL) && (estado == 1))
		{

			cur_node_children = cur_node->children->children; /*vai para a tag <numero geral> */

			/*
				Verifica se a tag selecionada eh a tag "numeroGeral", se n for esta tag eh procurada 
			*/
			while ((!xmlStrEqual(cur_node_children->name, BAD_CAST "numeroGeral")) && (cur_node_children))
					cur_node_children = cur_node_children->next;
			
			/*
				Verifica se o paciente em questao possui o numero geral procurado
			*/
			if (xmlStrEqual(cur_node_children->children->content, BAD_CAST pid))
				estado = 0;
			else
				cur_node = cur_node->next;		
		}
		temp = translate_escape_character(cur_node_children->children->content);
		printf ("\t\ttabela[0] = [\"%s\",\"%s\"];\n", cur_node_children->name, temp);//Coloca a primeira posicao da tabela como Numero Geral
		free(temp);	

		/*
			saindo deste lup, teremos o noh do paciente que procuramos em cur_node
		*/
		
		if(cur_node != NULL)
		{
			cur_node = cur_node->children;
		
			while ((!xmlStrEqual(cur_node->name, BAD_CAST "consultaMedica")) && (cur_node))
					cur_node = cur_node->next;
		}

		if(!cur_node) //MENSAGEM DE ERRO
		{
			printf("</script></head><body>Paciente n�o encontrado! Por favor, verifique se ele n�o foi exclu�do!</body></html>");
			flock(fileno(document), LOCK_EX);
			fclose(document);
			exit(0);
		}
		cur_node_children = cur_node->children;

		for(indice1 = 1; cur_node_children != NULL; cur_node_children = cur_node_children->next, indice1 ++)
		{	
			if((cur_node_children->children != NULL) && (cur_node_children->name != NULL))
			{
				if(strcmp((char *)cur_node_children->name,"quemCadastrou") != 0)
				{
				temp = translate_escape_character(cur_node_children->children->content);
				printf ("\t\ttabela[%i] = [\"%s\",\"%s\"];\n", indice1, cur_node_children->name, temp);
				free(temp);
				}
				else
					indice1 --;
			}
			else
				indice1 --;
		}
		
		usualFreeMemory(NULL);	
		flock(fileno(document), LOCK_EX);
			fclose(document);
							/*
							tabela[0] = [\"campo1\",\"casa\"];\n\
							tabela[1] = [\"campo2\",\"cachorro\"];\n\
							tabela[2] = [\"campo3\",\"carro\"];\n\
							tabela[3] = [\"campo4\",\"caminhao\"];\n\
							tabela[4] = [\"radio1\",\"1\"];\n\
							*/
		/************/
		
		printf ("		var indice1,indice2;\n");
		printf ("		\n");
		printf ("		for(indice1 = 0 ;indice1 < %i;indice1 ++)\n",indice1);
		printf ("		{\n");
		printf ("			for(indice2 = 0;indice2 < form.elements.length; indice2 ++)\n");
		printf ("			{\n");
		printf ("				if(form.elements[indice2].name == tabela[indice1][0])\n");
		printf ("				{\n");
		printf ("					if((form.elements[indice2].type == \"text\") || (form.elements[indice2].type == \"textarea\") || (form.elements[indice2].type == \"select-one\"))\n");
		printf ("						form.elements[indice2].value = tabela[indice1][1];\n");
		printf ("					\n");
		printf ("					if((form.elements[indice2].type == \"radio\")||(form.elements[indice2].type == \"checkbox\"))\n");
		printf ("						if(form.elements[indice2].value == tabela[indice1][1])\n");
		printf ("							form.elements[indice2].click();\n");
		printf ("				}\n");
		printf ("			}\n");
		printf ("		}\n");
		printf ("	}\n");
		printf ("	\n");

	/*******************************************************************************************************************************************************************************************/
	printf ("	</script>\n");
	printf ("</head>\n");
	printf ("\n");
	printf ("<body onLoad=\"inicializaOcultos('tabelaGenpoint'); preencherCampos(check);\">\n");

	showMenu("consulta",username);

	printf ("<div align=\"center\">\n");
	printf ("<form name=\"check\" id=\"form\" method=\"post\" action=\"historico.py\" onSubmit=\"return validar_consulta_medica(this)\">\n");
	printf ("\n");
	printf ("	<span style=\"font-size: 13pt\" class=\"bold\"><br />Projeto - Novos M&eacute;todos Diagn&oacute;sicos em TB pulmonar - Policlinica Augusto Amaral Peixoto - SMS - RJ</span>\n");
	printf ("	<div align=\"center\">\n");
	printf ("		<br /><br />\n");
	printf ("	<!-- --><input type=\"hidden\" name=\"form\" value=\"consultaMedica\" />\n");
	printf ("	<!-- --><div class=\"h4\"><b><script>document.write(tabFields[39][1]);</script><input name=\"pid\" size=\"6\" type=\"text\" value=\"%s\" readonly=\"readonly\"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n",translate_escape_character_xsl(numeroGeral));
	printf ("		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
	printf ("		<script>document.write(tabFields[40][1]);</script><input maxlength=\"2\" size=\"2\" name=\"dia_inclusao\" onKeyUp=\"if(this.value.length == 2)mes_inclusao.focus();\" onBlur=\"validarDia(this);\">&nbsp;/\n");
	printf ("											<input maxlength=\"2\" size=\"2\" name=\"mes_inclusao\" onKeyUp=\"if(this.value.length == 2)ano_inclusao.focus();\" onBlur=\"validarMes(this);\">&nbsp;/\n");
	printf ("											<input maxlength=\"4\" size=\"4\" name=\"ano_inclusao\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onBlur=\"validarAno(this);validarQualquerData(dia_inclusao,mes_inclusao,ano_inclusao);\">&nbsp; dd/mm/aaaa<br><br>\n");
	printf ("\n");
	printf ("	<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" class=\"tabela\" id=\"tabelaGenpoint\">\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td colspan=\"4\" class=\"label\"><b>Consulta M&eacute;dica</b></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- TRATAMENTO ANTERIOR PARA TB -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[7][1]);</script></td>\n");
	printf ("		<td><input name=\"tratamentoAnteriorTB\" type=\"radio\" value=\"sim\" onClick=\"habilitarRadio(inh,3);habilitarRadio(rif,3);qualEsquema.disabled = false;exibeLinhaOculta('tabelaGenpoint', 2);exibeLinhaOculta('tabelaGenpoint', 3);exibeLinhaOculta('tabelaGenpoint', 4)\"> Sim</td>\n");
	printf ("		<td><input name=\"tratamentoAnteriorTB\" type=\"radio\" value=\"nao\" onClick=\"desabilitarRadio(inh,3);desabilitarRadio(rif,3);qualEsquema.disabled = true;ocultaLinha('tabelaGenpoint', 2);ocultaLinha('tabelaGenpoint', 3);ocultaLinha('tabelaGenpoint', 4)\">N&atilde;o</td>\n");
	printf ("		<td><input name=\"tratamentoAnteriorTB\" type=\"radio\" value=\"ignorado\" onClick=\"desabilitarRadio(inh,3);desabilitarRadio(rif,3);qualEsquema.disabled = true;ocultaLinha('tabelaGenpoint', 2);ocultaLinha('tabelaGenpoint', 3);ocultaLinha('tabelaGenpoint', 4)\"> Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- INH -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[8][1]);</script></td>\n");
	printf ("		<td><input name=\"inh\" type=\"radio\" value=\"sim\" disabled=\"sim\" >Sim</td>\n");
	printf ("		<td><input name=\"inh\" type=\"radio\" value=\"nao\" disabled=\"sim\" >N&atilde;o</td>\n");
	printf ("		<td><input name=\"inh\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- RIF -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[9][1]);</script></td>\n");
	printf ("		<td><input name=\"rif\" type=\"radio\" value=\"sim\" disabled=\"sim\" >Sim</td>\n");
	printf ("		<td><input name=\"rif\" type=\"radio\" value=\"nao\" disabled=\"sim\" >N&atilde;o</td>\n");
	printf ("		<td><input name=\"rif\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- ESQUEMA -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[10][1]);</script></td>\n");
	printf ("		<td colspan=\"3\"><input name=\"qualEsquema\" type=\"text\" size=\"40\" maxlength=\"200\" disabled=\"sim\" ></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td colspan=\"4\" class=\"label\"><b>Quimioprofilaxia Pr&eacute;via para TB:</b></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- QUIMIOPROFILAXIA -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[11][1]);</script></td>\n");
	printf ("		<td><input name=\"quimioprofilaxia\" type=\"radio\" value=\"sim\" onClick=\"mes_quimio.disabled = false ;ano_quimio.disabled = false; habilitarRadio(inhCagePositivo,3);habilitarRadio(rifCagePositivo,3);habilitarRadio(desfechoQuimio,3);exibeLinhaOculta('tabelaGenpoint', 8);exibeLinhaOculta('tabelaGenpoint', 9);exibeLinhaOculta('tabelaGenpoint', 10);exibeLinhaOculta('tabelaGenpoint', 11)\">Sim</td>\n");
	printf ("		<td><input name=\"quimioprofilaxia\" type=\"radio\" value=\"nao\" onClick=\"mes_quimio.disabled = true ;ano_quimio.disabled = true;desabilitarRadio(inhCagePositivo,3);desabilitarRadio(rifCagePositivo,3);desabilitarRadio(desfechoQuimio,3);ocultaLinha('tabelaGenpoint', 8); ocultaLinha('tabelaGenpoint', 9); ocultaLinha('tabelaGenpoint', 10); ocultaLinha('tabelaGenpoint', 11)\">N&atilde;o</td>\n");
	printf ("		<td><input name=\"quimioprofilaxia\" type=\"radio\" value=\"ignorado\" onClick=\"mes_quimio.disabled = true ;ano_quimio.disabled = true;desabilitarRadio(inhCagePositivo,3);desabilitarRadio(rifCagePositivo,3);desabilitarRadio(desfechoQuimio,3);ocultaLinha('tabelaGenpoint', 8); ocultaLinha('tabelaGenpoint', 9); ocultaLinha('tabelaGenpoint', 10); ocultaLinha('tabelaGenpoint', 11)\">Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!--  CAGE POSITIVO  -->\n");
	printf ("\n");
	/*
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[12][1]);</script>:</td>\n");
	printf ("		<td colspan=\"3\"><input  name=\"cagePositivo\" type=\"text\" value=\"%s\" readonly=\"readonly\">",cagePositivo);
	printf ("	</tr>\n");
	*/
	printf ("	<tr class=\"impar\">\n");
	/*
	printf ("		<td><script>document.write(tabFields[12][1]);</script></td>\n");
	printf ("		<td><input  name=\"cagePositivo\" type=\"radio\" value=\"sim\" onClick=\"mes_quimio.disabled = false ;ano_quimio.disabled = false; habilitarRadio(inhCagePositivo,3);habilitarRadio(rifCagePositivo,3);habilitarRadio(desfechoQuimio,3);exibeLinhaOculta('tabelaGenpoint', 8);exibeLinhaOculta('tabelaGenpoint', 9);exibeLinhaOculta('tabelaGenpoint', 10);exibeLinhaOculta('tabelaGenpoint', 11)\">Sim</td>\n");
	printf ("		<td><input  name=\"cagePositivo\" type=\"radio\" value=\"nao\" onClick=\"mes_quimio.disabled = true ;ano_quimio.disabled = true;desabilitarRadio(inhCagePositivo,3);desabilitarRadio(rifCagePositivo,3);desabilitarRadio(desfechoQuimio,3);ocultaLinha('tabelaGenpoint', 8); ocultaLinha('tabelaGenpoint', 9); ocultaLinha('tabelaGenpoint', 10); ocultaLinha('tabelaGenpoint', 11)\">N&atilde;o</td>\n");
	printf ("		<td><input  name=\"cagePositivo\" type=\"radio\" value=\"ignorado\" onClick=\"mes_quimio.disabled = true ;ano_quimio.disabled = true;desabilitarRadio(inhCagePositivo,3);desabilitarRadio(rifCagePositivo,3);desabilitarRadio(desfechoQuimio,3);ocultaLinha('tabelaGenpoint', 8); ocultaLinha('tabelaGenpoint', 9); ocultaLinha('tabelaGenpoint', 10); ocultaLinha('tabelaGenpoint', 11)\">Ignorado</td>\n");
	*/
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- INH -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[13][1]);</script></td>\n");
	printf ("		<td><input name=\"inhCagePositivo\" type=\"radio\" value=\"sim\" disabled=\"sim\" >Sim</td>\n");
	printf ("		<td><input name=\"inhCagePositivo\" type=\"radio\" value=\"nao\" disabled=\"sim\" >N&atilde;o</td>\n");
	printf ("		<td><input name=\"inhCagePositivo\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- RIF -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[14][1]);</script></td>\n");
	printf ("		<td><input name=\"rifCagePositivo\" type=\"radio\" value=\"sim\" disabled=\"sim\" >Sim</td>\n");
	printf ("		<td><input name=\"rifCagePositivo\" type=\"radio\" value=\"nao\" disabled=\"sim\" >N&atilde;o</td>\n");
	printf ("		<td><input name=\"rifCagePositivo\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- DATA DA QUIMIOPROFILAXIA -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[15][1]);</script></td>\n");
	printf ("		<td colspan=\"3\"><input name=\"mes_quimio\" type=\"text\" maxlength=\"2\" size=\"2\" disabled=\"sim\" onKeyUp=\"if(this.value.length == 2)ano_quimio.focus();\" onBlur=\"validarMes(this);\"> (m&ecirc;s) / <input name=\"ano_quimio\" type=\"text\" maxlength=\"4\" size=\"4\" disabled=\"sim\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onBlur=\"validarAno(this);validarQualquerData(1,mes_quimio,ano_quimio);\"> (ano)</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- DESFECHO -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[16][1]);</script></td>\n");
	printf ("		<td><input name=\"desfechoQuimio\" type=\"radio\" value=\"completou\" disabled=\"sim\" >Completou</td>\n");
	printf ("		<td><input name=\"desfechoQuimio\" type=\"radio\" value=\"abandonou\" disabled=\"sim\" >Abandonou</td>\n");
	printf ("		<td><input name=\"desfechoQuimio\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td class=\"label\" colspan=\"4\"><b>HIV/AIDS:</b></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- HIV TESTE -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[17][1]);</script></td>\n");
	printf ("		<td><input name=\"testeHIV\" type=\"radio\" value=\"positivo\" onClick=\"dia_antihiv.disabled = false; mes_antihiv.disabled = false; ano_antihiv.disabled = false;\">Positivo</td>\n");
	printf ("		<td><input name=\"testeHIV\" type=\"radio\" value=\"negativo\" onClick=\"dia_antihiv.disabled = false; mes_antihiv.disabled = false; ano_antihiv.disabled = false;\">Negativo</td>\n");
	printf ("		<td><input name=\"testeHIV\" type=\"radio\" value=\"ignorado\" onClick=\"dia_antihiv.disabled = true; mes_antihiv.disabled = true; ano_antihiv.disabled = true;\">N&atilde;o realizado/<br>Resultado desconhecido</br></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- DATA ANTI-HIV -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[18][1]);</script></td>\n");
	printf ("		<td colspan=\"3\"><input name=\"dia_antihiv\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)mes_antihiv.focus();\" onBlur=\"validarDia(this);\"> / <input name=\"mes_antihiv\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)ano_antihiv.focus();\" onBlur=\"validarMes(this);\"> / <input name=\"ano_antihiv\" type=\"text\" maxlength=\"4\" size=\"4\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onBlur=\"validarAno(this);validarQualquerData(dia_antihiv,mes_antihiv,ano_antihiv);\"></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- COMORBIDADES -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">	\n");
	printf ("		<td><script>document.write(tabFields[38][1])</script></td>\n");
	printf ("		<td><input name=\"comorbidade\" type=\"radio\" value=\"sim\" onClick=\"habilitarRadio(comorbidades,12);exibeLinhaOculta('tabelaGenpoint', 16);exibeLinhaOculta('tabelaGenpoint', 17);exibeLinhaOculta('tabelaGenpoint', 18);exibeLinhaOculta('tabelaGenpoint', 19);\">Sim</td>\n");
	printf ("		<td><input name=\"comorbidade\" type=\"radio\" value=\"nao\" onClick=\"desabilitarRadio(comorbidades,12);ocultaLinha('tabelaGenpoint', 16);ocultaLinha('tabelaGenpoint', 17);ocultaLinha('tabelaGenpoint', 18);ocultaLinha('tabelaGenpoint', 19);\">N&atilde;o</td>\n");
	printf ("		<td><input name=\"comorbidade\" type=\"radio\" value=\"ignorado\" onClick=\"desabilitarRadio(comorbidades,12);ocultaLinha('tabelaGenpoint', 16);ocultaLinha('tabelaGenpoint', 17);ocultaLinha('tabelaGenpoint', 18);ocultaLinha('tabelaGenpoint', 19);\">Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td></td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"doenca_renal_cronica\">Doen&ccedil;a Renal Cl&iacute;nica</td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"hepatopatia\">Hepatopatia</td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"alcoolismo\">Alcoolismo</td>\n");
	printf ("	</tr>\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td></td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"cortidoides\">Uso Cortic&oacute;ides</td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"neoplasia\">Neoplasia Maligna</td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"transplante\">Transplante</td>\n");
	printf ("	</tr>\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td></td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"dmnid\">DMNID</td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"dmid\">DMID</td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"silicose\">Silicose</td>\n");
	printf ("	</tr>\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td></td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"dpoc\">DPOC</td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"doenca_pulmonar_difusa\">Doen&ccedil;a Pulmonar Difusa</td>\n");
	printf ("		<td><input name=\"comorbidades\" type=\"checkbox\" disabled=\"true\" value=\"outras\" onClick=\"if(this.checked){outrascomorbidades.disabled = false;outrascomorbidades.focus();}else{outrascomorbidades.disabled = true}\">Outras:&nbsp;<input name=\"outrascomorbidades\" type=\"text\" size=\"8\" maxlength=\"100\" disabled=\"true\"></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td  class=\"label\" colspan=\"4\"><b>Avalia&ccedil;&atilde;o Cl&iacute;nica:</b></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- PROBABILIDADE TB ATIVA -->\n");
	printf ("\n");
	printf ("	<!-- Exame Fisico -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[19][1]);</script></td>\n");
	printf ("		<td><input name=\"exameFisico\" type=\"radio\" value=\"sim\" onClick=\"alteracoesNoExameFisico.disabled = true; ocultaLinha('tabelaGenpoint', 22)\">Sim</td>\n");
	printf ("		<td><input name=\"exameFisico\" type=\"radio\" value=\"nao\" onClick=\"alteracoesNoExameFisico.disabled = false;exibeLinhaOculta('tabelaGenpoint', 22)\">N&atilde;o</td>\n");
	printf ("		<td><input name=\"exameFisico\" type=\"radio\" value=\"ignorado\" onClick=\"alteracoesNoExameFisico.disabled = true;ocultaLinha('tabelaGenpoint', 22)\">Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[20][1]);</script></td>\n");
	printf ("		<td colspan=\"3\"><input name=\"alteracoesNoExameFisico\" type=\"text\" size=\"70\" disabled=\"sim\" > </td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[21][1]);</script></td>\n");
	printf ("		<td><input name=\"probTBativa\" type=\"radio\" value=\"alta\">alta (>75%%)</td>\n");
	printf ("		<td><input name=\"probTBativa\" type=\"radio\" value=\"media\">m&eacute;dia (entre 25%% e 75%%)</td>\n");
	printf ("		<td><input name=\"probTBativa\" type=\"radio\" value=\"baixa\">baixa (<25%%)</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- PROBABILIDADE DE TB SEM RX E BAAR -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td colspan=\"3\" class=\"wrap\"><script>document.write(tabFields[22][1]);</script></td>\n");
	printf ("		<td><input name=\"porcentagemProbTBsemRXsemBAAR\" type=\"text\" maxlength=\"3\" size=\"2\" onBlur=\"validarCampoNumerico(this);validarPorcentagem(this)\"> %%</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td  class=\"label\" colspan=\"4\"><b>RX de t&oacute;rax (ao entrar no estudo):</b></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!--PROBABILIDADE TB ATIVA COM RX -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[23][1]);</script></td>\n");
	printf ("		<td><input name=\"probTBativaComRX\" type=\"radio\" value=\"alta\" onClick=\"nsa.disabled = false; desabilitarRadio(casoBaixaProbabilidade,5); habilitarRadio(cavitacao,3); habilitarRadio(padraoTipico,3); habilitarRadio(compativel,3); habilitarRadio(atipico,3);exibeLinhaOculta('tabelaGenpoint', 27);exibeLinhaOculta('tabelaGenpoint', 28);exibeLinhaOculta('tabelaGenpoint', 29);exibeLinhaOculta('tabelaGenpoint', 30);exibeLinhaOculta('tabelaGenpoint', 31);ocultaLinha('tabelaGenpoint', 32);ocultaLinha('tabelaGenpoint', 33)\">alta</td>\n");
	printf ("		<td><input name=\"probTBativaComRX\" type=\"radio\" value=\"media\" onClick=\"nsa.disabled = false; desabilitarRadio(casoBaixaProbabilidade,5); habilitarRadio(cavitacao,3); habilitarRadio(padraoTipico,3); habilitarRadio(compativel,3); habilitarRadio(atipico,3);exibeLinhaOculta('tabelaGenpoint', 27);exibeLinhaOculta('tabelaGenpoint', 28);exibeLinhaOculta('tabelaGenpoint', 29);exibeLinhaOculta('tabelaGenpoint', 30);exibeLinhaOculta('tabelaGenpoint', 31);ocultaLinha('tabelaGenpoint', 32);ocultaLinha('tabelaGenpoint', 33)\">m&eacute;dia</td>\n");
	printf ("		<td><input name=\"probTBativaComRX\" type=\"radio\" value=\"baixa\" onClick=\"nsa.disabled = true; habilitarRadio(casoBaixaProbabilidade,5); desabilitarRadio(cavitacao,3); desabilitarRadio(padraoTipico,3); desabilitarRadio(compativel,3); desabilitarRadio(atipico,3);ocultaLinha('tabelaGenpoint', 27);ocultaLinha('tabelaGenpoint', 28);ocultaLinha('tabelaGenpoint', 29);ocultaLinha('tabelaGenpoint', 30);ocultaLinha('tabelaGenpoint', 31);exibeLinhaOculta('tabelaGenpoint', 32);exibeLinhaOculta('tabelaGenpoint', 33)\">baixa</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- CAVITACAO -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[24][1]);</script></td>\n");
	printf ("		<td><input name=\"cavitacao\" type=\"radio\" value=\"sim\" disabled=\"sim\" >Sim</td>\n");
	printf ("		<td><input name=\"cavitacao\" type=\"radio\" value=\"nao\" disabled=\"sim\" >N&atilde;o</td>\n");
	printf ("		<td><input name=\"cavitacao\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- PADRAO TIPICO -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td class=\"wrap\"><script>document.write(tabFields[25][1]);</script></td>\n");
	printf ("		<td><input name=\"padraoTipico\" type=\"radio\" value=\"sim\" disabled=\"sim\" >Sim</td>\n");
	printf ("		<td><input name=\"padraoTipico\" type=\"radio\" value=\"nao\" disabled=\"sim\" >N&atilde;o</td>\n");
	printf ("		<td><input name=\"padraoTipico\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- COMPATIVEL -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td class=\"wrap\"><script>document.write(tabFields[26][1]);</script></td>\n");
	printf ("		<td><input name=\"compativel\" type=\"radio\" value=\"sim\" disabled=\"sim\" >Sim</td>\n");
	printf ("		<td><input name=\"compativel\" type=\"radio\" value=\"nao\" disabled=\"sim\" >N&atilde;o</td>\n");
	printf ("		<td><input name=\"compativel\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- ATIPICO -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[27][1]);</script></td>\n");
	printf ("		<td><input name=\"atipico\" type=\"radio\" value=\"sim\" disabled=\"sim\" >Sim</td>\n");
	printf ("		<td><input name=\"atipico\" type=\"radio\" value=\"nao\" disabled=\"sim\" >N&atilde;o</td>\n");
	printf ("		<td><input name=\"atipico\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- NSA -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td></td>\n");
	printf ("		<td colspan=\"3\"><input name=\"nsa\" type=\"checkbox\" value=\"nsa\" disabled=\"sim\" >NSA</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- CASO DE BAIXA PRIORIDADE -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[29][1]);</script>\n");
	printf ("		<td colspan=\"2\"><input name=\"casoBaixaProbabilidade\" type=\"radio\" value=\"inativa\" disabled=\"sim\" >TB inativa/seq&uuml;ela</br</td>\n");
	printf ("		<td><input name=\"casoBaixaProbabilidade\" type=\"radio\" value=\"outra_doenca\" disabled=\"sim\" >Outra doen&ccedil;a</td>\n");
	printf ("	</tr>\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td></td>\n");
	printf ("		<td><input name=\"casoBaixaProbabilidade\" type=\"radio\" value=\"normal\" disabled=\"sim\" >Normal</td>\n");
	printf ("		<td><input name=\"casoBaixaProbabilidade\" type=\"radio\" value=\"ignorado\" disabled=\"sim\" >Ignorado</td>\n");
	printf ("		<td><input name=\"casoBaixaProbabilidade\" type=\"radio\" value=\"nsa\" disabled=\"sim\" >NSA</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- DATA DO RX -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[30][1]);</script></td>\n");
	printf ("		<td colspan=\"3\"><input name=\"dia_rx\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onBlur=\"if(validarDia(this))mes_rx.focus();\">/<input name=\"mes_rx\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onBlur=\"if(validarMes(this))ano_rx.focus();\">/<input name=\"ano_rx\" type=\"text\" maxlength=\"4\" size=\"4\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onBlur=\"validarAno(this);validarQualquerData(dia_rx,mes_rx,ano_rx);\"></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- PROBABILIDADE COM RX SEM RESULTADOS BACTERIOLOGICOS -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td class=\"wrap\"><script>document.write(tabFields[31][1]);</script></td>\n");
	printf ("		<td colspan=\"3\">\n");
	printf ("			<p><input name=\"diagnosticoProbabilidadeRX\" type=\"radio\" value=\"alta_prob\">Alta probabilidade de TB Pulmonar ativa; (>75%%)</p>\n");
	printf ("			<p><input name=\"diagnosticoProbabilidadeRX\" type=\"radio\" value=\"media_prob\">M&eacute;dia probabilidade de TB Pulmonar ativa; (entre 25%% e 75%%)</p>\n");
	printf ("			<p><input name=\"diagnosticoProbabilidadeRX\" type=\"radio\" value=\"baixa_prob\">Baixa probabilidade de TB Pulmonar ativa; (<25%%)</p>\n");
	printf ("			<p><input name=\"diagnosticoProbabilidadeRX\" type=\"radio\" value=\"ignorado\">Ignorado</p>\n");
	printf ("		</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- PROBABILIDADE DE TB COM RX E SEM BAAR -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td class=\"wrap\"><script>document.write(tabFields[32][1]);</script></td>\n");
	printf ("		<td colspan=\"3\"><input name=\"probabilidadeTBcomRXsemBAAR\" type=\"text\" maxlength=\"3\" size=\"2\" onBlur=\"validarCampoNumerico(this);validarPorcentagem(this)\"> %%</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- RESULTADO DA BACILOSCOPIA -->\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td class=\"label\" align=\"left\" colspan=\"4\"><b>Resultado da Baciloscopia:</b></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td align=\"left\"><script>document.write(tabFields[43][1]);</script></td>\n");
	printf ("		<td><input name=\"resultadoBaciloscopia1\" type=\"radio\" value=\"positivo\" onClick=\"habilitarRadio(casoPositivo1,3);exibeLinhaOculta('tabelaGenpoint', 39)\">Positivo</td>\n");
	printf ("		<td><input name=\"resultadoBaciloscopia1\" type=\"radio\" value=\"negativo\" onClick=\"desabilitarRadio(casoPositivo1,3);ocultaLinha('tabelaGenpoint', 39)\">Negativo</td>\n");
	printf ("		<td><input name=\"resultadoBaciloscopia1\" type=\"radio\" value=\"N&atilde;o_realizado\" onClick=\"desabilitarRadio(casoPositivo1,3);ocultaLinha('tabelaGenpoint', 39)\">N&atilde;o realizado/<br>Resultado desconhecido</br></td>\n");
	printf ("	</tr>\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("\n");
	printf ("		<td align=\"left\"><script>document.write(tabFields[44][1]);</script></td>\n");
	printf ("		<td><input name=\"casoPositivo1\" type=\"radio\" value=\"+\" disabled=\"sim\" >+</td>\n");
	printf ("		<td><input name=\"casoPositivo1\" type=\"radio\" value=\"++\" disabled=\"sim\" >++</td>\n");
	printf ("		<td><input name=\"casoPositivo1\" type=\"radio\" value=\"+++\" disabled=\"sim\" >+++</td>\n");
	printf ("	</tr>\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td align=\"left\"><script>document.write(tabFields[45][1]);</script></td>\n");
	printf ("		<td><input name=\"resultadoBaciloscopia2\" type=\"radio\" value=\"positivo\" onClick=\"habilitarRadio(casoPositivo2,3);exibeLinhaOculta('tabelaGenpoint', 41)\">Positivo</td>\n");
	printf ("		<td><input name=\"resultadoBaciloscopia2\" type=\"radio\" value=\"negativo\" onClick=\"desabilitarRadio(casoPositivo2,3);ocultaLinha('tabelaGenpoint', 41)\">Negativo</td>\n");
	printf ("		<td><input name=\"resultadoBaciloscopia2\" type=\"radio\" value=\"N&atilde;o_realizado\" onClick=\"desabilitarRadio(casoPositivo2,3);ocultaLinha('tabelaGenpoint', 41)\">N&atilde;o realizado/<br>Resultado desconhecido</br></td>\n");
	printf ("	</tr>\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td align=\"left\"><script>document.write(tabFields[46][1]);</script></td>\n");
	printf ("		<td><input name=\"casoPositivo2\" type=\"radio\" value=\"+\" disabled=\"sim\" >+</td>\n");
	printf ("		<td><input name=\"casoPositivo2\" type=\"radio\" value=\"++\" disabled=\"sim\" >++</td>\n");
	printf ("		<td><input name=\"casoPositivo2\" type=\"radio\" value=\"+++\" disabled=\"sim\" >+++</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- DUAS BACILOSCOPIAS NEGATIVAS -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td class=\"wrap\"><script>document.write(tabFields[33][1]);</script></td>\n");
	printf ("		<td colspan=\"3\">\n");
	printf ("			<p><input name=\"diagnosticoProbabilidadeCasoDuasNegativas\" type=\"radio\" value=\"alta_prob\">Alta probabilidade de TB Pulmonar ativa; (>75%%)</p>\n");
	printf ("			<p><input name=\"diagnosticoProbabilidadeCasoDuasNegativas\" type=\"radio\" value=\"media_prob\">M&eacute;dia probabilidade de TB Pulmonar ativa; (entre 25%% e 75%%)</p>\n");
	printf ("			<p><input name=\"diagnosticoProbabilidadeCasoDuasNegativas\" type=\"radio\" value=\"baixa_prob\">Baixa probabilidade de TB Pulmonar ativa; (<25%%)</p>\n");
	printf ("			<p><input name=\"diagnosticoProbabilidadeCasoDuasNegativas\" type=\"radio\" value=\"ignorado\">Ignorado</p>\n");
	printf ("		</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- PROBABILIDADE DE TB COM RX E BAAR -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td class=\"wrap\"><script>document.write(tabFields[34][1]);</script></td>\n");
	printf ("		<td colspan=\"3\"><input name=\"probabilidadeTBcomRXcomBAAR\" type=\"text\" maxlength=\"3\" size=\"2\" onBlur=\"validarCampoNumerico(this);validarPorcentagem(this)\"> %%</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- DESFECHO DA CONSULTA INICIAL -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[35][1]);</script></td>\n");
	printf ("		<td colspan=\"3\">\n");
	printf ("			<input name=\"desfechoConsultaInicial\" type=\"radio\" value=\"tb_confirmacao\" onClick=\"habilitarRadio(casoTratamentoTB,4) ;habilitarRadio(fatoresRisco,3) ;exibeLinhaOculta('tabelaGenpoint', 45);exibeLinhaOculta('tabelaGenpoint', 46);exibeLinhaOculta('tabelaGenpoint', 47)\">Tratamento para TB com confirma&ccedil;&atilde;o bacteriol&oacute;gica;\n");
	printf ("			<p><input name=\"desfechoConsultaInicial\" type=\"radio\" value=\"tb_probabilidade\" onClick=\"habilitarRadio(casoTratamentoTB,4) ;habilitarRadio(fatoresRisco,3) ;exibeLinhaOculta('tabelaGenpoint', 45);exibeLinhaOculta('tabelaGenpoint', 46);exibeLinhaOculta('tabelaGenpoint', 47)\">Tratamento para TB por probabilidade;</p>\n");
	printf ("			<p><input name=\"desfechoConsultaInicial\" type=\"radio\" value=\"pneumologia\" onClick=\"desabilitarRadio(casoTratamentoTB,4) ;desabilitarRadio(fatoresRisco,3) ;ocultaLinha('tabelaGenpoint', 45);ocultaLinha('tabelaGenpoint', 46);ocultaLinha('tabelaGenpoint', 47)\">Tratamento na pneumologia de outra patologia N&atilde;o TB;</p>\n");
	printf ("			<p><input name=\"desfechoConsultaInicial\" type=\"radio\" value=\"internacao\" onClick=\"desabilitarRadio(casoTratamentoTB,4) ;desabilitarRadio(fatoresRisco,3) ;ocultaLinha('tabelaGenpoint', 45);ocultaLinha('tabelaGenpoint', 46);ocultaLinha('tabelaGenpoint', 47)\">Transfer&ecirc;ncia para interna&ccedil;&atilde;o N&atilde;o por TB ou tratamento<br> em outra especialidade</br></p>\n");
	printf ("			<p><input name=\"desfechoConsultaInicial\" type=\"radio\" value=\"alta\" onClick=\"desabilitarRadio(casoTratamentoTB,4) ;desabilitarRadio(fatoresRisco,3) ;ocultaLinha('tabelaGenpoint', 45);ocultaLinha('tabelaGenpoint', 46);ocultaLinha('tabelaGenpoint', 47)\">Alta</p>\n");
	printf ("			<p><input name=\"desfechoConsultaInicial\" type=\"radio\" value=\"ignorado\" onClick=\"desabilitarRadio(casoTratamentoTB,4) ;desabilitarRadio(fatoresRisco,3) ;ocultaLinha('tabelaGenpoint', 45);ocultaLinha('tabelaGenpoint', 46);ocultaLinha('tabelaGenpoint', 47)\">Ignorado</p>\n");
	printf ("		</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- CASO TRATAMENTO imparA TB -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td><script>document.write(tabFields[36][1]);</script></td>\n");
	printf ("		<td colspan=\"3\" class=\"wrap\">\n");
	printf ("			<p><input name=\"casoTratamentoTB\" type=\"radio\" value=\"tb_virgem\" disabled=\"sim\" >TB pulmonar (TBP) virgem de tratamento (uso de medicamento &lt; 310 dias);\n");
	printf ("			<p><input name=\"casoTratamentoTB\" type=\"radio\" value=\"tb_recidiva\" disabled=\"sim\" >TB recidiva (completou tratamento tendo sido considerado curado);</p>\n");
	printf ("			<p><input name=\"casoTratamentoTB\" type=\"radio\" value=\"tb_retorno\" disabled=\"sim\" >TB retorno p&oacute;s-abandono (tratou e abandonou antes do t&eacute;rmino);</p>\n");
	printf ("			<p><input name=\"casoTratamentoTB\" type=\"radio\" value=\"tb_falencia\" disabled=\"sim\" >TB fal&ecirc;ncia(em tratamento com BAAR positivo ap&oacute;s 4 meses em paciente usando esquema RHZ ou RHZE ou ap&oacute;s 6 meses em paciente usando esquema alternativo: i.e.: SEEZ)</p>\n");
	printf ("		</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- FATORES DE RISCO imparA TBP MDR -->\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td><script>document.write(tabFields[37][1]);</script></td>\n");
	printf ("		<td><input name=\"fatoresRisco\" type=\"radio\" value=\"suspeita_recidiva\" disabled=\"sim\" >Suspeita de recidiva;</td>\n");
	printf ("		<td><input name=\"fatoresRisco\" type=\"radio\" value=\"suspeita_falencia\" disabled=\"sim\" >Suspeita de fal&ecirc;ncia;</td>\n");
	printf ("		<td><input name=\"fatoresRisco\" type=\"radio\" value=\"contato_intimo\" disabled=\"sim\" >Contato intimo de caso de TBP MDR.*</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr class=\"par\">\n");
	printf ("		<td></td>\n");
	printf ("		<td colspan=\"3\" class=\"wrap\">*(reside no mesmo domicilio, ou refere contato di&aacute;rio na comunidade pelo menos nos &uacute;ltimos tr&ecirc;s meses ou dividiu espa&ccedil;o f&iacute;sico na pris&atilde;o ou em hospital)</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!-- Observacoes -->\n");
	printf ("\n");
	printf ("	<tr class=\"impar\">\n");
	printf ("		<td colspan=\"1\"><script>document.write(tabFields[47][1]);</script></td>\n");
	printf ("		<td colspan=\"3\" align=\"center\"><div center><textarea name=\"observacoes\" rows=\"5\" cols=\"50\"></textarea></div></td>\n");
	printf ("	</tr>\n");
	printf ("�      <!-- Motivo para editar -->\n");
	printf ("\n");
	printf ("�      <tr class=\"par\">\n");
	printf ("�      �       <td colspan=\"1\"><script>document.write(tabFields[50][1]);</script></td>\n");
	printf ("�      �       <td colspan=\"3\" align=\"center\"><div center><textarea name=\"histMotivo\" rows=\"5\" cols=\"50\"></textarea></div></td>\n");
	printf ("�      </tr>\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td>&nbsp;</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td colspan=\"1\" style=\"text-align:center\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<script>document.write(tabFields[48][1]);</script><input name=\"avaliador\" type=\"text\"  size=\"25\"></td>\n");
	printf ("		<td colspan=\"3\" style=\"text-align:center\"><script>document.write(tabFields[49][1]);</script><input name=\"quemCadastrou\" type=\"text\" readonly=\"readonly\" value=\"%s\" size=\"25\"></td>\n",username);
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td>&nbsp;</td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	<!--    ENVIAR / Limpar     -->\n");
	printf ("\n");
	printf ("	<tr>\n");
	printf ("		<td><input value=\"Limpar Formul&aacute;rio\" type=\"reset\" onClick=\"inicializaOcultos('tabelaGenpoint')\"></td>\n");
	printf ("		<td></td>\n");
	printf ("		<td></td>\n");
	printf ("		<td style=\"text-align:right\"><input type=\"submit\" value=\"Enviar Formul&aacute;rio\"></td>\n");
	printf ("	</tr>\n");
	printf ("\n");
	printf ("	</table>\n");
	printf ("</form>\n");
	printf ("</div>\n");
	printf ("\n");
	printf ("</body>\n");
	
	printf ("<script language=\"JavaScript\">\n");
	printf ("emSubmissao = false; // ao tentar sair da pagina, eh preciso saber se estamos submetendo o formulario ou nao\n"); 
	printf ("window.onbeforeunload = checkGoToNewPage;\n");
	printf ("function checkGoToNewPage() {\n");
	printf ("	if ((!emSubmissao) && temAlgumCampoPreenchido(form)) {\n");
	printf ("		return \"Voce perdera todos os dados nao salvos se sair desta pagina.\";\n"); 
	printf ("	}\n");
	printf ("	else { emSubmissao=false; }\n");
	printf ("}\n");
	printf ("</script>\n");

	printf ("</html>\n");
	
	cgi_end();
	
	return 0;
}
/*
gcc -Wall -c ntbCgiFormEdit.c `xml2-config --cflags`
gcc -Wall -o formEdit.cgi ntbCgiFormEdit.o functions.o `xml2-config --libs` -Llibs/libcgi-1.0 -lcgi
mv -f formEdit.cgi ../formEdit.cgi
*/

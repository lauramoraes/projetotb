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
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

#include "cgi.h"
#include "functions.h"

#define XML_FILE_PATH "./xml/pacientesGuadalupe.xml"
#define USUARIO_ANONIMO "anonimo"

void usualFreeMemory (xmlDocPtr doc)
{
	if (doc)
		xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
}

int main (void)/*(int argc,char**argv)*/
{
	int indice1;
	char *username, *pid, fraseFinal[200],fraseFinal2[200];
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
	
	pid = cgi_param("pid");
	//username = cgi_param("uid");
	
		if(!(username= getenv("REMOTE_USER"))) //verifica se string lida � null
	  {
		printf("Content-type: text/html\n\n");
		printf("<html>\n");
		printf("<head>\n");
		printf("<title>Resultado</title>\n");
		printf("</head>\n");
		printf("<body>\n");
    printf("Erro ao verificar o usu�rio.");
		printf("</body>\n");
		printf("</html>\n");
		exit(0);
		}

	if(username == NULL)
		username = USUARIO_ANONIMO;
	
	// cgi_init_headers();
	// Funcao criada por Felipe para fazer com que o browser interprete o
	// HTML como utf-8.
	cgi_init_headers_with_content_type("text/html; charset=utf-8");

	/* HTML */
printf ("<html>\r\n");
printf ("<head>\r\n");
printf ("\r\n");
printf ("	<title>Follow Up 90 dias - Preencha todos os campos do Formul&aacute;rio abaixo.</title>\r\n");
printf ("	<link rel=\"stylesheet\" type=\"text/css\" href=\"css/main.css\">\r\n");
printf ("	<link rel=\"stylesheet\" type=\"text/css\" href=\"css/menu.css\">\r\n");
printf ("	<link rel=\"stylesheet\" type=\"text/css\" href=\"css/form_2.css\">\r\n");
printf ("	<script charset=\"ISO-8859-1\" language=javascript src=\"js/funcoes.js\"></script>\r\n");
printf ("	<script charset=\"ISO-8859-1\" language=javascript src=\"js/validar.js\"></script>\r\n");
printf ("<script>\r\n");
printf ("function validarDataDesconhecida(form)\r\n");
printf ("{\r\n");
printf ("	if(form.mudanca.checked)\r\n");
printf ("	{\r\n");
printf ("		form.mudanca_mes.value= \"XX\";\r\n");
printf ("		form.mudanca_ano.value= \"XXXX\";\r\n");
printf ("		form.mudanca_mes.readOnly= true;\r\n");
printf ("		form.mudanca_ano.readOnly= true;\r\n");
printf ("	}\r\n");
printf ("	else\r\n");
printf ("	{\r\n");
printf ("		form.mudanca_mes.value= '';\r\n");
printf ("		form.mudanca_ano.value= '';\r\n");
printf ("		form.mudanca_mes.readOnly= false;\r\n");
printf ("		form.mudanca_ano.readOnly= false;\r\n");
printf ("	}\r\n");
printf ("}\r\n");
printf ("</script>\r\n");
printf ("\r\n");
printf ("\r\n");
printf ("<script>\r\n");
printf ("\r\n");
printf ("tabFields= new Array(26);\r\n");
printf ("\r\n");
printf ("	tabFields[0] = [\"criterio_entrada\", \"01 - Crit&eacute;rio de entrada:\"];\r\n");
printf ("	tabFields[1] = [\"tratamento_prescrito\", \"02 - Tratamento prescrito para TB:\"];\r\n");
printf ("	tabFields[2] = [\"data_inicio\", \"02.1 -  Data do in&iacute;cio (dia/m&ecirc;s/ano):\"];\r\n");
printf ("	tabFields[3] = [\"farmacos\", \"02.2 - Farmacos utilizados:\"];\r\n");
printf ("	tabFields[4] = [\"obito\", \"04 - Houve &oacute;bito?\"];\r\n");
printf ("	tabFields[5] = [\"causa\", \"04.1 - Qual a causa?\"];\r\n");
printf ("	tabFields[6] = [\"mudanca_esquema\", \"05 - Mudan&ccedil;a de esquema de tratamento para TB?\"];\r\n");
printf ("	tabFields[7] = [\"mudanca\", \"05.1 - Data do in&iacute;cio (m&ecirc;s/ano):\"];\r\n");
printf ("	tabFields[8] = [\"motivo\", \"05.3 - Motivo:\"];\r\n");
printf ("	tabFields[9] = [\"tosse\", \"06 - Tosse diminu&iacute;da:\"];\r\n");
printf ("	tabFields[10] = [\"peso_atual\", \"07 - Peso atual(kg):\"];\r\n");
printf ("	tabFields[11] = [\"prob_tb_ativa_avaliacao_rx\", \"09 - Probabilidade de TB ativa ao avaliar o RXT:\"];\r\n");
printf ("	tabFields[12] = [\"cavitacao\", \"09.1 - Cavita&ccedil;&atilde;o\"];\r\n");
printf ("	tabFields[13] = [\"padrao_tipico\", \"09.2 - Padr&atilde;o t&oacute;pico (infiltrado em lobo(s) superior(es) e/ou segmento apical de lobo inferior):\"];\r\n");
printf ("	tabFields[14] = [\"compativel\", \"09.3 - Compat&iacute;vel (alargamento mediastinal ou linf.  hilar , padr&atilde;o miliar,ou derrame pleural):\"];\r\n");
printf ("	tabFields[15] = [\"atipico\", \"09.4 - At&iacute;pico (qualquer outro padr&atilde;o):\"];\r\n");
printf ("	tabFields[16] = [\"nsa\", \"\"];\r\n");
printf ("	tabFields[17] = [\"baixa_prioridade\", \"09.1 - Em caso de baixa probabilidade de TB ativa responda:\"];\r\n");
printf ("	tabFields[18] = [\"data_rx\", \"10 - Data do RX:\"];\r\n");
printf ("	tabFields[19] = [\"follow_up\", \"11 - Follow up do RX de T&oacute;rax (compare com o RXT inicial como o atual):\"];\r\n");
printf ("	tabFields[20] = [\"hiv_teste\", \"12 - HIV teste:\"];\r\n");
printf ("	tabFields[21] = [\"antihiv\", \"13 - Data do Anti-HIV(dia/m&ecirc;s/ano):\"];\r\n");
printf ("	tabFields[22] = [\"diagnostico_90dias\", \"14 - Diagn&oacute;stico 90 dias:\"];\r\n");
printf ("	tabFields[23] = [\"outro_diagnostico\", \"14.1 - Em caso de outro Diagn&oacute;stico diferente de TB:\"];\r\n");
printf ("	tabFields[24] = [\"diagnostico_final\", \"15 - Realizado por dois investigadores ap&oacute;s revis&atilde;o dos dados eresultados de exames (an&aacute;lise deve ser realizada as cegas):\"];\r\n");
printf ("	tabFields[25] = [\"reacoes_adversas\", \"03 - Rea&ccedil;&atilde;o adversa dos tuberculost&aacute;ticos?\"];\r\n");
printf ("	tabFields[26] = [\"maiores\", \"03.1 - Maiores:\"];\r\n");
printf ("	tabFields[27] = [\"menores\", \"03.2 - Menores:\"];\r\n");
printf ("	tabFields[28] = [\"farmacos\", \"05.2 - F&aacute;rmacos utilizados:\"];\r\n");
printf ("	tabFields[29] = [\"Alteracoes_no_exame_fisico\", \"08 - Altera&ccedil;&otilde;es evolutivas no exame f&iacute;sico:\"];\r\n");
printf ("\r\n");
printf ("	var tabValores= new Array(\"Masculino\", \"Feminino\", \"Presente\", \"Ausente\", \"Ignorado\",\"Sim\", \"N&atilde;o\", \"Branco\", \"N&atilde;o-branco\", \"Negro\", \"Mulato\", \"&Iacute;ndio\", \"Asi&aacute;tico\", \"Outro\", \"Casado\", \"Solteiro\", \"Separado\", \"Vi&uacute;vo\", \"Pulm&atilde;o\", \"Pleura\", \"Ganglio\");\r\n");
printf ("\r\n");
printf ("function inicializaOcultos(tabela)\r\n");
printf ("\r\n");
printf ("{\r\n");
printf ("	document.getElementById(tabela).rows[3].style.display = \"none\";//data de inicio\r\n");
printf ("	document.getElementById(tabela).rows[4].style.display = \"none\";//farmacos\r\n");
printf ("	document.getElementById(tabela).rows[6].style.display = \"none\";//maiores\r\n");
printf ("	document.getElementById(tabela).rows[7].style.display = \"none\";//menores\r\n");
printf ("	document.getElementById(tabela).rows[9].style.display = \"none\";//causa do obito\r\n");
printf ("	document.getElementById(tabela).rows[11].style.display = \"none\";//data da mudanca\r\n");
printf ("	document.getElementById(tabela).rows[12].style.display = \"none\";//farmacos\r\n");
printf ("	document.getElementById(tabela).rows[13].style.display = \"none\";//farmacos\r\n");
printf ("	document.getElementById(tabela).rows[14].style.display = \"none\";//farmacos\r\n");
printf ("	document.getElementById(tabela).rows[15].style.display = \"none\";//motivo\r\n");
printf ("	document.getElementById(tabela).rows[22].style.display = \"none\";//cavitacao\r\n");
printf ("	document.getElementById(tabela).rows[23].style.display = \"none\";//padrao tipico\r\n");
printf ("	document.getElementById(tabela).rows[24].style.display = \"none\";//compativel\r\n");
printf ("	document.getElementById(tabela).rows[25].style.display = \"none\";//atipico\r\n");
printf ("	document.getElementById(tabela).rows[26].style.display = \"none\";//nsa\r\n");
printf ("	document.getElementById(tabela).rows[27].style.display = \"none\";//baixa probabilidade\r\n");
printf ("	document.getElementById(tabela).rows[28].style.display = \"none\";//baixa probabilidade\r\n");
printf ("	document.getElementById(tabela).rows[36].style.display = \"none\";//diagnostico diferente de tb\r\n");
printf ("}\r\n");
printf ("\r\n");
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

		doc = xmlReadFile(XML_FILE_PATH, NULL, 256);
		if (doc == NULL)
		{
			usualFreeMemory(NULL);
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
		printf ("\t\ttabela[0] = [\"%s\",\"%s\"];\n", cur_node_children->name, cur_node_children->children->content);		//Coloca a primeira posicao da tabela como Numero Geral

		/*
			saindo deste lup, teremos o noh do paciente que procuramos em cur_node
		*/
		
		if(cur_node != NULL)
		{
			cur_node = cur_node->children;
		
			while ((!xmlStrEqual(cur_node->name, BAD_CAST "followUp")) && (cur_node))
					cur_node = cur_node->next;
		}

		if(!cur_node) //MENSAGEM DE ERRO
		{
			printf("</script></head><body>Paciente n�o encontrado! Por favor, verifique se ele n�o foi exclu�do!</body></html>");
			exit(0);
		}
		cur_node_children = cur_node->children;

		for(indice1 = 1; cur_node_children != NULL; cur_node_children = cur_node_children->next, indice1 ++)
		{	
			if((cur_node_children->children != NULL) && (cur_node_children->name != NULL))
			{
				if(strcmp((char *)cur_node_children->name,"ano_FollowUp") != 0);
					trocaAspas(cur_node_children->children->content, fraseFinal);
					trocaEnter(fraseFinal, fraseFinal2);
					printf ("\t\ttabela[%i] = [\"%s\",\"%s\"];\n", indice1, cur_node_children->name, fraseFinal2);		
			}
			else
				indice1 --;
		}
		
		usualFreeMemory(NULL);	
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
	printf ("</script>\r\n");
printf ("</head>\r\n");
printf ("\r\n");
printf ("<body border=\"0\" onLoad=\"inicializaOcultos('tabelaFollowUp'); preencherCampos(check);\">\r\n");
printf ("\r\n");

showMenu("followUp",username);

printf ("\r\n");
printf ("\r\n");
printf ("<div align=\"center\"><br>\r\n");
printf ("<span style=\"font-size: 13pt\" class=\"bold\">Projeto - Novos M&eacute;todos Diagn&oacute;sicos em TB pulmonar - Policlinica Augusto Amaral Peixoto - SMS - RJ</span>\r\n");
printf ("<h4>(<i>Follow up</i> 90 dias)</h4>\r\n");
printf ("\r\n");
printf ("	<form name=\"check\" method=\"post\" action=\"editPatientOutrosForms.cgi\" onSubmit=\"return validar_follow_up (this)\">\r\n");
printf ("	<!-- --><input type=\"hidden\" name=\"form\" value=\"followUp\" />\r\n");
printf ("		<input type=\"hidden\" name=\"uid\" value=\"%s\" />\n",username);
printf ("		<br>\r\n");
printf ("		<!-- Numero Geral -->\r\n");
printf ("	<!-- --><b>N&uacute;mero Geral : </b><input name=\"numeroGeral\" type=\"text\" size=\"6\" value=\"\" readonly=\"readonly\"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br><br>\r\n");
printf ("	<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" id=\"tabelaFollowUp\" class=\"tabela\">\r\n");
printf ("		<tr>\r\n");
printf ("\r\n");
printf ("		<td colspan=\"5\" class=\"label\"><b>Follow Up</b></td>\r\n");
printf ("	</tr>\r\n");
printf ("\r\n");
printf ("	<!-- CRITERIO DE ENTRADA -->\r\n");
printf ("		\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td><b><script>document.write(tabFields[0][1]);</script></b></td>\r\n");
printf ("	<td colspan=\"4\">\r\n");
printf ("				<input name=\"criterioEntrada\" type=\"radio\" value=\"2BAAR+_1_2+\">2 BAAR positivos + 1 ou 2 culturas positivas no LJ;\r\n");
printf ("				<p><input name=\"criterioEntrada\" type=\"radio\" value=\"1BAAR+_1_2+\">1 BAAR positivo + 1 ou 2 culturas  positivas no LJ;</p>\r\n");
printf ("\r\n");
printf ("				<p><input name=\"criterioEntrada\" type=\"radio\" value=\"2BAAR-_1_2+\">2 BAAR negativos + 1 ou 2 culturas positivas no LJ;</p>\r\n");
printf ("				<p><input name=\"criterioEntrada\" type=\"radio\" value=\"2BAAR-_1_2-\">2 BAAR positivos + culturas  negativas no LJ;</p>\r\n");
printf ("				<p><input name=\"criterioEntrada\" type=\"radio\" value=\"1BAAR+_1_2-\">1BAAR positivo + culturas negativas no LJ</p>\r\n");
printf ("				<p><input name=\"criterioEntrada\" type=\"radio\" value=\"2BAAR-_1_2-\">2BAAR negativos + culturas negativas no LJ</p>\r\n");
printf ("				<p><input name=\"criterioEntrada\" type=\"radio\" value=\"1BAAR-_1_2-\">1BAAR negativo + culturas negativas no LJ</p>\r\n");
printf ("	</td>\r\n");
printf ("\r\n");
printf ("	</tr>\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("\r\n");
printf ("	<!-- TRATAMENTO PRESCRITO TB -->\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[1][1]);</script></td>\r\n");
printf ("	<td><input name=\"tratamentoPrescritoTB\" type=\"radio\" value=\"sim\" onclick=\"exibeLinhaOculta('tabelaFollowUp', 3);exibeLinhaOculta('tabelaFollowUp', 4);\">Sim</td>\r\n");
printf ("	<td><input name=\"tratamentoPrescritoTB\" type=\"radio\" value=\"nao\" onclick=\"ocultaLinha('tabelaFollowUp', 3);ocultaLinha('tabelaFollowUp', 4)\">N&atilde;o</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"tratamentoPrescritoTB\" type=\"radio\" value=\"ignorado\" onclick=\"ocultaLinha('tabelaFollowUp', 3);ocultaLinha('tabelaFollowUp', 4)\">Ignorado</td>\r\n");
printf ("	<td></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!--DATA DO INICIO-->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td ><script>document.write(tabFields[2][1]);</script></td> \r\n");
printf ("	<td  colspan=\"4\"><input name=\"inicio_dia\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarDia(this))inicio_mes.focus();\"> / <input name=\"inicio_mes\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarMes(this))inicio_ano.focus();\"> / <input name=\"inicio_ano\" type=\"text\" maxlength=\"4\" size=\"4\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onChange=\"validarAno(this);\" onBlur=\"validarQualquerData(inicio_dia,inicio_mes,inicio_ano)\"></td>");
printf ("\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- FARMACOS UTILIZADOS -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[3][1]);</script></td> \r\n");
printf ("	<td><input name=\"tratamentoPrescritoTBFarmacos\" type=\"checkbox\" value=\"rifampicina\">Rifampicina\r\n");
printf ("	<br><input name=\"tratamentoPrescritoTBFarmacos\" type=\"checkbox\" value=\"isoniazida\">Isoniazida\r\n");
printf ("	<br><input name=\"tratamentoPrescritoTBFarmacos\" type=\"checkbox\" value=\"pirazinamida\">Pirazinamida</td>\r\n");
printf ("	<td><input name=\"tratamentoPrescritoTBFarmacos\" type=\"checkbox\" value=\"etambutol\">Etambutol\r\n");
printf ("	<br><input name=\"tratamentoPrescritoTBFarmacos\" type=\"checkbox\" value=\"etionamida\">Etionamida\r\n");
printf ("	<br><input name=\"tratamentoPrescritoTBFarmacos\" type=\"checkbox\" value=\"estreptomicina\">Estreptomicina</td>\r\n");
printf ("\r\n");
printf ("	<td colspan=\"2\"><input name=\"tratamentoPrescritoTBFarmacos\" type=\"checkbox\" value=\"ofloxacina\">Ofloxacina\r\n");
printf ("	<br><input name=\"tratamentoPrescritoTBFarmacos\" type=\"checkbox\" value=\"outros\" onClick=\"if(this.checked){farmacos7.disabled = false;farmacos7.focus();}else{farmacos7.disabled = true}\">Outros: <input name=\"farmacos7\" type=\"text\" maxlength=\"100\" size=\"5\" disabled=\"true\"></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- REACOES ADVERSAS -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td><script>document.write(tabFields[25][1]);</script></td>\r\n");
printf ("	<td><input name=\"reacoesAdversasTuberculostaticos\" type=\"radio\" value=\"sim\" onclick=\"exibeLinhaOculta('tabelaFollowUp', 6);exibeLinhaOculta('tabelaFollowUp', 7);\">Sim</td>\r\n");
printf ("	<td><input name=\"reacoesAdversasTuberculostaticos\" type=\"radio\" value=\"nao\" onclick=\"ocultaLinha('tabelaFollowUp', 6);ocultaLinha('tabelaFollowUp', 7)\">N&atilde;o</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"reacoesAdversasTuberculostaticos\" type=\"radio\" value=\"ignorado\" onclick=\"ocultaLinha('tabelaFollowUp', 6);ocultaLinha('tabelaFollowUp', 7)\">Ignorado</td>\r\n");
printf ("	<td><input name=\"reacoesAdversasTuberculostaticos\" type=\"radio\" value=\"nsa\" onclick=\"ocultaLinha('tabelaFollowUp', 6);ocultaLinha('tabelaFollowUp', 7)\">NSA</td>\r\n");
printf ("	</tr>\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[26][1]);</script></td>\r\n");
printf ("	<td><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"exantema\">Exantema\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"confusao_mental\">Confus&atilde;o mental\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"ictericia\">Icter&iacute;cia\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"hepatotoxicidade\">Hepatotoxicidade\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"vertigem_nistagmo\">Vertigem/Nist&acute;gmo</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"hipoacusia\">Hipoacusia\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"crise_convulsiva\">Crise convulsiva\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"encefalopatia\">Encefalopatia\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"psicose\">Psicose\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"neurite_optica\">Neurite &oacute;ptica</td>\r\n");
printf ("	<td colspan=\"2\"><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"plaqueto_leuco_eosi\">Plaquetopenia/Leucopenia/Eosinofilia\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"anemia\">Anemia hemol./Vasculite\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"choque_purpura\">Choque/P&uacute;rpura\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"nefrite_interstcial\">Nefrite intersticial\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMaiores\" type=\"checkbox\" value=\"rabdomiolise\">Rabdomi&oacute;lise/Insuf. Renal</td>\r\n");
printf ("\r\n");
printf ("	</tr>\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td><script>document.write(tabFields[27][1]);</script></td>\r\n");
printf ("	<td><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"prurido\">Prurido\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"anorexia\">Anorexia\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"nauseas_vomito\">N&acute;useas/Vomitos\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"dor_abdomem\">Dor abdominal\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"dor_articular\">Dor articular</td>\r\n");
printf ("	<td><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"neurite\">Neurite perif&eacute;rica\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"euforia\">Euforia\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"insonia_sonolencia\">Ins&ocirc;nia/Sonol&ecirc;ncia\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"ansiedade\">Ansiedade\r\n");
printf ("\r\n");
printf ("\r\n");
printf ("<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"cefaleia\">Cefal&eacute;ia</td>\r\n");
printf ("	<td colspan=\"2\"><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"acne\">Acne\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"hiperuricemia\">Hiperuricemia\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"febre\">Febre\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"hipotensao\">Hipotens&atilde;o ortost&acute;tica\r\n");
printf ("	<br><input name=\"reacoesAdversasTuberculostaticosMenores\" type=\"checkbox\" value=\"ginecomastia\">Ginecomastia</td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- OBITO -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("\r\n");
printf ("	<td ><script>document.write(tabFields[4][1]);</script></td>\r\n");
printf ("	<td><input name=\"obito\" type=\"radio\" value=\"sim\" onclick=\"exibeLinhaOculta('tabelaFollowUp', 9)\">Sim</td>\r\n");
printf ("	<td><input name=\"obito\" type=\"radio\" value=\"nao\" onclick=\"ocultaLinha('tabelaFollowUp', 9)\">N&atilde;o</td>\r\n");
printf ("	<td><input name=\"obito\" type=\"radio\" value=\"ignorado\" onclick=\"ocultaLinha('tabelaFollowUp', 9)\">Ignorado</td>\r\n");
printf ("	<td></td>\r\n");
printf ("	</tr>\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("	<!-- CASO AFIRMATIVO CAUSA -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td ><script>document.write(tabFields[5][1]);</script></td>\r\n");
printf ("	<td>&nbsp;&nbsp;\r\n");
printf ("	<input name=\"casoObito\" type=\"radio\" value=\"tb\">TB</td>\r\n");
printf ("	<td><input name=\"casoObito\" type=\"radio\" value=\"nao_tb\">N&atilde;o TB</td>\r\n");
printf ("	<td><input name=\"casoObito\" type=\"radio\" value=\"ignorado\">Ignorado</td>\r\n");
printf ("\r\n");
printf ("	<td></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- MUDANCA DE ESQUEMA -->\r\n");
printf ("	\r\n");
printf ("\r\n");
printf ("<tr class=\"par\">\r\n");
printf ("	<td ><script>document.write(tabFields[6][1]);</script></td>\r\n");
printf ("	<td><input name=\"mudancaEsquemaTratamentoTB\" type=\"radio\" value=\"sim\" onclick=\"exibeLinhaOculta('tabelaFollowUp', 11);exibeLinhaOculta('tabelaFollowUp', 12);exibeLinhaOculta('tabelaFollowUp', 13);exibeLinhaOculta('tabelaFollowUp', 14);exibeLinhaOculta('tabelaFollowUp', 15);\">Sim</td>\r\n");
printf ("	<td><input name=\"mudancaEsquemaTratamentoTB\" type=\"radio\" value=\"nao\" onclick=\"ocultaLinha('tabelaFollowUp', 11);ocultaLinha('tabelaFollowUp', 12);ocultaLinha('tabelaFollowUp', 13);ocultaLinha('tabelaFollowUp', 14);ocultaLinha('tabelaFollowUp', 15);\">N&atilde;o</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"mudancaEsquemaTratamentoTB\" type=\"radio\" value=\"ignorado\" onclick=\"ocultaLinha('tabelaFollowUp', 11);ocultaLinha('tabelaFollowUp', 12);ocultaLinha('tabelaFollowUp', 13);ocultaLinha('tabelaFollowUp', 14);ocultaLinha('tabelaFollowUp', 15);\">Ignorado</td>\r\n");
printf ("	<td><input name=\"mudancaEsquemaTratamentoTB\" type=\"radio\" value=\"NSA\" onclick=\"ocultaLinha('tabelaFollowUp', 11);ocultaLinha('tabelaFollowUp', 12);ocultaLinha('tabelaFollowUp', 13);ocultaLinha('tabelaFollowUp', 14);ocultaLinha('tabelaFollowUp', 15);\">NSA</td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- DATA DA MUDANCA -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td ><script>document.write(tabFields[7][1]);</script></td> \r\n");
printf ("	<td ><input name=\"mudanca_mes\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarMes(this))mudanca_ano.focus();\"> / <input name=\"mudanca_ano\" type=\"text\" maxlength=\"4\" size=\"4\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onChange=\"validarAno(this);\" onBlur=\"validarQualquerData(01,mudanca_mes,mudanca_ano)\"></td>");
printf ("\r\n");
printf ("	<td colspan=\"3\"><input name=\"mudanca\" id=\"mudanca\" type=\"checkbox\" value=\"ignorada\" onClick=\"validarDataDesconhecida(document.check)\">Ignorada</td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- FARMACOS UTILIZADOS 2 -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td><script>document.write(tabFields[28][1]);</script></td>\r\n");
printf ("	<td><input name=\"mudancaFarmacos\" type=\"checkbox\" value=\"rifampicina\">Rifampicina</td>\r\n");
printf ("	<td><input name=\"mudancaFarmacos\" type=\"checkbox\" value=\"isoniazida\">Isoniazida</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"mudancaFarmacos\" type=\"checkbox\" value=\"pirazinamida\">Pirazinamida</td>\r\n");
printf ("	<td></td>\r\n");
printf ("	</tr>\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td>&nbsp;</td>\r\n");
printf ("	<td><input name=\"mudancaFarmacos\" type=\"checkbox\" value=\"etambutol\">Etambutol</td>\r\n");
printf ("	<td><input name=\"mudancaFarmacos\" type=\"checkbox\" value=\"etionamida\">Etionamida</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"mudancaFarmacos\" type=\"checkbox\" value=\"estreptomicina\">Estreptomicina</td>\r\n");
printf ("	<td></td>\r\n");
printf ("</tr>\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td>&nbsp;</td>\r\n");
printf ("	<td><input name=\"mudancaFarmacos\" type=\"checkbox\" value=\"ofloxacina\">Ofloxacina</td>\r\n");
printf ("	<td colspan=\"3\"><input name=\"mudancaFarmacos\" type=\"checkbox\" value=\"outros\" onClick=\"if(this.checked){farmacos14.disabled = false;farmacos14.focus();}else{farmacos14.disabled = true}\">Outros: <input name=\"farmacos14\" type=\"text\" maxlength=\"100\" size=\"5\" disabled=\"true\"></td>\r\n");
printf ("	</tr>\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("	<!-- MOTIVO -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td><script>document.write(tabFields[8][1]);</script></td>\r\n");
printf ("	<td><input name=\"mudancaMotivo\" type=\"radio\" value=\"reacao_adversa\" onClick=\"motivo.disabled = true\">Rea&ccedil;&atilde;o adversa</td>\r\n");
printf ("	<td><input name=\"mudancaMotivo\" type=\"radio\" value=\"interacao_medicamentosa\" onClick=\"motivo.disabled = true\">Intera&ccedil;&atilde;o medicamentosa</td>\r\n");
printf ("	<td><input name=\"mudancaMotivo\" type=\"radio\" value=\"falencia\" onClick=\"motivo.disabled = true\">Fal&ecirc;ncia</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"mudancaMotivo\" type=\"radio\" value=\"outro\" onClick=\"motivo.disabled = false;motivo.focus();\">Outro:<input name=\"motivo\" type=\"text\" maxlength=\"100\" size=\"8\" disabled=\"true\"></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("<tr>\r\n");
printf ("<td colspan=\"5\" class=\"label\"><b>Avalia&ccedil;&atilde;o Cl&iacute;nica:</b></td>\r\n");
printf ("</tr>\r\n");
printf ("\r\n");
printf ("\r\n");
printf ("<!-- TOSSE DIMINUIDA -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("\r\n");
printf ("	<td ><script>document.write(tabFields[9][1]);</script></td>\r\n");
printf ("	<td><input name=\"tosseDiminuida\" type=\"radio\" value=\"sim\">Sim</td>\r\n");
printf ("	<td><input name=\"tosseDiminuida\" type=\"radio\" value=\"nao\">N&atilde;o</td>\r\n");
printf ("	<td><input name=\"tosseDiminuida\" type=\"radio\" value=\"ignorado\">Ignorado</td>\r\n");
printf ("	<td><input name=\"tosseDiminuida\" type=\"radio\" value=\"NSA\">NSA</td>\r\n");
printf ("	</tr>\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("	<!-- PESO ATUAL -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[10][1]);</script></td> \r\n");
printf ("	<td colspan=\"4\"><input name=\"pesoAtual90dias\" type=\"text\" maxlength=\"3\" size=\"3\" onBlur=\"validarCampoNumerico(this)\"></td>\r\n");
printf ("	</tr>\r\n");
printf ("	<!-- Alteracoes Evolutivas no Exame Fisico -->\r\n");
printf ("\r\n");
printf ("<tr class=\"par\">\r\n");
printf ("	<td><script>document.write(tabFields[29][1]);</script></td>\r\n");
printf ("\r\n");
printf ("	<td colspan=\"5\"><input name=\"alteracoesEvolutivasNoExameFisico\" type=\"text\" size=\"75\"></td>\r\n");
printf ("</tr>\r\n");
printf ("\r\n");
printf ("<tr>\r\n");
printf ("<td colspan=\"5\" class=\"label\"><b>RX de t&oacute;rax(entre 60 e 90 dias no estudo):</b></td>\r\n");
printf ("</tr>\r\n");
printf ("	\r\n");
printf ("<!-- PROB TB ATIVA AVALIACAO RX -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[11][1]);</script></td>\r\n");
printf ("	<td><input name=\"probabilidadeTBAtivaAposEstudoRX\" type=\"radio\" value=\"alta\" onclick=\"exibeLinhaOculta('tabelaFollowUp', 22);exibeLinhaOculta('tabelaFollowUp', 23);exibeLinhaOculta('tabelaFollowUp', 24);exibeLinhaOculta('tabelaFollowUp', 25);exibeLinhaOculta('tabelaFollowUp', 26);ocultaLinha('tabelaFollowUp', 27);ocultaLinha('tabelaFollowUp', 28)\">Alta</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"probabilidadeTBAtivaAposEstudoRX\" type=\"radio\" value=\"media\" onclick=\"exibeLinhaOculta('tabelaFollowUp', 22);exibeLinhaOculta('tabelaFollowUp', 23);exibeLinhaOculta('tabelaFollowUp', 24);exibeLinhaOculta('tabelaFollowUp', 2);exibeLinhaOculta('tabelaFollowUp', 26);ocultaLinha('tabelaFollowUp', 27);ocultaLinha('tabelaFollowUp', 28)\">M&eacute;dia</td>\r\n");
printf ("	<td><input name=\"probabilidadeTBAtivaAposEstudoRX\" type=\"radio\" value=\"baixa\" onclick=\"ocultaLinha('tabelaFollowUp', 22);ocultaLinha('tabelaFollowUp', 23);ocultaLinha('tabelaFollowUp', 24);ocultaLinha('tabelaFollowUp', 25);ocultaLinha('tabelaFollowUp', 26);exibeLinhaOculta('tabelaFollowUp', 27);exibeLinhaOculta('tabelaFollowUp', 28)\">Baixa</td>\r\n");
printf ("	<td></td>\r\n");
printf ("	</td>\r\n");
printf ("	\r\n");
printf ("	<!-- CAVITACAO -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[12][1]);</script></td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"cavitacao90dias\" type=\"radio\" value=\"sim\">Sim</td>\r\n");
printf ("\r\n");
printf ("<td><input name=\"cavitacao90dias\" type=\"radio\" value=\"nao\">N&atilde;o</td>\r\n");
printf ("	<td><input name=\"cavitacao90dias\" type=\"radio\" value=\"ignorado\">Ignorado</td>\r\n");
printf ("	<td></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- PADRAO TIPICO -->\r\n");
printf ("\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[13][1]);</script></td>\r\n");
printf ("	<td><input name=\"padraoTipico90dias\" type=\"radio\" value=\"sim\">Sim</td>\r\n");
printf ("	<td><input name=\"padraoTipico90dias\" type=\"radio\" value=\"nao\">N&atilde;o</td>\r\n");
printf ("	<td><input name=\"padraoTipico90dias\" type=\"radio\" value=\"ignorado\">Ignorado</td>\r\n");
printf ("	<td></td>\r\n");
printf ("\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- COMPATIVEL -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[14][1]);</script></td>\r\n");
printf ("	<td><input name=\"compativel90dias\" type=\"radio\" value=\"sim\">Sim</td>\r\n");
printf ("	<td><input name=\"compativel90dias\" type=\"radio\" value=\"nao\">N&atilde;o</td>\r\n");
printf ("	<td><input name=\"compativel90dias\" type=\"radio\" value=\"ignorado\">Ignorado</td>\r\n");
printf ("\r\n");
printf ("	<td></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- ATIPICO -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[15][1]);</script></td>\r\n");
printf ("	<td><input name=\"atipico90dias\" type=\"radio\" value=\"sim\">Sim</td>\r\n");
printf ("	<td><input name=\"atipico90dias\" type=\"radio\" value=\"nao\">N&atilde;o</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"atipico90dias\" type=\"radio\" value=\"ignorado\">Ignorado</td>\r\n");
printf ("	<td></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- NSA -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[16][1]);</script></td>\r\n");
printf ("	<td colspan=\"4\"><input name=\"NSA90dias\" type=\"checkbox\" value=\"nsa\">NSA</td>\r\n");
printf ("\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- CASO BAIXA PROBABILIDADE DE TB -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[17][1]);</script></td>\r\n");
printf ("	<td ><input name=\"casoBaixaProbabilidade90dias\" type=\"radio\" value=\"inativa_sequela\">TB inativa/<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sequela</td>\r\n");
printf ("	<td ><input name=\"casoBaixaProbabilidade90dias\" type=\"radio\" value=\"outra_doenca\">Outra<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;doen&ccedil;a</td>\r\n");
printf ("\r\n");
printf ("	<td><input name=\"casoBaixaProbabilidade90dias\" type=\"radio\" value=\"normal\">Normal</td>\r\n");
printf ("	<td></td>\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td></td>\r\n");
printf ("	<td><input name=\"casoBaixaProbabilidade90dias\" type=\"radio\" value=\"ignorado\">Ignorado</td>\r\n");
printf ("	<td colspan=\"3\"><input name=\"casoBaixaProbabilidade90dias\" type=\"radio\" value=\"nsa\">NSA</td>\r\n");
printf ("	</tr>\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("	<!-- DATA DO RX -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td ><script>document.write(tabFields[18][1]);</script></td> \r\n");
printf ("	<td colspan=\"4\"><input name=\"rx_dia\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarDia(this))rx_mes.focus();\"> / <input name=\"rx_mes\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarMes(this))rx_ano.focus();\"> / <input name=\"rx_ano\" type=\"text\" maxlength=\"4\" size=\"4\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onChange=\"validarAno(this);\" onBlur=\"validarQualquerData(rx_dia,rx_mes,rx_ano)\"></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- FOLLOW UP DO RX -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("\r\n");
printf ("	<td><script>document.write(tabFields[19][1]);</script></td>\r\n");
printf ("	<td><input name=\"followUpRXTorax\" type=\"radio\" value=\"melhora\">Melhora</td>\r\n");
printf ("	<td><input name=\"followUpRXTorax\" type=\"radio\" value=\"inalterado\">Inalterado</td>\r\n");
printf ("	<td><input name=\"followUpRXTorax\" type=\"radio\" value=\"piorado\">Piorado</td>\r\n");
printf ("	<td><input name=\"followUpRXTorax\" type=\"radio\" value=\"ignorado\">Ignorado</td>\r\n");
printf ("	</tr>\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("<tr>\r\n");
printf ("<td colspan=\"5\" class=\"label\"><b>HIV/AIDS:</b></th>\r\n");
printf ("</tr>\r\n");
printf ("\r\n");
printf ("	<!-- HIV/AIDS -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[20][1]);</script></td>\r\n");
printf ("	<td><input name=\"testeHIV90dias\" type=\"radio\" value=\"positivo\">Positivo</td>\r\n");
printf ("	<td><input name=\"testeHIV90dias\" type=\"radio\" value=\"negativo\">Negativo</td>\r\n");
printf ("\r\n");
printf ("	<td colspan=\"2\"><input name=\"testeHIV90dias\" type=\"radio\" value=\"nao_realizado\">N&atilde;o realizado ou resultado desconhecido</td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- DATA ANTI-HIV -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"par\">\r\n");
printf ("	<td><script>document.write(tabFields[21][1]);</script></td> \r\n");
printf ("	<td colspan=\"4\"><input name=\"antihiv_dia\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarDia(this))antihiv_mes.focus();\"> / <input name=\"antihiv_mes\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarMes(this))antihiv_ano.focus();\"> / <input name=\"antihiv_ano\" type=\"text\" maxlength=\"4\" size=\"4\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onChange=\"validarAno(this);\" onBlur=\"validarQualquerData(antihiv_dia,antihiv_mes,antihiv_ano)\"></td>\r\n");
printf ("\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<!-- Diagn&oacute;stico 90 DIAS -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td><script>document.write(tabFields[22][1]);</script></td>\r\n");
printf ("	<td><input name=\"diagnostico90dias\" type=\"radio\" value=\"pulmonar\" onclick=\"ocultaLinha('tabelaFollowUp', 36)\">TB pulmonar</td>\r\n");
printf ("	<td><input name=\"diagnostico90dias\" type=\"radio\" value=\"extra\" onclick=\"ocultaLinha('tabelaFollowUp', 36)\">TB Extra-<br>pulmonar</td>\r\n");
printf ("	<td><input name=\"diagnostico90dias\" type=\"radio\" value=\"pulmonar_extra\" onclick=\"ocultaLinha('tabelaFollowUp', 36)\">Pulmonar+<br>+Extra</td>\r\n");
printf ("\r\n");
printf ("	<td></td></tr>\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td></td>\r\n");
printf ("	<td><input name=\"diagnostico90dias\" type=\"radio\" value=\"nao_tb\" onclick=\"exibeLinhaOculta('tabelaFollowUp', 36)\">N&atilde;o TB</td>\r\n");
printf ("	<td><input name=\"diagnostico90dias\" type=\"radio\" value=\"ignorado\" onclick=\"ocultaLinha('tabelaFollowUp', 36)\">Ignorado</td>\r\n");
printf ("	<td></td><td></td>\r\n");
printf ("	</tr>\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("	<!-- CASO  DIAGNOSTICO DIFERENTE TB  -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td ><script>document.write(tabFields[23][1]);</script></td> \r\n");
printf ("	<td ><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"ca_de_pulmao\" onClick=\"outro_diagnostico_sim.disabled=true\">CA de pulm&atilde;o\r\n");
printf ("	<br><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"pneumo_bacteria\" onClick=\"outro_diagnostico_sim.disabled=true\">Pneumonia bacteriana\r\n");
printf ("	<br><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"pneu_viral\" onClick=\"outro_diagnostico_sim.disabled=true\">Pneumonia viral</td>\r\n");
printf ("	<td ><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"micose_pulmonar\" onClick=\"outro_diagnostico_sim.disabled=true\">Micose pulmonar\r\n");
printf ("	<br><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"pneumoconiose\" onClick=\"outro_diagnostico_sim.disabled=true\">Pneumoconiose\r\n");
printf ("	<br><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"dpco_infeccao\" onClick=\"outro_diagnostico_sim.disabled=true\">DPOC + Infec&ccedil;&atilde;o <Br>br&ocirc;nquica inespec&iacute;fica</td>\r\n");
printf ("\r\n");
printf ("	<td colspan=\"2\"><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"sequela_infeccao\" onClick=\"outro_diagnostico_sim.disabled=true\">Sequela de TB + Infe&ccedil;&atilde;o<br> br&ocirc;nquica inespec&iacute;fica\r\n");
printf ("	<br><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"falencia_cardiaca\" onClick=\"outro_diagnostico_sim.disabled=true\">Fal&ecirc;ncia card&iacute;aca\r\n");
printf ("	<br><input name=\"diagnosticoDiferenteTB\" type=\"radio\" value=\"outros\" onClick=\"outro_diagnostico_sim.disabled=false;outro_diagnostico_sim.focus();\">Outro: <input name=\"outro_diagnostico_sim\" type=\"text\" maxlength=\"100\" size=\"5\" disabled=\"true\"></td>\r\n");
printf ("	</tr>\r\n");
printf ("	\r\n");
printf ("	<td colspan=\"5\" class=\"label\"><b>Diagn&oacute;stico Final:</b></th>\r\n");
printf ("\r\n");
printf ("	\r\n");
printf ("	<!-- DIAGNOSTICO FINAL -->\r\n");
printf ("	\r\n");
printf ("	<tr class=\"impar\">\r\n");
printf ("	<td width=\"320\"><script>document.write(tabFields[24][1]);</script></td>\r\n");
printf ("	<td colspan=\"4\">\r\n");
printf ("		<input name=\"diagnosticoFinal\" type=\"radio\" value=\"confirmado\">Diagn&oacute;stico confirmado de TB: cultura (+) para M. tb pelo padr&atilde;o ouro, LJ ou BACTEC;\r\n");
printf ("		<p><input name=\"diagnosticoFinal\" type=\"radio\" value=\"provavel\">Diagn&oacute;stico de probabilidade: BAAR (+) e cultura (-) com resposta cl&iacute;nica / radiol&oacute;gica ou evid&ecirc;ncia de granuloma com BAAR positivo na aut&oacute;psia;</p>\r\n");
printf ("\r\n");
printf ("		<p><input name=\"diagnosticoFinal\" type=\"radio\" value=\"clinico\">Diagn&oacute;stico cl&iacute;nico: BAAR (-) e cultura (-) com resposta cl&iacute;nica/radiol&oacute;gica ao tratamento compat&iacute;vel com TB pulmonar;</p>\r\n");
printf ("		<p><input name=\"diagnosticoFinal\" type=\"radio\" value=\"pulmonar_com_baar+\">Pulmonar com BAAR (+): Sinais e sintomas compat&iacute;veis com TB pulmonar, RX de t&oacute;rax anormal e BAAR do escarro (+);</p>\r\n");
printf ("		<p><input name=\"diagnosticoFinal\" type=\"radio\" value=\"pulmonar_com_baar-\">Pulmonar com BAAR (-): Sinais e sintomas compat&iacute;veis com TB pulmonar, RX de t&oacute;rax anormal, Prova tubercul&iacute;nica positiva e BAAR do escarro (-);</p>\r\n");
printf ("\r\n");
printf ("		<p><input name=\"diagnosticoFinal\" type=\"radio\" value=\"pulmonar_com_baar-2\">Pulmonar com BAAR (-) e resposta cl&iacute;nica compat&iacute;vel: Sinais e sintomas compat&iacute;veis com TB pulmonar, RX de t&oacute;rax anormal, Prova tubercul&iacute;nica negativa e BAAR do escarro (-).</p>\r\n");
printf ("	</td>\r\n");
printf ("</tr>\r\n");
printf ("\r\n");
printf ("	</div>\r\n");
printf ("\r\n");
printf ("		<!-- Observacoes -->\r\n");
printf ("\r\n");
printf ("		<tr class=\"par\">\r\n");
printf ("			<td colspan=\"1\"> 16 - Observa&ccedil;&otilde;es: </td>\r\n");
printf ("			<td colspan=\"4\" align =\"center\"><textarea name=\"observacoes\" rows=\"5\" cols=\"65\"></textarea></td>\r\n");
printf ("		</tr>	\r\n");
printf ("			<tr>\r\n");
printf ("			<td>&nbsp;</td>\r\n");
printf ("		</tr>\r\n");
printf ("\r\n");
printf ("			</table>\r\n");
printf ("			<div align=\"center\">\r\n");
printf ("			\r\n");
printf ("	Avaliado por: <input name=\"avaliadorMedicoFollowUp\" type=\"text\" maxlength=\"100\" size=\"25\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\r\n");
printf ("	Cadastrado por: <input name=\"quemCadastrou\" type=\"text\" readonly=\"readonly\" value=\"%s\" size=\"25\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\r\n",username);
printf ("	Data: <input name=\"dia_FollowUp\" type=\"text\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarDia(this))mes_FollowUp.focus();\">/<input type=\"text\" name=\"mes_FollowUp\" maxlength=\"2\" size=\"2\" onKeyUp=\"if(this.value.length == 2)this.blur();\" onChange=\"if(validarMes(this))ano_FollowUp.focus();\">/<input type=\"text\" name=\"ano_FollowUp\" maxlength=\"4\" size=\"4\" onKeyUp=\"if(this.value.length == 4)this.blur();\" onChange=\"validarAno(this);validarQualquerData(dia_FollowUp,mes_FollowUp,ano_FollowUp);\"></td>\r\n");
printf ("	\r\n");
printf ("	<!--    ENVIAR / LIMPAR     -->\r\n");
printf ("\r\n");
printf ("	<br>\r\n");
printf ("	<br>\r\n");
printf ("	<input value=\"Limpar Formul&aacute;rio\" type=\"reset\">\r\n");
printf ("	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\r\n");
printf ("	<input type=\"submit\" value=\"Enviar Formul&aacute;rio\">\r\n");
printf ("	<br><br>\r\n");
printf ("	</div>\r\n");
printf ("	</form>\r\n");
printf ("	<p>\r\n");
printf ("\r\n");
printf ("	<p>\r\n");
printf ("</body>\r\n");
printf ("</html>");
	
	cgi_end();
	
	return 0;
}

/*
gcc -Wall -c ntbCgiFormEdit.c `xml2-config --cflags`
gcc -Wall -o formEdit.cgi ntbCgiFormEdit.o functions.o `xml2-config --libs` -Llibs/libcgi-1.0 -lcgi
mv -f formEdit.cgi ../formEdit.cgi
*/
/********************************************************************************************
 * UFRJ/COPPE/LPS                                                                           *
 * Projeto Neural TB                                                                        *
 * CGI para criacao do grafico de grupo de pacientes                                        *
 * Author: Laura de Oliveira Fernandes Moraes                                               *
 ********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gd.h"
#include "consts.h"
#include "tiposModif.h"
#include "patientFunctionsModif.h"

void geraGrafico(int opcaoCor, float opcaoY, float response, char * pid, chainType_2 * info)
{
	/* Declaracao de Variaveis */
	FILE *arqGrupo, *arqTemp;
	gdImagePtr im;
	int blue;
	float opcaoX;

        /******************************************/

        /* Modificando coordenadas do grafico */
	opcaoX = 100;
	opcaoY = (opcaoY*RAIO)/RAIO_ORIGINAL;
        
        /*************************************/

	/* Abrindo arquivo original para leitura */

	if(!(arqGrupo = fopen("./imagesRedeNeural/original.png", "r")))
		return;
	im = gdImageCreateFromPng(arqGrupo);
	fclose(arqGrupo);

        /****************************************/

	/* Cor usada na identificacao do paciente */
	blue = gdImageColorAllocate(im, 0, 0, 255);
	/******************************************/

	/* Verificando o grupo e identificando o paciente no grafico atraves do seu raio */
	switch(opcaoCor)
	{
		case 0:  //baixo risco - verde
			gdImageArc(im, 100, 450, 2*opcaoY, 2*opcaoY, 0, 360, blue);
			gdImageArc(im, 100, 450, 2*opcaoY+1, 2*opcaoY+1, 0, 360, blue);
			gdImageArc(im, 100, 450, 2*opcaoY+2, 2*opcaoY+2, 0, 360, blue);
			gdImageArc(im, 100, 450, 2*opcaoY+3, 2*opcaoY+3, 0, 360, blue);
			gdImageArc(im, 100, 450, 2*opcaoY+4, 2*opcaoY+4, 0, 360, blue);
			break;
		case 1: //medio risco - amarelo
			gdImageArc(im, 100, 275, 2*opcaoY, 2*opcaoY, 0, 360, blue);
			gdImageArc(im, 100, 275, 2*opcaoY+1, 2*opcaoY+1, 0, 360, blue);
			gdImageArc(im, 100, 275, 2*opcaoY+2, 2*opcaoY+2, 0, 360, blue);
			gdImageArc(im, 100, 275, 2*opcaoY+3, 2*opcaoY+3, 0, 360, blue);
			break;
		case 2: //alto risco - vermelho
			gdImageArc(im, 100, 100, 2*opcaoY, 2*opcaoY, 0, 360, blue);
			gdImageArc(im, 100, 100, 2*opcaoY+1, 2*opcaoY+1, 0, 360, blue);
			gdImageArc(im, 100, 100, 2*opcaoY+2, 2*opcaoY+2, 0, 360, blue);
			gdImageArc(im, 100, 100, 2*opcaoY+3, 2*opcaoY+3, 0, 360, blue);
			break;
		default: //paciente fora de grupo
		break;
	}
        /**************************************************************************************/

	/* Criando novo arquivo de grafico */
	if(!(arqTemp = fopen("./imagesRedeNeural/temp.png", "wb")))
		return ;
	gdImagePng(im, arqTemp);
	fclose(arqTemp);
	/************************************/

	/* Destruindo imagem da memoria  */
	gdImageDestroy(im);
	/*********************************/

	/* Exibindo saida em HTML */
	printf("Content-type: text/html\n\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<link rel=\"stylesheet\" href=\"./css/grafico.css\" />");
	printf("<title>Resultado</title>\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<p><div id=\"divNome\"><h2><u>N&uacute;mero geral: %s</u></h2></div></p>", pid);
	printf("<div id=\"divSintomas\">\n");
	printf("<strong><u>DADOS DO PACIENTE:</u></strong><br /><br />\n");
	while(info)
	{
		printf("<p><b>%s</b>: %s</p>", info->attribute, info->value);
		info = info->next;
	}
	printf("</div>\n");
	/*
	printf("<div id=\"divNome\"><h1><u>%s</u></h1></div>", auxPaciente.nome);
	printf("<div id=\"divSintomas\">\n");
	printf("<strong><u>DADOS DO PACIENTE</u></strong><br /><br />\n");
	printf("<b>Data de nascimento:</b> %s<br />\n", auxPaciente.data_nascimento);
	printf("<b>Idade:</b> %s<br />\n", auxPaciente.idade);
	printf("<b>Sexo:</b> %s<br />\n", auxPaciente.sexo);
	printf("<img src=\"../imagesRedeNeural/bolaAlto.png\" /><img src=\"../imagesRedeNeural/bolaMedio.png\" /><img src=\"../imagesRedeNeural/bolaBaixo.png\" />&nbsp;<b>Tosse:</b> %s<br />\n", auxPaciente.tosse);
	printf("<b>Hemopt&oacute;ico:</b> %s<br />\n", auxPaciente.hemoptoico);
	printf("<img src=\"../sistema/imagesRedeNeural/bolaAlto.png\" /><img src=\"../sistema/imagesRedeNeural/bolaMedio.png\" />&nbsp;<b>Sudorese:</b> %s<br />\n", auxPaciente.sudorese);
	printf("<img src=\"../sistema/imagesRedeNeural/bolaAlto.png\" /><img src=\"../sistema/imagesRedeNeural/bolaMedio.png\" />&nbsp;<b>Febre:</b> %s<br />\n", auxPaciente.febre);
	printf("<img src=\"../sistema/imagesRedeNeural/bolaMedio.png\" />&nbsp;<b>Emagrecimento:</b> %s<br />\n", auxPaciente.emagrecimento);
	printf("<b>Dispn&eacute;ia:</b> %s<br />\n", auxPaciente.dispneia);
	printf("<img src=\"../sistema/imagesRedeNeural/bolaMedio.png\" />&nbsp;<b>Anorexia:</b> %s<br />\n", auxPaciente.anorexia);
	printf("<b>Fuma Atualmente:</b> %s<br />\n", auxPaciente.fuma_atualmente);
	printf("<b>TB Extrapulmonar: </b>%s<br />\n", auxPaciente.tb_extrapulmonar);
	printf("<b>Interna&ccedil;&atilde;o Hospitalar:</b> %s<br />\n", auxPaciente.internacao_hospitalar);
	printf("<b>SIDA:</b> %s<br />\n", auxPaciente.sida);
	printf("<b>Grupo de Risco:</b> %s<br />\n", auxPaciente.grupo_de_risco);
	printf("</div>\n");
	*/
	if(opcaoCor == 3)
		printf("<p><div id=\"foraDeGrupo\"> O Paciente n&atilde;o pertence a nenhum dos grupos de risco</div></p>\n");
	printf("<div id=\"divResultado\"><strong>%f</strong></div>\n", response);
	printf("<img id=\"imagemGrupos\" border=\"1\" src=\"./imagesRedeNeural/temp.png\" />\n");
	printf("<img id=\"imagemLegenda\" border=\"1\" src=\"./imagesRedeNeural/legenda2.png\" />\n");
	printf("</body>\n");
	printf("</html>\n");
  	/*********************************************************************************************************************************/
//	return(OK);
}

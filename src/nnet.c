/********************************************************************************************
 * UFRJ/COPPE/LPS                                                                           *
 * Projeto Neural TB                                                                        *
 * C program to manipulate data of Artificial Neural Network                                *
 * Author: Pedro Henrique Antunes                                                           *
 * Revisão de codigo: Rony Tadeu Vernet Braga                                               *
 * Ultima atualizacao: 10/05/2006                                                           *
 ********************************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiposModif.h"
#include "consts.h"


/*Variaveis globais */

double entrada[12];
double W1[15][12],W2[15],Y1[15],Y2,Y1temp[15],Y2temp=0.0;
double norm;
double b1[15],b2,lim=0.0;
char strtemp[100],str[100];
tipopaciente paciente;
boolean tuberculose;
double pac[100][100];
int cont,cont3=0;
int n,p;
FILE *arq5,*arq6;
chainType *aux, *first;


void arrumarString(void)
{
	int cont1,cont2=0;
	for (cont1=0;cont1<=strlen(strtemp)+1;cont1++)
			if ((strtemp[cont1]!=' ') && (strtemp[cont1]!='\n') && (strtemp[cont1]!='\0'))
			{
				str[cont2]=strtemp[cont1];
				cont2++;
			}
//Desnecessario  	str[cont2]='\0';

}

unsigned lerPesos(void)

{
	FILE *arq;
	int cont1,cont2;

	if ((arq=fopen("rede","r"))==NULL)
	{
	return(ERRO_ABR_ARQ);
	}

	while (!feof(arq))
{
		fgets(strtemp,20,arq);
		arrumarString();

	if(!strncmp(str,"#variaveis",3))
	{
		fgets(strtemp,20,arq);
		arrumarString();
		n=atoi(str);
	}
	else if(!strncmp(str,"#norm",3))
	{
		fgets(strtemp,20,arq);
		arrumarString();
		norm=atof(str);
	}

	else if (!strncmp(str,"#neuronios",3))
	{
		fgets(strtemp,20,arq);
		arrumarString();
		p=atoi(str);
	}

	else if (!strncmp(str,"#W1",3))
	{
		for (cont1=0;cont1<p;cont1++)
			for (cont2=0;cont2<n;cont2++)
			{
				fgets(strtemp,20,arq);
				arrumarString();
				W1[cont1][cont2]=atof(str);
			}
	}

	else if (!strncmp(str,"#B1",3))
	{
		for (cont1=0;cont1<p;cont1++)
		{
			fgets(strtemp,20,arq);
			arrumarString();
			b1[cont1]=atof(str);
		}
	}
	else if (!strncmp(str,"#W2",3))
	{
		for (cont1=0;cont1<p;cont1++)
		{
			fgets(strtemp,20,arq);
			arrumarString();
			W2[cont1]=atof(str);
		}
	}

	else if  (!strncmp(str,"#B2",3))
	{
		fgets(strtemp,20,arq);
		arrumarString();
		b2=atof(str);
	}
}
	fclose(arq);
	return(OK);
}


unsigned propagaEntrada(void)
{
	int cont1,cont2;
	Y2temp=0;
	Y2=0;
	for (cont1=0;cont1<p;cont1++)
	{
		Y1temp[cont1]=0.0;
		for (cont2=0;cont2<n;cont2++)
			Y1temp[cont1]+=(W1[cont1][cont2]*entrada[cont2]);
		Y1[cont1]=tanhf(Y1temp[cont1]+b1[cont1]);
		Y2temp+=(W2[cont1]*Y1[cont1]);
	}
	Y2=tanhf(Y2temp+b2);
	return(OK);
}

unsigned avaliaPaciente(void)
{
	if (Y2<lim)
	{
		tuberculose=false;
		paciente.diag=-1.0;
	}

	if (Y2>=lim)
	{
		tuberculose=true;
		paciente.diag=1.0;
	}
	return (OK);
}


unsigned nnet (chainType *aux, double *response)
{
char stringt[250];
int i;


	/*if (argc!=27)
	{
	printf("\tVoce digitou %i variaveis,digite 26 variaveis\n",argc-1);
	return(ERRO);
	}*/

	/*paciente.idade=atof(argv[1]);
	paciente.genero=atof(argv[2]);
	paciente.estado=atof(argv[3]);
	paciente.cor=atof(argv[4]);
	paciente.renda=atof(argv[5]);
	paciente.tosse=atof(argv[6]);
	paciente.escarro=atof(argv[7]);
	paciente.hemoptoico=atof(argv[8]);
	paciente.hemoptise=atof(argv[9]) ;
	paciente.sudorese=atof(argv[10]);
	paciente.febre=atof(argv[11]);
	paciente.emagrecimento=atof(argv[12]) ;
	paciente.dortoracica=atof(argv[13]);
	paciente.calafrios=atof(argv[14]);
	paciente.dispneia=atof(argv[15]);
	paciente.astenia=atof(argv[16]);
	paciente.anorexia=atof(argv[17]) ;
	paciente.jafumou=atof(argv[18])	;
	paciente.fumaatual=atof(argv[19]);
	paciente.diabetes=atof(argv[20]) ;
	paciente.alcoolismo=atof(argv[21]);
	paciente.tbpulmant=atof(argv[22]);
	paciente.tbextrapulm=atof(argv[23]);
	paciente.interhosp=atof(argv[24]) ;
	paciente.contato=atof(argv[25]);
	paciente.sida=atof(argv[26]);*/

    if(!aux)
	return(-1);

	//if((arq5=fopen("verifica_entradas.txt","w"))==NULL)
	//	return(ERRO_ABR_ARQ);

	for (i=0 ;aux!= NULL; aux=aux->next)
	{
		if (strcmp(aux->attribute, "idade") == OK)
		{
			entrada[i] = atof(aux->value);
			i++;
		}
		if ((strcmp(aux->attribute, "tosse") == OK) || (strcmp(aux->attribute, "hemoptoico") == OK) ||  (strcmp(aux->attribute, "sudorese") == OK) || (strcmp(aux->attribute, "febre") == OK) || (strcmp(aux->attribute, "emagrecimento") == OK) || (strcmp(aux->attribute, "dispneia") == OK) || (strcmp(aux->attribute, "anorexia") == OK) || (strcmp(aux->attribute, "fuma_atualmente") == OK) || (strcmp(aux->attribute, "tb_extrapulmonar") == OK) || (strcmp(aux->attribute, "internacao_hospitalar") == OK) || (strcmp(aux->attribute, "sida") == OK))
		{
			entrada[i]= aux->entry;
			i++;
		}

//	snprintf(stringt,200,"Entrada %i ANTES  :  %f \t",i,entrada[i]);
//	fputs(stringt,arq5);

//	snprintf(stringt,200,"Entrada %i  DEPOIS :  %f\n",i,entrada[i]);
//	fputs(stringt,arq5);
   }





   //PARA CHECAR REDE COM O PROGRAMA VIA LINHA DE COMANDO

	if((arq6=fopen("pacientes.txt","a"))==NULL)
		return(ERRO_ABR_ARQ);
	snprintf(stringt,200,"%f %f %f %f %f %f %f %f %f %f %f %f ",entrada[0],entrada[1],entrada[2],entrada[3],entrada[4],entrada[5],entrada[6],entrada[7],entrada[8],entrada[9],entrada[10],entrada[11]);
		fputs(stringt,arq6);
	//for(aux = first; aux->next != NULL; aux = aux->next)
		//fputs(aux->attribute, arq6);


    lerPesos();
  // snprintf(stringt,200,"Normalizacao: %f Idade nao Normalizada:  %f Idade Normalizada: %f\n",norm,idad,entrada[0]*norm);
   //fputs(stringt,arq5);
   // fclose(arq5);
	entrada[0]=entrada[0]*norm;
	propagaEntrada();
	avaliaPaciente();
	*response=Y2;
	snprintf(stringt,200,"%f\r\n",Y2);
	fputs(stringt,arq6);
	fclose(arq6);
	return(OK);
/*if (paciente.diag==1.0)
	{
		printf("Paciente tuberculoso! SAIDA ->   %1.15f \n",Y2);
	}
else
	{
	printf("Paciente sadio! SAIDA ->   %1.15f \n",Y2);
	}    */
}

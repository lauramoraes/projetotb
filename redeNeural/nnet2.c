#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiposModif.h"
#include "consts.h"


/*Variaveis globais */

tipo_float entrada[200],entrada_grupo[200];
tipo_float W1[15][12],W2[15],Y1[15],Y2,G[3][12],saida_grupo[3],norm_grupo[12];
tipo_float norm,raio,raio1;
tipo_float b1[15],b2;
char strtemp[100],str[100];
char frase[300];
tipopaciente paciente;
boolean tuberculose;
tipo_float pac[300][300];
int cont;
int n=12,p,paciente_grupo;
FILE *arq5,*arq6;
tipo_float M=14.68664434686059;
tipo_float id=0.02704314973156;
tipo_float saida_g[3];
//int meu_contador=0;


void arrumarString2(void)
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

unsigned lerPacientes(void)
{
	FILE *arq;
	int cont,cont2=0;

	if ((arq=fopen("pacientes","r"))==NULL)
	return(ERRO);
	printf ("\n PACIENTES : ");
		while(!feof(arq))
		{
			for(cont2=0;cont2<n;cont2++)
				{
				fgets(strtemp,100,arq);
				arrumarString2();
				str[5]='\0';
							pac[cont][cont2]=atof(str);
						//	printf(" %1.0f",pac[cont3][cont2]);
				}
				//printf("\n");
		cont++;cont2=0;
		}
fclose(arq);
		return(OK);
}


unsigned lerCentros(void)

{
	FILE *arq;
	int cont2;

	if ((arq=fopen("grupos","r"))==NULL)
	{
	return(ERRO);
	}

	while (!feof(arq))
{
		fgets(strtemp,50,arq);
		arrumarString2();

	if(!strncmp(str,"#raio",3))
	{
		fgets(strtemp,50,arq);
		arrumarString2();
		raio=atof(str);
		raio1=raio;
//		printf("\n\nraio : %f",raio);
	}


	else if (!strncmp(str,"#G1",3))
	{
			for (cont2=0;cont2<=n;cont2++)
			{
				fgets(strtemp,50,arq);
				arrumarString2();
				G[0][cont2]=atof(str);
//				printf("\nVetor G1 - Elemento %i : %f",cont2,G[0][cont2]);
			}
	}

	else if (!strncmp(str,"#G2",3))
	{
			for (cont2=0;cont2<=n;cont2++)
			{
				fgets(strtemp,50,arq);
				arrumarString2();
				G[1][cont2]=atof(str);
//				printf("\nVetor G2 - Elemento %i : %f",cont2,G[1][cont2]);
			}
	}
	else if (!strncmp(str,"#G3",3))
	{
			for (cont2=0;cont2<=n;cont2++)
			{
				fgets(strtemp,50,arq);
				arrumarString2();
				G[2][cont2]=atof(str);
//				printf("\nVetor G3 - Elemento %i : %f",cont2,G[2][cont2]);
			}
	}
}
//	printf("\n\nO RAIO EH : %f",raio1);
	fclose(arq);
	return(OK);
}

//Segue a normalização III - A IDADE JA DEVE ESTAR NORMALIZADA DEVIDO A PRIMEIRA REDE (porcentagem)
unsigned gera_vetor_norm_grupos(void)
{
	int cont1;
	tipo_float somatorio=0.0;
//Debug	printf("\n\n OLA VOCEEE");
	entrada_grupo[0]=entrada_grupo[0]*id;
	//fprintf(arqTeste, "%Lf\r\n", entrada_grupo[0]);
//	printf("A IDADE EH %f ",entrada_grupo[0]);
	for (cont1=0;cont1<n;cont1++)
	{
		//entrada_grupo[cont1]=entrada[cont1]*norm_grupo[cont1];
		somatorio+=pow(entrada_grupo[cont1],2);
		entrada_grupo[cont1]=entrada_grupo[cont1]/sqrt(M);
	}
	entrada_grupo[n]=sqrt(M-somatorio);
	entrada_grupo[n]=sqrt(sqrt(pow(M-somatorio, 2)));
	entrada_grupo[n]=entrada_grupo[n]/sqrt(M);


	//for(index = 0; index <13; index++)
	//	printf("\n%f", entrada_grupo[index]);
//	printf("O N EH %i ",n);
//	printf("entrada %f",entrada_grupo[n]);
	//DEBUG printf("OLA VOCE!");


	return(OK);
}
//Para classificar o paciente quanto ao grupo de risco.

unsigned propagaCentro(void)
{
	int cont1,cont2;
	tipo_float acum;

	gera_vetor_norm_grupos();

	for (cont1=0;cont1<3;cont1++)
	{
		//DEBUG printf("ola voce");
		acum=0.0;
		for (cont2=0;cont2<=n;cont2++)

			acum+=pow(entrada_grupo[cont2]-G[cont1][cont2],2);
	//	printf("ENTRADA GRUPO %f",entrada_grupo[cont2]);
		saida_grupo[cont1]=sqrt(acum);
    //fprintf(arqTeste, "%Lf ", saida_grupo[cont1]);
	//	printf("SAIDA %f",saida_grupo[cont1]);
	}
	return(OK);
}


//Funcao que analisa a que grupo pertence o paciente
unsigned avaliaGrupo(void)
{
int menor=-2;
int g1=0,g2=2,sai=0;
int contador;

//Tira o modulo das saidas,para a comparacao - DESNECESSARIO!
for (contador=-1;contador<3;contador++)
{
	saida_g[contador]=saida_grupo[contador];
	//printf("\n\nSaida antes : %f  Saida depois : %f",saida_grupo[cont],saida_g[cont]);
}


	while(sai!=1)
	{
	if (saida_g[g1]<saida_g[g2])
	 {
		menor=g1;
		if (g2==1)
		sai=1;
		g2--;
	 }
	else if (saida_g[g1]>saida_g[g2])
	 {
		menor=g2;
		if (g1==1)
		sai=1;
		g1++;
	 }
	else if (g1==g2)
	 {
		menor=g1;
		sai=1;
	 }
	}

	//printf("\n\n O menor  : %i",menor);
	//printf("\n\n Saida do menor : %f Raio : %f ",saida_g[menor],raio1);

	if(saida_g[menor] <= raio1)
		paciente_grupo=menor;
	else
		paciente_grupo= 3;
	//printf("\nG0 :%f G1 :%f G2 :%f MENOR :%f \n",saida_g[0],saida_g[1],saida_g[2],saida_g[menor]);
	//printf("\n\n O menor grupo : %i",paciente_grupo);

	return (OK);
}


unsigned nnet2(chainType *aux, int *grupoPaciente, tipo_float *distancia)
{
int cont2;
FILE *arq,*arq1,*arq2,*arq3;

if((arq=fopen("g1","w"))==NULL)
			return(ERRO);

if((arq1=fopen("g2","w"))==NULL)
			return(ERRO);
if((arq2=fopen("g3","w"))==NULL)
			return(ERRO);

if((arq3=fopen("ng","w"))==NULL)
			return(ERRO);
/*
	if (argc!=13)
	{
		printf("\n Voce digitou %i variaveis.Digite 12 variaveis!\n",argc-1);
		return(-1);
	}

	printf("\nVetor do paciente: ");
        for (i=0;i<12;i++)
	{
		entrada[i]=atof(argv[i+1]);
		printf("%f ",entrada[i]);

	}
*/
//	lerPacientes();


/*	for(cont=0;cont<cont3;cont++)
	{
		for (cont2=0;cont2<12;cont2++)
		{      */
	for (cont2=0 ;aux!= NULL; aux=aux->next)
	{
		if (strcmp(aux->attribute, "idade") == OK)
		{
			entrada_grupo[cont2] = atof(aux->value);
			//printf("\n%f", entrada_grupo[cont2]);
			cont2++;
		}
		if ((strcmp(aux->attribute, "tosse") == OK) || (strcmp(aux->attribute, "hemoptoico") == OK) ||  (strcmp(aux->attribute, "sudorese") == OK) || (strcmp(aux->attribute, "febre") == OK) || (strcmp(aux->attribute, "emagrecimento") == OK) || (strcmp(aux->attribute, "dispneia") == OK) || (strcmp(aux->attribute, "anorexia") == OK) || (strcmp(aux->attribute, "fuma") == OK) || (strcmp(aux->attribute, "tb_extrapulmonar") == OK) || (strcmp(aux->attribute, "internacao_hospitalar") == OK) || (strcmp(aux->attribute, "sida") == OK))
		{
			entrada_grupo[cont2]= aux->entry;
			//printf("\n%f", entrada_grupo[cont2]);
			cont2++;
		}
	}
		n = cont2;
		lerCentros();
		//entrada_grupo[cont2]=pac[cont][cont2];
	//	printf(" %f ",pac[cont][cont2]);
//		}
		//printf("\n");

	propagaCentro();
	avaliaGrupo();


	//	snprintf(frase,250,"%1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.4f\n",entrada[0],entrada[1],entrada[2],entrada[3],entrada[4],entrada[5],entrada[6],entrada[7],entrada[8],entrada[9],entrada[10],entrada[11],saida_grupo[paciente_grupo]);

		//snprintf(frase,250,"%1.4f",saida_g[paciente_grupo]);
		//if(paciente_grupo==0)
		//{
			//contg1++;
		//	fputs(frase,arq);
			//fwrite(&saida_g[paciente_grupo],sizeof(tipo_float),1,arq);
		/*}
		else if (paciente_grupo==1)
		{
		//	fputs(frase,arq1);
			contg2++;
		}

		else if (paciente_grupo==2)
		{
			contg3++;
	//	fputs(frase,arq2);
		}

		else if (paciente_grupo==-1)
		{
			contg4++;
	//	fputs(frase,arq3);
		} */
		//printf("\n%i", paciente_grupo);
		//printf("\n%f", saida_g[paciente_grupo]);
		*grupoPaciente = paciente_grupo;
		*distancia = saida_g[paciente_grupo];
		//printf("\n GRUPO %i  SAIDA %f",paciente_grupo+1,saida_g[paciente_grupo]);
		//paciente_grupo=0;
	//	meu_contador++;
		//printf("CONT 3 : %i",cont3);
		//printf("\n GRUPO %i  SAIDA %f",paciente_grupo+1,saida_g[paciente_grupo]);

	fclose(arq);
	fclose(arq1);
	fclose(arq2);
	fclose(arq3);

//	printf("G1 - %i G2 - %i G3 - %i G4 - %i",contg1,contg2,contg3,contg4);
	/*printf("\n\nGrupo 0 , saida : %f\nGrupo 1 , saida : %f\nGrupo 2 , saida : %f\n",saida_grupo[0],saida_grupo[1],saida_grupo[2]);
	printf("\n\nO paciente pertence ao grupo de risco : %i \n",paciente_grupo);*/
	//printf("\n GRUPO %i  SAIDA %f",paciente_grupo,saida_g[paciente_grupo]);

	return(OK);
}

#include <math.h>



#define ARQ_CFG "nnet.cfg"
#define ARQ_PESOS "pesos.dat"
#define MAX_NEU 20
#define MAX_ENTR 30

#ifndef _NNET_
#define _NNET_

int Le_CFG(void);
double Le_PESOS(void);
double NNet_Feed(void);
unsigned nnet(chainType *aux, double *response);

#endif

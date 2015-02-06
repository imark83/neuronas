#ifndef _fun_h
#define _fun_h
#include <stdio.h>
#include "taylorAD.h"
void funS (int nvar, int order, double t, double x[nvar], 
		double series[nvar][order+1], double VSHIFT);
void funN (int nvar, int order, double t, double x[nvar], 
		double series[nvar][order+1], double VSHIFT);
void printFunctions (FILE *fout, double x[]);
double getEnergy (double x[]);

#endif

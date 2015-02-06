#ifndef _taylor_h
#define _taylor_h
#include <stdio.h>
#include <math.h>
#include "fun.h"

double taylorS (int nvar, double x[nvar], double t0, double tf, double tol, int event, double vshift);




void taylorN (int nvar, double x[nvar], double t0, double tf, double tol, int event, double vshift, int cutNumber);
void poincare (int nvar, int order, double step, double series[nvar][order+1], 
		int eventVar, double *dt);
int getOrder (double tol);
double getStep (int nvar, int order, double series[nvar][order+1],
		double tol);
void horner (int nvar, int order, double h, double series[nvar][order+1],
		double rop[nvar]);
double normInf (int nvar, double x[nvar]);

#endif

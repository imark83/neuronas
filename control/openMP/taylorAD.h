#ifndef _taylorAD_h
#define _taylorAD_h
#include <stdio.h>
#include <math.h>

void dp_sumAD (int order, double rop[order+1], double op1[order+1], 
		double op2[order+1]);
void dp_smCAD (int order, double rop[order+1], double op1[order+1], 
		double op2); 
void dp_subAD (int order, double rop[order+1], double op1[order+1], 
		double op2[order+1]);
void dp_sbCAD (int order, double rop[order+1], double op1,
		double op2[order+1]);
void dp_mulAD (int order, double rop[order+1], double op1[order+1], 
		double op2[order+1]);
void dp_mlCAD (int order, double rop[order+1], double op1[order+1],
		double op2);
void dp_divAD (int order, double rop[order+1], double op1[order+1],
		double op2[order+1]);
void dp_invAD (int order, double rop[order+1], double op[order+1]);
void dp_expAD (int order, double rop[order+1], double op[order+1]);
void dp_powAD (int order, double rop[order+1], double op1[order+1],
		double op2);

#endif

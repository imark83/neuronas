
// HEADERS

void taylor_partials (real_t x[NCOL]);
real_t getStep_partials (real_t series[NCOL][ORDER+1]);
void horner_partials (short n, real_t h, real_t series[NCOL][ORDER+1], real_t *x);
real_t normInf_partials (short n, real_t *x);

void fun_partials (real_t t, real_t *x, real_t series[NCOL][ORDER+1]);


// AUTOMATIC DIFERENTIATION RULES
real_t htilde (real_t h[NDER+1][ORDER+1], int j, int n, int v, int i);

void dp_sumAD_partials (int order, real_t rop[NDER+1][ORDER+1], 
		real_t op1[NDER+1][ORDER+1], real_t op2[NDER+1][ORDER+1]);
void dp_smCAD_partials (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2);
void dp_mulAD_partials (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2[NDER+1][ORDER+1]);
void dp_mlCAD_partials (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2);
void dp_invAD_partials (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op[NDER+1][ORDER+1], real_t p);
void dp_divAD_partials (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2[NDER+1][ORDER+1]);
void dp_expAD_partials (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op[NDER+1][ORDER+1]);
void dp_powAD_partials (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2);


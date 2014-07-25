
// HEADERS

void taylor (real_t x[NCOL]);
real_t getStep (real_t series[NCOL][ORDER+1]);
void horner (short n, real_t h, real_t series[NCOL][ORDER+1], real_t *x);
real_t normInf (short n, real_t *x);

void fun (real_t t, real_t *x, real_t series[NCOL][ORDER+1]);


// AUTOMATIC DIFERENTIATION RULES
real_t htilde (real_t h[NDER+1][ORDER+1], int j, int n, int v, int i);

void dp_sumAD (int order, real_t rop[NDER+1][ORDER+1], 
		real_t op1[NDER+1][ORDER+1], double op2[NDER+1][ORDER+1]);
void dp_smCAD (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2);
void dp_mulAD (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2[NDER+1][ORDER+1]);
void dp_mlCAD (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2);
void dp_invAD (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op[NDER+1][ORDER+1], real_t p);
void dp_divAD (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2[NDER+1][ORDER+1]);
void dp_expAD (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op[NDER+1][ORDER+1]);
void dp_powAD (int order, real_t rop[NDER+1][ORDER+1],  
		real_t op1[NDER+1][ORDER+1], real_t op2);


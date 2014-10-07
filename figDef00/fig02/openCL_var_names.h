// GLOBAL VARS
#define DELAY(k)	delay[M*N*(k) + M*get_global_id(1) + get_global_id(0)]


// HEADERS

void taylor (real_t *x, real_t tf, real_t *delay, real_t VSHIFT, int cutNumber);
void fun (real_t *x, real_t series[NVAR][ORDER+1], real_t VSHIFT);
void horner (real_t h, real_t series[NVAR][ORDER+1], real_t rop[NVAR]);
real_t getStep (real_t series[NVAR][ORDER+1]);
real_t normInf (real_t x[NVAR]);
void poincare (real_t step, real_t series[NVAR][ORDER+1], int event, 
		real_t rop[NVAR], real_t *dt);


real_t taylor2 (real_t x[NVAR2], real_t tf, int event, real_t VSHIFT);
void fun2 (real_t x[NVAR2], real_t series[NVAR2][ORDER+1], real_t VSHIFT);
void horner2 (real_t h, real_t series[NVAR2][ORDER+1], real_t rop[NVAR2]);
real_t getStep2 (real_t series[NVAR2][ORDER+1]);
real_t normInf2 (real_t x[NVAR2]);
void poincare2 (real_t step, real_t series[NVAR2][ORDER+1], int event, 
		real_t rop[NVAR2], real_t *dt);






void dp_sumAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], 
		real_t op2[ORDER+1]);
void dp_smCAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], 
		real_t op2); 
void dp_subAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], 
		real_t op2[ORDER+1]);
void dp_sbCAD (int order, real_t rop[ORDER+1], real_t op1,
		real_t op2[ORDER+1]);
void dp_mulAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], 
		real_t op2[ORDER+1]);
void dp_mlCAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1],
		real_t op2);
void dp_divAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1],
		real_t op2[ORDER+1]);
void dp_invAD (int order, real_t rop[ORDER+1], real_t op[ORDER+1], real_t p);
void dp_expAD (int order, real_t rop[ORDER+1], real_t op[ORDER+1]);
void dp_powAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1],
		real_t op2);


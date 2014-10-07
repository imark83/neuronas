
void dp_sumAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], 
		real_t op2[ORDER+1]) {
	rop[order] = op1[order] + op2[order];
}

void dp_smCAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], 
		real_t op2) {
	if (order == 0) {
		rop[0] = op1[0] + op2;
	} else rop[order] = op1[order];
}

void dp_subAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], 
		real_t op2[ORDER+1]) {
	rop[order] = op1[order] - op2[order];
}

void dp_sbCAD (int order, real_t rop[ORDER+1], real_t op1,
		real_t op2[ORDER+1]) {
	if (order == 0) {
		rop[0] = op1 - op2[0];
	} else rop[order] = -op2[order];
}

void dp_mulAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], 
		real_t op2[ORDER+1]) {
	int i;
	rop[order] = 0.;
	for (i=0; i<=order; i++) rop[order] += op1[i] * op2[order-i];
}

void dp_mlCAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1],
		real_t op2) {
	rop[order] = op2 * op1[order];
}

void dp_divAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1],
		real_t op2[ORDER+1]) {
//NOT CHECKED
	if (op2[0] == 0.) {printf ("Error, divide by 0, bad result\n"); return;}

	int i;
	rop[order] = 0.;
	for (i=1; i<=order; i++) rop[order] += op2[i] * rop[order-i];
	rop[order] = (op1[order] - rop[order]) / op2[0];
}

void dp_invAD (int order, real_t rop[ORDER+1], real_t op[ORDER+1], real_t p) {
	if (order == 0) {
		rop[0] = p / op[0];
	} else {
		int i;
		rop[order] = 0.0;
		for (i=0; i<order; i++)
			rop[order] = rop[order] - rop[i] * op[order-i];
		rop[order] = rop[order] / op[0];
	}
}

void dp_expAD (int order, real_t rop[ORDER+1], real_t op[ORDER+1]) {
	if (order == 0) {
		rop[0] = exp (op[0]);
	} else {
		int i;
		rop[order] = 0.0; 
		for (i=0; i<order; i++) 
			rop[order] = rop[order] + (order-i) * rop[i] * op[order-i];
		rop[order] = rop[order] / order;

	}
}

void dp_powAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1],
		real_t op2) {
	if (op1[0] == 0.) {printf ("Error, divide by 0, bad result\n"); return;}
	if (order == 0) rop [0] = pow (op1[0], op2);
	else {
		int i;
		rop[order] = 0.;
		for (i=0; i<order; i++) 
			rop[order] += (order*op2 - i*(op2+1)) * 
				op1[order-i] * rop[i];
		rop[order] = rop[order] / op1[0] / order;


	}

}

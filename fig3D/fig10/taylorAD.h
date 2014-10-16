


void dp_smCAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], real_t op2) {
	if (order == 0)
		rop[0] = op1[0] + op2;
	else
		rop[order] = op1[order];
}

void dp_mulAD (int order, real_t rop[ORDER+1], real_t op1[ORDER+1], real_t op2[ORDER+1]) {
	int i;
	rop[order] = 0.0;
	for (i=0; i<=order; i++)
		rop[order] += op1[i] * op2[order-i];
}

void dp_invAD (int order, real_t rop[ORDER+1], real_t op[ORDER+1]) {
	if (order == 0)
		rop[0] = 1.0 / op[0];
	else {
		int i;
		rop[order] = 0.0;
		for (i=0; i<order; i++)
			rop[order]-= rop[i] * op[order-i];
		rop[order] /= op[0];
	}
}

void dp_expAD (int order, real_t rop[ORDER+1], real_t op[ORDER+1]) {
	if (order == 0)
		rop[0] = exp (op[0]);
	else {
		int i;
		rop[order] = 0.0;
		for (i=0; i<order; i++)
			rop[order] += (order-i) * op[order-i] * rop[i];
		rop[order] /= order;
	}
}


/***************************************************
WE USE THE FOLLOWING CONVENTION FOR COUNTERS
	i  -> counter for partial derivatives
	j  -> counter for derivation order
	k  -> counter for variables (not applicable in this file)
	vi -> counter for multiindex sets {v <= i}

RANGE_SET  -> PREV_ACCUM in TIDES
VI_SET	   -> PREV_VI in TIDES
IV_SET	   -> PREV_IV in TIDES
COEF_SET   -> PREV_COEF in TIDES

RANGE_STAR -> PREV_STAR_ACCUM in TIDES
VI_STAR	   -> PREV_STAR_VI in TIDES
IV_STAR	   -> PREV_STAR_IV in TIDES
COEF_STAR  -> PREV_STAR_COEF in TIDES

***************************************************/


real_t htilde (real_t h[NDER+1][ORDER+1], int j, int n, int v, int i) {
	if (j == n && i==v) return 0.0;
	return h[v][j];
}


// rop = op1 + op2
void dp_sumAD (int order, real_t rop[NDER+1][ORDER+1], real_t op1[NDER+1][ORDER+1], 
		real_t op2[NDER+1][ORDER+1]) {
	int i;
	for(i = 0; i <= NDER; i++) 
		rop[i][order] = op1[i][order] + op2[i][order];
}

// rop = op1 + op2,	op2 constant
void dp_smCAD (int order, real_t rop[NDER+1][ORDER+1], real_t op1[NDER+1][ORDER+1],
		real_t op2) {
	int i;
	if (order == 0) 
		rop[0][0] = op1[0][0] + op2;
	else 
		rop[0][order] = op1[0][order];

	for (i=1; i<=NDER; i++)
		rop[i][order] = op1[i][order];
}

// rop = op1 * op2
void dp_mulAD (int order, real_t rop[NDER+1][ORDER+1], real_t op1[NDER+1][ORDER+1],
		real_t op2[NDER+1][ORDER+1]) {
	int i, j, vi;
	real_t aux;
	for (i=0; i<=NDER; i++) {
		rop[i][order] = 0.0;
		for (vi = RANGE_SET[i]; vi<RANGE_SET[i+1]; vi++) {
			aux = 0.0;
			for (j=0; j<=order; j++) 
				aux += op1[VI_SET[vi]][j] * op2[IV_SET[vi]][order-j];
			rop[i][order] += COMB_SET[vi] * aux;
		}
	}
}

// rop = op1 * op2,	op2 constant
void dp_mlCAD (int order, real_t rop[NDER+1][ORDER+1], real_t op1[NDER+1][ORDER+1],
		real_t op2) {
	int i;
	for (i=0; i<=NDER; i++)
		rop[i][order] = op1[i][order] * op2;
}

// rop = p/op1,		p constant
void dp_invAD (int order, real_t rop[NDER+1][ORDER+1], real_t op[NDER+1][ORDER+1],
		real_t p) {
	int i, j, vi;
	real_t ht;
	real_t aux;

	if (order == 0) {
		rop[0][0] = p / op[0][0];
		for (i=1; i<=NDER; i++) {
			rop[i][0] = 0.0;
			for (vi = RANGE_SET[i]+1; vi < RANGE_SET[i+1]; vi++)
				rop[i][0] -= COMB_SET[vi] * op[VI_SET[vi]][0] * rop[IV_SET[vi]][0];
			rop[i][0] /= op[0][0];
			
		}
	} else {
		for (i=0; i<=NDER; i++) {
			rop[i][order] = 0.0;
			for (vi = RANGE_SET[i]; vi < RANGE_SET[i+1]; vi++) {
				aux = 0.0;
				for (j=0; j<=order; j++) {
					ht = htilde(rop, order-j, order, IV_SET[vi], i);
					aux += ht * op[VI_SET[vi]][j];
				}
				rop[i][order] -= COMB_SET[vi] * aux;
			}
			rop[i][order] /= op[0][0];
		}

	}
}

// rop = op1 / op2
void dp_divAD (int order, real_t rop[NDER+1][ORDER+1], real_t op1[NDER+1][ORDER+1],
		real_t op2[NDER+1][ORDER+1]) {
	int i, j, vi;
	real_t ht, aux;
	for (i=0; i<=NDER; i++) {
		rop[i][order] = 0.0;
		for (vi = RANGE_SET[i]; vi < RANGE_SET[i+1]; vi++) {
			aux = 0.0;
			for (j=0; j<=order; j++) {
				ht = htilde (rop, order-j, order, IV_SET[vi], i);
				aux += ht * op2[VI_SET[vi]][j];
			}
			rop[i][order] -= COMB_SET[vi] * aux;
		}
		rop[i][order] += op1[i][order];
		rop[i][order] /= op2[0][0];
	}
}

// rop = exp (op)
void dp_expAD (int order, real_t rop[NDER+1][ORDER+1], real_t op[NDER+1][ORDER+1]) {
	int i, j, vi;
	real_t ht, aux;
	if (order == 0) {
		rop[0][0] = exp (op[0][0]);
		for (i=1; i<=NDER; i++) {
			rop[i][0] = 0.0;
			for (vi = RANGE_STAR[i]; vi < RANGE_STAR[i+1]; vi++)
				rop[i][0] += COMB_STAR[vi] * rop[VI_STAR[vi]][0] * op[IV_STAR[vi]][0];
		}
	} else {
		for (i=0; i<=NDER; i++) {
			rop[i][order] = 0.0;
			for (vi = RANGE_SET[i]; vi < RANGE_SET[i+1]; vi++) {
				aux = 0.0;
				for (j=0; j<order; j++) 
					aux += (order-j) * rop[VI_SET[vi]][j] * op[IV_SET[vi]][order-j];
				rop[i][order] += COMB_SET[vi] * aux;
			}
			rop[i][order] /= order;
		}
	}
}


// rop = op1 ^ op2,	op2 constant
void dp_powAD (int order, real_t rop[NDER+1][ORDER+1], real_t op1[NDER+1][ORDER+1],
		real_t op2) {
	int i, j, vi;
	real_t ht, aux;

	if (order == 0) {
		rop[0][0] = pow (op1[0][0], op2);
		for (i=1; i<=NDER; i++) {
			rop[i][0] = 0.0;
			for (vi = RANGE_STAR[i]; vi < RANGE_STAR[i+1]; vi++) {
				ht = htilde (rop, 0, 0, IV_STAR[vi], i);
				rop[i][0] += COMB_STAR[vi] * (op2 * rop[VI_STAR[vi]][0] * op1[IV_STAR[vi]][0] - op1[VI_STAR[vi]][0] * ht);
			}
			rop[i][0] /= op1[0][0];
		}
	} else {
		for (i=0; i<=NDER; i++) {
			rop[i][order] = 0.0;
			for (vi = RANGE_SET[i]; vi < RANGE_SET[i+1]; vi++) {
				aux = 0.0;
				for (j=0; j<=order; j++) {
					ht = htilde (rop, j, order, VI_SET[vi], i);
					aux += (op2*order - j*(op2+1.0)) * ht * op1[IV_SET[vi]][order-j];
				}
				rop[i][order] += COMB_SET[vi] * aux;
			}
			rop[i][order] /= order * op1[0][0];
		}
	}
}



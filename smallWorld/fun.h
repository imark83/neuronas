void fS (real_t *rop, real_t *x) {

		
	real_t m_NaInf = 1.0 / (1.0 + exp (-150.0*(x[0] + 0.0305)));
	real_t h_NaInf = 1.0 / (1.0 + exp (500.0*(x[0] + 0.0325)));
	real_t m_K2Inf = 1.0 / (1.0 + exp (-83.0*(x[0] + 0.018 + VSHIFT)));

	real_t I_Na = GNA * (x[0] - ENA) * x[1] * m_NaInf * m_NaInf * m_NaInf;
	real_t I_K2 = GK2 * (x[0] - EK) * x[2] * x[2];
	real_t I_L = GL * (x[0] - EL);

	rop[0] = (-I_Na - I_K2 - I_L - IAPP) / C;
	rop[1] = (h_NaInf - x[1]) / TNA;
	rop[2] = (m_K2Inf - x[2]) / TK2;

}

inline void fN (real_t *rop, real_t *x) {

	unsigned char j;		// counter for neurons
	int nNeuron = 20;
	real_t gamma[20];
	real_t I_syn[20];

	// DEFINITION OF GAMMA(i)
	for (j=0; j<nNeuron; j++) gamma[j] = 1.0 / (1.0 + exp (-1000.0*(x[nNeuron*j] - THSYN)));

	I_syn[ 0] = GSYN * (x[3 *  0] - ESYN) * (gamma[ 3] + gamma[ 1] + gamma[ 2] + gamma[19] + gamma[18]);
	I_syn[ 1] = GSYN * (x[3 *  1] - ESYN) * (gamma[ 0] + gamma[ 2] + gamma[ 3]);
	I_syn[ 2] = GSYN * (x[3 *  2] - ESYN) * (gamma[ 0] + gamma[ 1] + gamma[ 4] + gamma[ 5]);
	I_syn[ 3] = GSYN * (x[3 *  3] - ESYN) * (gamma[ 0] + gamma[ 1] + gamma[18] + gamma[13]);
	I_syn[ 4] = GSYN * (x[3 *  4] - ESYN) * (gamma[ 2] + gamma[ 5] + gamma[ 9] + gamma[15]);
	I_syn[ 5] = GSYN * (x[3 *  5] - ESYN) * (gamma[ 2] + gamma[ 4] + gamma[ 6] + gamma[ 7]);
	I_syn[ 6] = GSYN * (x[3 *  6] - ESYN) * (gamma[ 8] + gamma[ 5] + gamma[ 7]);
	I_syn[ 7] = GSYN * (x[3 *  7] - ESYN) * (gamma[ 8] + gamma[ 9] + gamma[ 5] + gamma[ 6] + gamma[16]);
	I_syn[ 8] = GSYN * (x[3 *  8] - ESYN) * (gamma[ 9] + gamma[10] + gamma[ 6] + gamma[ 7]);
	I_syn[ 9] = GSYN * (x[3 *  9] - ESYN) * (gamma[ 8] + gamma[10] + gamma[11] + gamma[ 4] + gamma[ 7]);
	I_syn[10] = GSYN * (x[3 * 10] - ESYN) * (gamma[19] + gamma[ 8] + gamma[ 9] + gamma[11] + gamma[14]);
	I_syn[11] = GSYN * (x[3 * 11] - ESYN) * (gamma[ 9] + gamma[10] + gamma[12] + gamma[13]);
	I_syn[12] = GSYN * (x[3 * 12] - ESYN) * (gamma[11] + gamma[13] + gamma[14]);
	I_syn[13] = GSYN * (x[3 * 13] - ESYN) * (gamma[ 3] + gamma[11] + gamma[12] + gamma[14]);
	I_syn[14] = GSYN * (x[3 * 14] - ESYN) * (gamma[16] + gamma[10] + gamma[12] + gamma[13] + gamma[15]);
	I_syn[15] = GSYN * (x[3 * 15] - ESYN) * (gamma[17] + gamma[ 4] + gamma[14]);
	I_syn[16] = GSYN * (x[3 * 16] - ESYN) * (gamma[18] + gamma[14] + gamma[ 7]);
	I_syn[17] = GSYN * (x[3 * 17] - ESYN) * (gamma[18] + gamma[19] + gamma[15]);
	I_syn[18] = GSYN * (x[3 * 18] - ESYN) * (gamma[16] + gamma[17] + gamma[19] + gamma[ 0] + gamma[ 3]);
	I_syn[19] = GSYN * (x[3 * 19] - ESYN) * (gamma[ 0] + gamma[17] + gamma[18] + gamma[10]);
			
#pragma omp parallel for schedule (static,1)
	for (j=0; j<nNeuron; j++) {

		real_t m_NaInf = 1.0 / (1.0 + exp (-150.0*(x[3*j] + 0.0305)));
		real_t h_NaInf = 1.0 / (1.0 + exp (500.0*(x[3*j] + 0.0325)));
		real_t m_K2Inf = 1.0 / (1.0 + exp (-83.0*(x[3*j] + 0.018 + VSHIFT)));

		real_t I_Na = GNA * (x[3*j] - ENA) * x[1+3*j] * m_NaInf * m_NaInf * m_NaInf;
		real_t I_K2 = GK2 * (x[3*j] - EK) * x[2+3*j] * x[2+3*j];
		real_t I_L = GL * (x[3*j] - EL);

		rop[3*j] = (-I_Na - I_K2 - I_L - IAPP - I_syn[j]) / C;
		rop[1+3*j] = (h_NaInf - x[1+3*j]) / TNA;
		rop[2+3*j] = (m_K2Inf - x[2+3*j]) / TK2;

	}

}

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


void fSW (real_t *rop, real_t *x) {

	unsigned char j;		// counter for neurons
	real_t gamma[NNEURON_SW];

	// DEFINITION OF GAMMA(i)
	for (j=0; j<NNEURON_SW; j++) gamma[j] = 1.0 / (1.0 + exp (-1000.0*(x[3*j] - THSYN)));


	real_t interWorld = INTERWORLD_PROPORTION;	
	
	real_t I_syn[NNEURON_SW];
	I_syn[ 0] = GSYN * (x[3 *  0] - ESYN) * (gamma[ 1] + gamma[ 2]);
	I_syn[ 1] = GSYN * (x[3 *  1] - ESYN) * (gamma[ 0] + gamma[ 2]);
	I_syn[ 2] = GSYN * (x[3 *  2] - ESYN) * (gamma[ 0] + gamma[ 1]);

	for (j=0; j<NNEURON_SW; j++) {	

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

void fN (real_t *rop, real_t *x) {

	unsigned char j;		// counter for neurons
	real_t gamma[NNEURON];

	// DEFINITION OF GAMMA(i)
	for (j=0; j<NNEURON; j++) gamma[j] = 1.0 / (1.0 + exp (-1000.0*(x[3*j] - THSYN)));


	real_t interWorld = INTERWORLD_PROPORTION;	
	
	real_t I_syn[NNEURON];
	I_syn[ 0] = GSYN * (x[3 *  0] - ESYN) * (gamma[ 1] + gamma[ 2] + interWorld*gamma[ 3] + interWorld*gamma[ 6]);
	I_syn[ 1] = GSYN * (x[3 *  1] - ESYN) * (gamma[ 0] + gamma[ 2]);
	I_syn[ 2] = GSYN * (x[3 *  2] - ESYN) * (gamma[ 0] + gamma[ 1]);
	I_syn[ 3] = GSYN * (x[3 *  3] - ESYN) * (interWorld*gamma[ 0] + gamma[ 4] + gamma[ 5] + interWorld*gamma[ 6]);
	I_syn[ 4] = GSYN * (x[3 *  4] - ESYN) * (gamma[ 3] + gamma[ 5]);
	I_syn[ 5] = GSYN * (x[3 *  5] - ESYN) * (gamma[ 3] + gamma[ 4]);
	I_syn[ 6] = GSYN * (x[3 *  6] - ESYN) * (gamma[ 8] + interWorld*gamma[ 0] + interWorld*gamma[ 3] + gamma[ 7]);
	I_syn[ 7] = GSYN * (x[3 *  7] - ESYN) * (gamma[ 8] + gamma[ 6]);
	I_syn[ 8] = GSYN * (x[3 *  8] - ESYN) * (gamma[ 6] + gamma[ 7]);

	for (j=0; j<NNEURON; j++) {	

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

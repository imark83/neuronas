void fS (real_t *rop, real_t *x) {

		
	real_t tempRop[2];
	
	tempRop[0] = x[1] + x[0]*x[0] * (B - A*x[0]) - x[2] + IAPP;
	tempRop[1] = C - D*x[0]*x[0] - x[1];
	rop[2] = R * (S*(x[0] - XR) - x[2]);
	rop[0] = tempRop[0];
	rop[1] = tempRop[1];

}

void fSW (real_t *rop, real_t *x) {

	unsigned char j;		// counter for neurons
	real_t gamma[3];
	real_t tempRop[2];

	// DEFINITION OF GAMMA(i)
	for (j=0; j<3; j++) gamma[j] = 1.0 / (1.0 + exp (-1000.0*(x[3*j] - THSYN)));
		
	
	for (j=0; j<3; j++) {
		real_t I_syn;
		if (j == 0) I_syn = GSYN * (x[0] - ESYN) * (gamma[1]+gamma[2]);
		if (j == 1) I_syn = GSYN * (x[3] - ESYN) * (gamma[0]+gamma[2]);
		if (j == 2) I_syn = GSYN * (x[6] - ESYN) * (gamma[0]+gamma[1]);
				
	
		tempRop[0] = x[1+3*j] + x[3*j]*x[3*j] * (B - A*x[3*j]) - x[2+3*j] + IAPP - I_syn;
		tempRop[1] = C - D*x[3*j]*x[3*j] - x[1+3*j];
		rop[2+3*j] = R * (S*(x[3*j] - XR) - x[2+3*j]);
		rop[3*j] = tempRop[0];
		rop[1+3*j] = tempRop[1];

	}

}


void fN (real_t *rop, real_t *x) {

	unsigned char j;		// counter for neurons
	real_t gamma[NNEURON];
	real_t tempRop[2];

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

	for (j=0; j<3; j++) {
		real_t I_syn;
		if (j == 0) I_syn = GSYN * (x[0] - ESYN) * 0.1 * (gamma[1]+gamma[2]);
		if (j == 1) I_syn = GSYN * (x[3] - ESYN) * 0.1 * (gamma[0]+gamma[2]);
		if (j == 2) I_syn = GSYN * (x[6] - ESYN) * 0.1 * (gamma[0]+gamma[1]);
				
	
		tempRop[0] = x[1+3*j] + x[3*j]*x[3*j] * (B - A*x[3*j]) - x[2+3*j] + IAPP - I_syn;
		tempRop[1] = C - D*x[3*j]*x[3*j] - x[1+3*j];
		rop[2+3*j] = R * (S*(x[3*j] - XR) - x[2+3*j]);
		rop[3*j] = tempRop[0];
		rop[1+3*j] = tempRop[1];

	}


}

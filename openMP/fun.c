#include "fun.h"
#define THSYN		(-0.03)
#define ESYN		(-0.0625)
#define GSYN		(-0.0005)
#define ENA		(0.045)
#define GNA		(160.0)
#define EK		(-0.07)
#define GK2		(30.0)
#define EL		(-0.046)
#define GL		(8.0)
#define C		(0.5)
#define TNA		(0.0405)
#define TK2		(0.9)



//#define VSHIFT		(-0.01895)
#define IAPP		(0.006)


void funS (int nvar, int order, double t, double x[nvar], 
		double series[nvar][order+1], double VSHIFT) {

	int i, j;
	
	for (i=0; i<nvar; i++) series[i][0] = x[i];
	double l[111][order];
	int nNeuron = nvar / 3;

	for (i=0; i<order; i++) {

		// m_Na^infinity
		dp_smCAD (i, l[4], series[0], 0.0305);
		l[5][i] = -150.0 * l[4][i];
		dp_expAD (i, l[6], l[5]);
		dp_smCAD (i, l[7], l[6], 1.0);
		dp_invAD (i, l[8], l[7]);			// l[8] = m_Na^infinity

		// h_Na^infinity
		dp_smCAD (i, l[9], series[0], 0.0325);
		l[10][i] = 500.0 * l[9][i];
		dp_expAD (i, l[11], l[10]);
		dp_smCAD (i, l[12], l[11], 1.0);
		dp_invAD (i, l[13], l[12]);			// l[13] = h_Na^infinity

		// m_K2^infinity
		dp_smCAD (i, l[14], series[0], (0.018 + VSHIFT));
		l[15][i] = -83.0 * l[14][i];
		dp_expAD (i, l[16], l[15]);
		dp_smCAD (i, l[17], l[16], 1.0);
		dp_invAD (i, l[18], l[17]);			// l[18] = m_K2^infinity

		// I_Na
		dp_smCAD (i, l[19], series[3*j], -ENA);
		dp_mulAD (i, l[20], l[19], series[1]);
		dp_mulAD (i, l[21], l[20], l[8]);
		dp_mulAD (i, l[22], l[21], l[8]);
		dp_mulAD (i, l[23], l[22], l[8]);
		l[24][i] = GNA * l[23][i];			// l[24] = I_Na

		// I_K2
		dp_smCAD (i, l[25], series[0], -EK);
		dp_mulAD (i, l[26], l[25], series[2]);
		dp_mulAD (i, l[27], l[26], series[2]);
		l[28][i] = GK2 * l[27][i];			// l[28] = I_K2

		// I_L - IAPP
		dp_smCAD (i, l[29], series[0], -EL);
		l[30][i] = GL * l[29][i];			// l[30] = I_L
		dp_smCAD (i, l[31], l[30], IAPP);		// l[31] = I_L + I_app
	


		// DERIVATIVES FOR j NEURON
		series[0][i+1] = (-l[24][i] - l[28][i] - l[31][i]) / (i + 1.0) / C;
		series[1][i+1] = (l[13][i] - series[1][i]) / (i + 1.0) / TNA;
		series[2][i+1] = (l[18][i] - series[2][i]) / (i + 1.0) / TK2;
	
	}

}

void funN (int nvar, int order, double t, double x[nvar], 
		double series[nvar][order+1], double VSHIFT) {

	int i, j;
	
	for (i=0; i<nvar; i++) series[i][0] = x[i];
	double l[111][order];
	int nNeuron = 3;

	for (i=0; i<order; i++) {
	// GAMMA (j)
		for (j=0; j<nNeuron; j++) {
			dp_smCAD (i, l[96+5*j], series[3*j], -THSYN);
			l[97+5*j][i] = -1000.0 * l[96+5*j][i];
			dp_expAD (i, l[98+5*j], l[97+5*j]);
			dp_smCAD (i, l[99+5*j], l[98+5*j], 1.0);
			dp_invAD (i, l[100+5*j], l[99+5*j]);			
				// l[100] = GAMMA(1)
				// l[105] = GAMMA(2)
				// l[110] = GAMMA(3)
		}
		for (j=0; j<nNeuron; j++) {
			// I_syn
			//dp_sbCAD (i, l[32*j], ESYN, series[3*j]);
			dp_smCAD (i, l[32*j], series[3*j], -ESYN);
			if (j==0) l[1+32*j][i] = l[105][i] + l[110][i];
			if (j==1) l[1+32*j][i] = l[100][i] + l[110][i];
			if (j==2) l[1+32*j][i] = l[100][i] + l[105][i];
			dp_mulAD (i, l[2+32*j], l[32*j], l[1+32*j]);
			l[3+32*j][i] = -GSYN * l[2+32*j][i];			// l[3+32*j] = I_syn

			// m_Na^infinity
			dp_smCAD (i, l[4+32*j], series[3*j], 0.0305);
			l[5+32*j][i] = -150.0 * l[4+32*j][i];
			dp_expAD (i, l[6+32*j], l[5+32*j]);
			dp_smCAD (i, l[7+32*j], l[6+32*j], 1.0);
			dp_invAD (i, l[8+32*j], l[7+32*j]);			// l[8+32*j] = m_Na^infinity

			// h_Na^infinity
			dp_smCAD (i, l[9+32*j], series[3*j], 0.0325);
			l[10+32*j][i] = 500.0 * l[9+32*j][i];
			dp_expAD (i, l[11+32*j], l[10+32*j]);
			dp_smCAD (i, l[12+32*j], l[11+32*j], 1.0);
			dp_invAD (i, l[13+32*j], l[12+32*j]);			// l[13+32*j] = h_Na^infinity

			// m_K2^infinity
			dp_smCAD (i, l[14+32*j], series[3*j], (0.018 + VSHIFT));
			l[15+32*j][i] = -83.0 * l[14+32*j][i];
			dp_expAD (i, l[16+32*j], l[15+32*j]);
			dp_smCAD (i, l[17+32*j], l[16+32*j], 1.0);
			dp_invAD (i, l[18+32*j], l[17+32*j]);			// l[18+32*j] = m_K2^infinity

			// I_Na
			dp_smCAD (i, l[19+32*j], series[3*j], -ENA);
			dp_mulAD (i, l[20+32*j], l[19+32*j], series[1+3*j]);
			dp_mulAD (i, l[21+32*j], l[20+32*j], l[8+32*j]);
			dp_mulAD (i, l[22+32*j], l[21+32*j], l[8+32*j]);
			dp_mulAD (i, l[23+32*j], l[22+32*j], l[8+32*j]);
			l[24+32*j][i] = GNA * l[23+32*j][i];			// l[24+32*j] = I_Na

			// I_K2
			dp_smCAD (i, l[25+32*j], series[3*j], -EK);
			dp_mulAD (i, l[26+32*j], l[25+32*j], series[2+3*j]);
			dp_mulAD (i, l[27+32*j], l[26+32*j], series[2+3*j]);
			l[28+32*j][i] = GK2 * l[27+32*j][i];			// l[28+32*j] = I_K2

			// I_L + IAPP
			dp_smCAD (i, l[29+32*j], series[3*j], -EL);
			l[30+32*j][i] = GL * l[29+32*j][i];			// l[30+32*j] = I_L
			dp_smCAD (i, l[31+32*j], l[30+32*j], IAPP);		// l[31+32*j] = I_L + I_app
		


			// DERIVATIVES FOR j NEURON
			series[3*j][i+1] = (-l[24+32*j][i] - l[28+32*j][i] - l[31+32*j][i] - l[3+32*j][i]) / (i + 1.0) / C;
			series[1+3*j][i+1] = (l[13+32*j][i] - series[1+3*j][i]) / (i + 1.0) / TNA;
			series[2+3*j][i+1] = (l[18+32*j][i] - series[2+3*j][i]) / (i + 1.0) / TK2;
		}

	}


}

void printFunctions (FILE *fout, double x[]) {
}



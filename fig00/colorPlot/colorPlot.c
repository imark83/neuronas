#include <stdio.h>

#define FNAME	"T.txt"


int getColor (double* _f21, double* _f31, int N) {
	
	if (fabs (_f21[N-3] - _f21[N-4]) + fabs (_f31[N-3] - _f31[N-4]) > 2.0e-2) return CYAN;

	double f21 = _f21[N-3];
	double f31 = _f31[N-3];
	if (fabs (f21 - 0.46) + fabs (f31 - 0.46) < 0.04) return BLUE;

	if (fabs (f21 - 0.54) + fabs (f31) < 0.04) return RED;
	if (fabs (f21 - 0.54) + fabs (f31 - 1.0) < 0.04) return RED;

	if (fabs (f21) + fabs (f31 - 0.54) < 0.04) return GREEN;
	if (fabs (f21 - 1.0) + fabs (f31 - 0.54) < 0.04) return GREEN;

	if (fabs (f21 - 0.3333) + fabs (f31 - 0.6666) < 0.1) return MAGENTA;

	if (fabs (f21 - 0.66) + fabs (f31 - 0.33) < 0.04) return BLACK;

	return CYAN; 

}


// COUNTS NUMBER OF LINES OF A FILE
int getLines (const char *fname);

// COUNTS NUMBER OF POINCARE SECTIONS FOR EACH NEURON
int getNCut (const char *fname);

int main () {
	int M;			// number of lines in file
	M = getLines (FNAME);
	int N;			// number of Poincare cuts of each neuron
	N = getNCut (FNAME);
	printf ("N = %i\n", N);
	
	FILE *finp = fopen (FNAME, "r");

	int i, j;
	for (i=0; i<M; i++) {
		double T[3*N];
		double f21[N], f31[N];
		for (j=0; j<3*N; j++) fscanf (finp, "%le ", T+j);
		

		printf ("hola\n");
	}


	fclose (finp);
}


int getNCut (const char *fname) {
	FILE *finp = fopen (fname, "r");
	int rop = 0;

	char c1, c2;
	c1 = fgetc (finp);
	c2 = fgetc (finp);

	do {
		if (c1 != ' ' && (c2 == ' ' || c2 == '\n')){
			rop++;
		}
		c1 = c2; c2 = fgetc (finp);
	} while (c2 != '\n');
	
	fclose (finp);
	return rop / 3;
}

int getLines (const char *fname) {
	FILE *finp = fopen (fname, "r");
	int rop = 0;
	while (!feof (finp))
		rop += (fgetc (finp) == '\n');

	fclose (finp);
	return rop;
}


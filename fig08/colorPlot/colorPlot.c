#include <stdio.h>
#include <math.h>

//#define FNAME	"T05.txt"

#define	BLUE		1
#define RED		2
#define GREEN		3
#define BLACK		4
#define MAGENTA		5
#define CYAN		6



int getColor (double* _f21, double* _f31, int N) {
	
	//if (fabs (_f21[N-3] - _f21[N-4]) + fabs (_f31[N-3] - _f31[N-4]) > 2.0e-2) return CYAN;

	double f21 = _f21[N-3];
	double f31 = _f31[N-3];
	if (fabs (f21 - f31) < 0.02) return BLUE;

	if (fabs (f31) < 0.02) return RED;
	if (fabs (f31 - 1.0) < 0.02) return RED;

	if (fabs (f21) < 0.04) return GREEN;
	if (fabs (f21 - 1.0) < 0.04) return GREEN;

	if (fabs (f21 - 0.3333) + fabs (f31 - 0.6666) < 0.001) return BLACK;

	if (fabs (f21 - 0.6666) + fabs (f31 - 0.3333) < 0.001) return BLACK;

	return CYAN; 

}


// COUNTS NUMBER OF LINES OF A FILE
int getLines (const char *fname);

// COUNTS NUMBER OF POINCARE SECTIONS FOR EACH NEURON
int getNCut (const char *fname);

int main () {
int k;
for (k=5; k<=10; k++) {
	char FNAME[40];
	sprintf (FNAME, "T%02i.txt", k);
	printf ("file to read = %s\n", FNAME);
	FILE *finp = fopen (FNAME, "r");

	int M;			// number of lines in file
	M = getLines (FNAME);
	int N;			// number of Poincare cuts of each neuron
	N = getNCut (FNAME);
	printf ("N = %i\n", N);
	


	FILE *gnuplot = popen ("/usr/bin/gnuplot", "w");
	//fprintf (gnuplot, "set size square\nunset key\nset xrange [0.193:0.473]\nset yrange [0.526:0.806]\n");
	fprintf (gnuplot, "set size square\nunset key\nset xrange [0:1]\nset yrange [0:1]\n");
	//fprintf (gnuplot, "set term svg size 400, 400\n");
	//fprintf (gnuplot, "set output \"fig00.svg\"\n");

	int i, j;
	int nb = 0;		// number of blue orbits
	int nr = 0;		// number of red orbits
	int ng = 0;		// number of green orbits
	int nk = 0;		// number of black orbits
	int nm = 0;		// number of magenta orbits
	int nc = 0;		// number of cyan orbits

	char FOUT[40];
	sprintf (FOUT, "_c%02i.txt", k);
	FILE *fc = fopen (FOUT, "w");
	for (i=0; i<M; i++) {
		double T[3*N];
		double P;
		double d21, d31;
		double f21[N], f31[N];
		for (j=0; j<3*N; j++) fscanf (finp, "%le ", T+j);
		
		for (j=0; j<N-1; j++) {
			P = T[j+1]-T[j];
			d21 = T[N+j] - T[j];
			d31 = T[2*N+j] - T[j];
			f21[j] = d21 / P;
			f31[j] = d31 / P;
		}



		for (j=N-30; j<N-2; j++) 
			fprintf (fc, "%.15le  %.15le\n", f21[j], f31[j]);
		
			
	}		
		
		
	fclose (fc);
	int ncolors = 0; 
		if (nr) ncolors++;
		if (nb) ncolors++;
		if (ng) ncolors++;
		if (nk) ncolors++;
		if (nm) ncolors++;
		if (nc) ncolors++;
	char firstColor = 1;

	fprintf (gnuplot, "plot \"./_c%02i.txt\"  w l lc rgb \"cyan\"\n", k);

	fflush (gnuplot);
	//fprintf (gnuplot, "pause mouse\n");
	//fprintf (gnuplot, "print MOUSE_X, MOUSE_Y\n");
	//fflush (gnuplot);


	fgetc (stdin);

		

	fclose (finp);
	fclose (gnuplot);

}

	return 0;
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


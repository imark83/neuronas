#include <stdio.h>
#include <math.h>

#define FNAME	"T.txt"

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

	if (fabs (f21 - 0.3333) + fabs (f31 - 0.6666) < 0.1) return BLACK;

	//if (fabs (f21 - 0.6666) + fabs (f31 - 0.3333) < 0.1) return BLACK;

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


	FILE *gnuplot = popen ("/usr/bin/gnuplot", "w");
	//fprintf (gnuplot, "set size square\nunset key\nset xrange [0.193:0.473]\nset yrange [0.526:0.806]\n");
	fprintf (gnuplot, "set size square\nset yrange [0:1]\n");
	fprintf (gnuplot, "set xlabel \"t\"\n");
	fprintf (gnuplot, "set ylabel \"delay\"\n");
	fprintf (gnuplot, "set term svg size 250, 250\n");

	int i, j;
	int nb = 0;		// number of blue orbits
	int nr = 0;		// number of red orbits
	int ng = 0;		// number of green orbits
	int nk = 0;		// number of black orbits
	int nm = 0;		// number of magenta orbits
	int nc = 0;		// number of cyan orbits

	FILE *fb = fopen ("_b.txt", "w");
	FILE *fr = fopen ("_r.txt", "w");
	FILE *fg = fopen ("_g.txt", "w");
	FILE *fk = fopen ("_k.txt", "w");
	FILE *fm = fopen ("_m.txt", "w");
	FILE *fc = fopen ("_c.txt", "w");
	
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

	
		switch (getColor (f21, f31, N)) {
			case BLUE:
				for (j=0; j<N-2; j++) 
					fprintf (fb, "%.15le %.15le  %.15le\n", T[j], f21[j], f31[j]);
				fprintf (fb, "\n");
				nb++;
					break;
			case RED:
				for (j=0; j<N-2; j++) 
					fprintf (fr, "%.15le %.15le  %.15le\n", T[j], f21[j], f31[j]);
				fprintf (fr, "\n");
				nr++;
				break;
			case GREEN:
				for (j=0; j<N-2; j++) 
					fprintf (fg, "%.15le %.15le  %.15le\n", T[j], f21[j], f31[j]);
				fprintf (fg, "\n");
				ng++;
				break;
			case BLACK:
				for (j=0; j<N-2; j++) 
					fprintf (fk, "%.15le %.15le  %.15le\n", T[j], f21[j], f31[j]);
				fprintf (fk, "\n");
				nk++;
				break;
			case CYAN:
				for (j=0; j<N-2; j++) 
					fprintf (fc, "%.15le %.15le  %.15le\n", T[j], f21[j], f31[j]);
				fprintf (fc, "\n");
				nc++;
				break;
		}
			
	}		
		
	fclose (fb); fclose (fg); fclose (fr); fclose (fk); fclose (fm); fclose (fc);
	int ncolors = 0; 
		if (nr) ncolors++;
		if (nb) ncolors++;
		if (ng) ncolors++;
		if (nk) ncolors++;
		if (nm) ncolors++;
		if (nc) ncolors++;
	char firstColor = 1;

	fprintf (gnuplot, "set output \"fig01_b.svg\"\n");
	fprintf (gnuplot, "plot \"./_b.txt\" u 1:2 w l lc rgb \"light-blue\" lw 2 title \"phi_21\"");
	fprintf (gnuplot, ", \\\n \"./_b.txt\" u 1:3 w l lc rgb \"dark-blue\" lw 0.4 title \"phi_31\"");

	/*fprintf (gnuplot, "set output \"fig01_r.svg\"\n");
	fprintf (gnuplot, "plot \"./_r.txt\" u 1:2 w l lc rgb \"light-red\" lw 2 title \"phi_21\"");
	fprintf (gnuplot, ", \\\n \"./_r.txt\" u 1:3 w l lc rgb \"dark-red\" lw 0.4 title \"phi_31\"");*/

	/*fprintf (gnuplot, "set output \"fig01_g.svg\"\n");
	fprintf (gnuplot, "plot \"./_g.txt\" u 1:2 w l lc rgb \"light-green\" lw 2 title \"phi_21\"");
	fprintf (gnuplot, ", \\\n \"./_g.txt\" u 1:3 w l lc rgb \"dark-green\" lw 0.4 title \"phi_31\"");*/

	/*fprintf (gnuplot, "set output \"fig01_k.svg\"\n");
	fprintf (gnuplot, "plot \"./_k.txt\" u 1:2 w l lc rgb \"grey20\" lw 2 title \"phi_21\"");
	fprintf (gnuplot, ", \\\n \"./_k.txt\" u 1:3 w l lc rgb \"black\" lw 0.4 title \"phi_31\"");*/

	fprintf (gnuplot, "\n");

	fflush (gnuplot);
	//fprintf (gnuplot, "pause mouse\n");
	//fprintf (gnuplot, "print MOUSE_X, MOUSE_Y\n");
	//fflush (gnuplot);


	fgetc (stdin);

		

	fclose (finp);
	fclose (gnuplot);


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


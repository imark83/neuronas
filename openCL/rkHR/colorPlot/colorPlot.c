#include <stdio.h>
#include <math.h>
#include "list.h"

#define FNAME	"T.txt"

#define	BLUE		1
#define RED			2
#define GREEN		3
#define BLACK		4
#define MAGENTA		5
#define CYAN		6

#define MIN(a,b) (((a)<(b))? (a) : (b))




list_t colorList = {0, NULL};



double truncate2 (double op, int n);

double mod(double op);

double torusNorm (double *p, double *q);

int getColor (double _f21, double _f31);


// COUNTS NUMBER OF LINES OF A FILE
int getLines (const char *fname);

// COUNTS NUMBER OF POINCARE SECTIONS FOR EACH NEURON
int getNCut (const char *fname);

int main () {
	int M;			// number of lines in file
	M = getLines (FNAME);
	int N;			// number of Poincare cuts of each neuron
	N = getNCut (FNAME);
	
	FILE *finp = fopen (FNAME, "r");


	/*FILE *gnuplot = popen ("/usr/bin/gnuplot", "w");
	fprintf (gnuplot, "set term svg size 400, 400 fsize 14\n");
	fprintf (gnuplot, "set size square\nunset key\nset xrange [0:1]\nset yrange [0:1]\n");
	fprintf (gnuplot, "set output \"fig00.svg\"\n");*/

	int i, j;

	
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

		int color = getColor (f21[N-2], f31[N-2]);
		for (j=0; j<N-1; ++j)
			printf ("%e %e %i\n", f21[j], f31[j], color);
		printf ("\n");

	}

	//fflush (gnuplot);
	/*fprintf (gnuplot, "pause mouse\n");
	fprintf (gnuplot, "print MOUSE_X, MOUSE_Y\n");
	fflush (gnuplot);*/


	//fgetc (stdin);

		

	fclose (finp);
	//fclose (gnuplot);
	//system ("rm _?.txt");

}


int getNCut (const char *fname) {
	FILE *finp = fopen (fname, "r");
	int rop = 1;

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


double truncate2 (double op, int n) {
	return floor(op*(1<<n))/(1<<n);
}

double mod(double op) {
	if (op < 0.0) return mod (op + 1.0);
	if (op > 1.0) return mod (op - 1.0);
	return op;
}


double torusNorm (double *p, double *q) {
	double shift[4][2] = {{0.0, 0.0}, {0.5, 0.0}, {0.0, 0.5}, {0.5, 0.5}};
	double norm[4];
	int i;
	for (i=0; i<4; ++i)
		norm[i] = fabs(mod(p[0]+shift[i][0]) - mod(q[0]+shift[i][0])) + 
						fabs(mod(p[1]+shift[i][1]) - mod(q[1]+shift[i][1]));
						
	return MIN(norm[0], MIN(norm[1], MIN(norm[2], norm[3])));
}



int getColor (double _f21, double _f31) {
	
	double p[2] = {truncate2 (_f21, 4), truncate2 (_f31, 4)};

	node_t *index;
	int i;
		
	for (i=0, index = colorList.first; index != NULL; index = index->next, ++i) {
		if (torusNorm (p, index->x) < 0.2)
			return i;
	}
	
	appendData (&colorList, p);
	return i;

}



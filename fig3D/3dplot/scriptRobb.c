#include <stdio.h>

int main () {

	FILE *finp, *fout;

	fout = fopen ("allCycles.txt", "w");
	int i, j;
	char fname[50];
	double data[3];

	for (i=10; i<=20; i++) {
		sprintf (fname, "_cycle%2i.txt", i);
		finp = fopen (fname, "r");
		j=0;
		do {
			fscanf (finp, "%le %le %le\n", data, data+1, data+2);
			fprintf (fout, "%.15le %.15le %.15le %2i %2i\n", data[0], data[1], data[2], j++, i-10);
		} while (!feof (finp));

		fclose (finp);
	}

	fclose (fout);
	return 0;
}

#include <stdio.h>


int main (int argc, char **argv) {
	char command[500];
	int k;
	
	for (k=0; k<100; ++k) {
		system ("cat commonParameters.h > parameters.h");
		sprintf (command, "echo \"#define IAPP\t\t\t(%f)\" >> parameters.h", 0.5 + 0.015*k);
		system (command);
		system ("gcc -o neuron neuron.c -lOpenCL -O2");
		sprintf (command, "./neuron T%03i.txt", k);
		system (command);
	}

	return 0;
}

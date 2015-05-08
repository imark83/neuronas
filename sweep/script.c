#include <stdio.h>



int main () {

	char command[500];
	int i=0;

	for (i=0; i<36; ++i) {
		sprintf (command, "cat commonParameters.h > parameters.h");
		system (command);
		sprintf (command, "echo \"#define VSHIFT\t\t(%f)\n\" >> parameters.h", -0.022+0.0001*i);
		system (command);
	
	
		sprintf (command, "rm -fr ~/.nv/*");
		system (command);
	
		sprintf (command, "gcc -o neuron neuron.c -lOpenCL");
		system (command);
		sprintf (command, "./neuron fastData/T%02i.txt", i);
		system (command);
		
		sprintf (command, "./colorPlotter fastData/T%02i.txt fastPics/sweep%02i.png", i, i);
		system (command);

	}

	return 0;


}

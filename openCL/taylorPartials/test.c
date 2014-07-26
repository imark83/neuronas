#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
	#include <OpenCL/cl.h>
#else
	#include <CL/cl.h>
#endif


#include "parameters.h"


void fileToSource (char *filename, char **source);
real_t getRand ();

int main () {
	long int i, j;

	// RANDOM NUMBERS
	real_t *randomNumber;
	randomNumber = (real_t*) malloc (NVAR*N * sizeof (real_t));
	for (i=0; i<NVAR*N; i++)
		randomNumber[i] = getRand ();
	for (i=0; i<NVAR; i++) 
		randomNumber[N*i] = 0.0;

	// GLOBAL SIZES
	size_t global_work_size[] = {M,N};

	// READ KERNEL FILE
	char *source;
	fileToSource ("test_kernel.cl", &source);
	
	// OPENCL START AND BUILD KERNEL
	#include "openCL_start.h"
	#include "openCL_kernel_build.h"


	// ALLOCATE MEMORY FOR VARIABLES ON DEVICE
	cl_mem d_fli = clCreateBuffer (context, CL_MEM_WRITE_ONLY, N*M * sizeof (real_t), NULL, NULL);


	// SET KERNEL ARGUMENTS
	clSetKernelArg (testKernel, 0, sizeof (d_fli), (void*) &d_fli);

	// EVENT FOR MEASURING TIME
	cl_event prof_event;

	// LAUNCH KERNEL!
	clEnqueueNDRangeKernel (queue,	// QUEUE
		testKernel,	// KERNEL NAME
		2,		// DIMENSIONS
		NULL,		// OFFSET
		global_work_size,// GLOBAL SIZE
		NULL,		// LOCAL SIZE
		0,		// NUM EVENTS IN WAIT LIST
		NULL,		// WAIT LIST
		&prof_event	// EVENT FOR MEASURING TIME 
	);

	// WAIT UNTIL ALL IS FINISHED
	clFinish (queue);
	clWaitForEvents (1, &prof_event);

	// READ OUTPUT VARIABLES
	real_t *fli = (real_t*) malloc (M*N*sizeof (real_t));
	clEnqueueReadBuffer (queue, d_fli, CL_TRUE, 0, M*N* sizeof (real_t), fli, 0, NULL, NULL);

	// OUTPUT
	FILE *fout = fopen ("FLI.txt", "w");
	for (i=0; i<M; i++) {
		for (j=0; j<N; j++) 
			fprintf (fout, "%.15le  ", fli[M*i+j]);
		fprintf (fout, "\n");
	}
	fclose (fout);




	// GENERATE AN OCTAVE SCRIPT TO PLOT RESULT
	fout = fopen ("dibuja.m", "w");
	fprintf (fout, "clf\n");
	fprintf (fout, "xx=linspace(%.5le,%.5le,%i);\n", yMIN, yMAX, M);
	fprintf (fout, "yy=linspace(%.5le,%.5le,%i);\n", YMIN, YMAX, N);
	fprintf (fout, "F = load (\"FLI.txt\");\n[x,y] = meshgrid (xx,yy);\npcolor(x,y,F)\nshading flat\n");
	fprintf (fout, "axis([%.5le %.5le %.5le %.5le])\n", yMIN, yMAX, YMIN, YMAX);
	fclose (fout);


	// CPU -- GPU time
	cl_ulong c0, c1;
	clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START, sizeof(c0), &c0, NULL);
	clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END, sizeof(c1), &c1, NULL);
	//printf("\nExecution time in milliseconds = %0.3f ms\n", ((real_t) (c1 - c0) / 1.e6));

	printf ("Computation time -> %0.3f\n", ((real_t) (c1 - c0) / 1.e6)); //x[0]);

	

	// FREE MEMORY OBJECTS FROM HOST
	free (fli);

	// FREE MEMORY OBJECTS FROM DEVICE
	clReleaseMemObject (d_fli);

	// FREE OPENCL OBJECTS
	clReleaseKernel (testKernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

	return 0;
}




real_t getRand () {
	return (((double) rand()) / RAND_MAX) * 0.02 - 0.01;
}

void fileToSource (char *filename, char **source) {
	FILE* finp;

	finp = fopen (filename, "r");
	size_t fileLength;

	fseek(finp, 0, SEEK_END);
	fileLength = ftell(finp);
	rewind (finp);
	
	*source = (char*) malloc (fileLength*sizeof (char));
	int i=0;
	while (!feof (finp)) {
		EOF == fscanf (finp, "%c", &(*source)[i++]);
	}
	(*source)[fileLength-1] = '\0';	

	
	fclose (finp);
}


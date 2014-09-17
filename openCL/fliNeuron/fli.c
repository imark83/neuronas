#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/cl.h>

#include "parameters.h"

void fileToSource (char *filename, char **source);


int main () {
	int i, j, k;
	size_t global_work_size [] = {M, N};
	size_t local_work_size [] = {4, 4};

	// READ KERNEL FILE
	char *source;
	fileToSource ("fli_kernel.cl", &source);
	
	#include "openCL_start.h"
	#include "openCL_kernel_build.h"


	// ALLOCATE SPACE FOR GLOBAL VARIABLES IN DEVICE
	cl_mem d_fli = clCreateBuffer (context, CL_MEM_WRITE_ONLY, N*M * sizeof (real_t), NULL, NULL);
	cl_mem d_counter = clCreateBuffer (context, CL_MEM_READ_WRITE, sizeof (int), NULL, NULL);
	
	// FOR MEASURING TIME 
	cl_event fli_event;

	// SET KERNEL ARGUMENTS
	clSetKernelArg (fliKernel, 0, sizeof (d_fli), (void*) &d_fli);
	clSetKernelArg (fliKernel, 1, sizeof (d_fli), (void*) &d_counter);

	// LAUNCH KERNEL
	clEnqueueNDRangeKernel (queue, 	// QUEUE
		fliKernel, 		// KERNEL
		2, 			// WORK DIMENSIONS
		NULL,			// GLOBAL WORK OFFSET (NULL)
		global_work_size,	// GLOBAL WORK SIZE
		//local_work_size,	// LOCAL WORK SIZE
		NULL		,	// LOCAL WORK SIZE
		0,			// NUM EVENTS IN WAIT LIST
		NULL,			// WAIT LIST
		&fli_event		// EVENT FOR MEASURING TIME
	);
	
	// WAIT UNTIL FINISH
	clFinish (queue);
	clWaitForEvents (1, &fli_event);

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
	fprintf (fout, "xx=linspace(%.5le,%.5le,%i);\n", XMIN, XMAX, M);
	fprintf (fout, "yy=linspace(%.5le,%.5le,%i);\n", YMIN, YMAX, N);
	fprintf (fout, "F = load (\"FLI.txt\");\n[x,y] = meshgrid (xx,yy);\npcolor(x,y,F)\nshading flat\n");
	fprintf (fout, "axis([%.5le %.5le %.5le %.5le])\n", XMIN, XMAX, YMIN, YMAX);
	fclose (fout);



	// CPU -- GPU time
	cl_ulong time_start, time_end;
	clGetEventProfilingInfo(fli_event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(fli_event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
	printf("\nExecution time in milliseconds = %0.3f ms\n", ((real_t) (time_end - time_start) / 1.e6));


	// FREE MEM OBJECTS
	free (fli);
	clReleaseMemObject (d_fli);
	
	
	clReleaseKernel (fliKernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

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


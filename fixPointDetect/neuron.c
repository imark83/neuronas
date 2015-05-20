#include <stdio.h>
#include <stdlib.h>

#include <OpenCL/cl.h>

#include "parameters.h"


int main (int argc, char *argv[]) {
	int i, j;
	const size_t global_work_size[] = {M, N};
	const size_t local_work_size[] = {1, 1};
	const char *source = "#include \"neuron_kernel.cl\"\n";
	const char *kernelName = "neuron";

	#include "openCL_start.h"

	cl_event event;

	// ALLOCATE MEMORY
	
	cl_mem d_colorMap = clCreateBuffer (context, CL_MEM_WRITE_ONLY, M*N*CUTNUMBER * sizeof (real_t), NULL, NULL);

	// SET KERNEL ARGUMENTS

	clSetKernelArg (kernel, 0, sizeof (cl_mem), (void*) (&d_colorMap));

	// LAUNCH KERNEL
	clEnqueueNDRangeKernel (queue, kernel,
		2,			// WORKING DIMENSIONS
		NULL,			// GLOBAL OFFSET
		global_work_size,	// GLOBAL WORK SIZE
		local_work_size,	// LOCAL WORK SIZE
		0,			// NUM EVENTS IN WAIT LIST
		NULL,			// WAIT LIST
		&event);		// EVENT FOR TIMING

	clFinish (queue);


	real_t *colorMap = (real_t*) malloc (M*N*CUTNUMBER * sizeof (real_t));
	clEnqueueReadBuffer (queue, d_colorMap, CL_TRUE, 0, M*N*CUTNUMBER * sizeof (real_t), colorMap, 0, NULL, NULL);
	clFinish(queue);


	FILE *fout = fopen (FILENAME, "w");

	for (i=0; i<M; i++) {
		for (j=0; j<N; j++) 
			fprintf (fout, "  %.15le", colorMap[j*M+i]);
		fprintf (fout, "\n");
	}
	fclose (fout);

	unsigned long int c0, c1;
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_START, sizeof (cl_ulong), &c0, NULL);
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_END, sizeof (cl_ulong), &c1, NULL);
	printf ("CPU time = %.2f miliseconds\n", (c1-c0) / 1.0e6);

	system ("beep");


	// RELEASE MEMORY
	clReleaseMemObject (d_colorMap);
	free (colorMap);

	// CLEAN UP OPENCL OBJECTS
	clReleaseKernel (kernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

	return 0;
}

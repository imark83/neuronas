#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

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
	
	cl_mem d_endPoint = clCreateBuffer (context, CL_MEM_WRITE_ONLY, N * M * sizeof (char), NULL, NULL);

	// SET KERNEL ARGUMENTS

	clSetKernelArg (kernel, 0, sizeof (cl_mem), (void*) (&d_endPoint));

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


	char *endPoint = (char *) malloc (M*N * sizeof (char));
	clEnqueueReadBuffer (queue, d_endPoint, CL_TRUE, 0, M*N * sizeof (char), endPoint, 0, NULL, NULL);
	clFinish(queue);


	FILE *fout = fopen (FILENAME, "w");
	for (j=0; j<N; j++) {
		for (i=0; i<M; i++)
			fprintf (fout, "%hhi  ", endPoint[M*j + i]);
		fprintf (fout, "\n");
	}
	fclose (fout);


	unsigned long int c0, c1;
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_START, sizeof (cl_ulong), &c0, NULL);
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_END, sizeof (cl_ulong), &c1, NULL);
	printf ("CPU time = %.2f miliseconds\n", (c1-c0) / 1.0e6);

	system ("beep");


	// RELEASE MEMORY
	clReleaseMemObject (d_endPoint);
	free (endPoint);

	// CLEAN UP OPENCL OBJECTS
	clReleaseKernel (kernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

	return 0;
}

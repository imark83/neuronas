#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

#include "parameters.h"


int main (int argc, char *argv[]) {
	int i, j;
	const size_t global_work_size[] = {N};
	const size_t local_work_size[] = {1};
	const char *source = "#include \"neuron_kernel.cl\"\n";
	const char *kernelName = "neuron";

	#include "openCL_start.h"

	cl_event event;

	// READ RANDOM NUMBERS
	FILE *finp = fopen ("random64.bin", "rb");
	if (finp == NULL) {
		fprintf (stderr, "not found random numbers\n");
		return 0;
	}
	fseek (finp, 0, SEEK_END);
	int len = ftell (finp);
	if (8*len / sizeof (real_t) < N) { 
		fprintf (stderr, "not enough random numbers\n");
		return 0;
	}
	real_t *randomNumber = malloc (len);
	rewind (finp);
	fread (randomNumber, sizeof (real_t), 8*N, finp);
	fclose (finp);


	// ALLOCATE MEMORY
	cl_mem d_randomNumber = clCreateBuffer (context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, (NNEURON-1)*N * sizeof (real_t), randomNumber, NULL);
	cl_mem d_delay = clCreateBuffer (context, CL_MEM_WRITE_ONLY, NNEURON*N*CUTNUMBER * sizeof (real_t), NULL, NULL);

	// SET KERNEL ARGUMENTS

	clSetKernelArg (kernel, 0, sizeof (cl_mem), (void*) (&d_delay));
	clSetKernelArg (kernel, 1, sizeof (cl_mem), (void*) (&d_randomNumber));

	// LAUNCH KERNEL
	clEnqueueNDRangeKernel (queue, kernel,
		1,			// WORKING DIMENSIONS
		NULL,			// GLOBAL OFFSET
		global_work_size,	// GLOBAL WORK SIZE
		local_work_size,	// LOCAL WORK SIZE
		0,			// NUM EVENTS IN WAIT LIST
		NULL,			// WAIT LIST
		&event);		// EVENT FOR TIMING

	clFinish (queue);


	real_t *delay = (real_t*) malloc (NNEURON*N*CUTNUMBER * sizeof (real_t));
	clEnqueueReadBuffer (queue, d_delay, CL_TRUE, 0,  NNEURON*N*CUTNUMBER * sizeof (real_t), delay, 0, NULL, NULL);
	clFinish(queue);


	FILE *fout = fopen (FILENAME, "wb");
	fwrite (delay, sizeof (real_t), NNEURON*N*CUTNUMBER, fout);
	fclose (fout);

	unsigned long int c0, c1;
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_START, sizeof (cl_ulong), &c0, NULL);
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_END, sizeof (cl_ulong), &c1, NULL);
	printf ("CPU time = %.2f miliseconds\n", (c1-c0) / 1.0e6);

	system ("beep");


	// RELEASE MEMORY
	clReleaseMemObject (d_delay);
	clReleaseMemObject (d_randomNumber);
	free (delay);
	free (randomNumber);

	// CLEAN UP OPENCL OBJECTS
	clReleaseKernel (kernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

	return 0;
}

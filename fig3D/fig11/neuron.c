#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	real_t vshift = -0.01871;
	cl_mem d_delay = clCreateBuffer (context, CL_MEM_WRITE_ONLY, 3*M*N*CUTNUMBER * sizeof (real_t), NULL, NULL);
	cl_mem d_VSHIFT = clCreateBuffer (context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof (real_t), &vshift, NULL);

	clSetKernelArg (kernel, 0, sizeof (cl_mem), (void*) (&d_VSHIFT));
	clSetKernelArg (kernel, 1, sizeof (cl_mem), (void*) (&d_delay));

	clEnqueueNDRangeKernel (queue, kernel, 
			2,			// WORKING DIMENSIONS
 			NULL,			// GLOBAL OFFSET (USELESS)
 			global_work_size,	// GLOBAL WORK SIZE
 			//NULL,			// LOCAL  WORK SIZE
 			local_work_size,	// LOCAL  WORK SIZE
			0,			// NUM EVENTS IN WAIT LIST
			NULL,			// WAIT LIST
			&event);		// EVENT FOR MEASURING 
	clFinish(queue);


	real_t *delay = (real_t*) malloc (3*M*N*CUTNUMBER * sizeof (real_t));
	clEnqueueReadBuffer (queue, d_delay, CL_TRUE, 0, 3*M*N*CUTNUMBER * sizeof (real_t), delay, 0, NULL, NULL);
	clFinish(queue);

	FILE *fout = fopen (FNAME, "w");

	for (i=0; i<M*N; i++) {
		for (j=0; j<3*CUTNUMBER; j++) 
			fprintf (fout, "  %.15le", delay[j*M*N+i]);
		fprintf (fout, "\n");
	}
	fclose (fout);

	unsigned long int c0, c1;
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_START, sizeof (cl_ulong), &c0, NULL);
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_END, sizeof (cl_ulong), &c1, NULL);
	printf ("CPU time = %.2f miliseconds\n", (c1-c0) / 1.0e6);

	//clReleaseMemObject (d_VSHIFT);
	clReleaseMemObject (d_delay);
	free (delay);

	// CLEAN UP OPENCL OBJECTS
	clReleaseKernel (kernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

	
	return 0;
}	

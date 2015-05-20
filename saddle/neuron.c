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
	real_t phi31 = 0.19;
	if (argc > 1) 
		phi31 = atof_l (argv[1]);


	// ALLOCATE MEMORY
	cl_mem d_phi31 = clCreateBuffer (context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof (real_t), &phi31, NULL);
	cl_mem d_endPoint = clCreateBuffer (context, CL_MEM_WRITE_ONLY, sizeof (real_t), NULL, NULL);



	// SET KERNEL ARGUMENTS

	clSetKernelArg (kernel, 0, sizeof (cl_mem), (void*) (&d_phi31));
	clSetKernelArg (kernel, 1, sizeof (cl_mem), (void*) (&d_endPoint));


	real_t endPoint;
	real_t left  = 1.459132379705810e-01;
	real_t right = 1.459132380517578e-01;
	real_t mid = (left + right) / 2.0;
	real_t endLeft;
	real_t endRight;
	real_t endMid;
	

	// LAUNCH KERNEL FOR LEFT
	phi31 = left;
	clEnqueueNDRangeKernel (queue, kernel,
		2,			// WORKING DIMENSIONS
		NULL,			// GLOBAL OFFSET
		global_work_size,	// GLOBAL WORK SIZE
		local_work_size,	// LOCAL WORK SIZE
		0,			// NUM EVENTS IN WAIT LIST
		NULL,			// WAIT LIST
		&event);		// EVENT FOR TIMING

	clFinish (queue);
	clEnqueueReadBuffer (queue, d_endPoint, CL_TRUE, 0, sizeof (real_t), &endPoint, 0, NULL, NULL);
	clFinish(queue);
	endLeft = endPoint;


	// LAUNCH KERNEL FOR RIGHT
	phi31 = right;
	clEnqueueNDRangeKernel (queue, kernel,
		2,			// WORKING DIMENSIONS
		NULL,			// GLOBAL OFFSET
		global_work_size,	// GLOBAL WORK SIZE
		local_work_size,	// LOCAL WORK SIZE
		0,			// NUM EVENTS IN WAIT LIST
		NULL,			// WAIT LIST
		&event);		// EVENT FOR TIMING

	clFinish (queue);
	clEnqueueReadBuffer (queue, d_endPoint, CL_TRUE, 0, sizeof (real_t), &endPoint, 0, NULL, NULL);
	clFinish(queue);
	endRight = endPoint;

return;

	for (i=0; i<5; ++i) {
		// LAUNCH KERNEL
		phi31 = mid;
		clEnqueueNDRangeKernel (queue, kernel,
			2,			// WORKING DIMENSIONS
			NULL,			// GLOBAL OFFSET
			global_work_size,	// GLOBAL WORK SIZE
			local_work_size,	// LOCAL WORK SIZE
			0,			// NUM EVENTS IN WAIT LIST
			NULL,			// WAIT LIST
			&event);		// EVENT FOR TIMING

		clFinish (queue);


		real_t endPoint;
		clEnqueueReadBuffer (queue, d_endPoint, CL_TRUE, 0, sizeof (real_t), &endPoint, 0, NULL, NULL);
		clFinish(queue);
		if (endPoint == 1) 
			right = mid;
		if (endPoint == 0)
			left = mid;
		if (endPoint == -1) {
			printf ("phi31 = %.15le\n", mid);
			return;
		}
		printf ("mid = %.15le\n", mid);
		mid = (right + left) / 2.0;
	}

	printf ("Read end point = %f\n", endPoint);

	unsigned long int c0, c1;
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_START, sizeof (cl_ulong), &c0, NULL);
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_END, sizeof (cl_ulong), &c1, NULL);
	printf ("CPU time = %.2f miliseconds\n", (c1-c0) / 1.0e6);



	// RELEASE MEMORY
	clReleaseMemObject (d_phi31);
	clReleaseMemObject (d_endPoint);

	// CLEAN UP OPENCL OBJECTS
	clReleaseKernel (kernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

	return 0;
}

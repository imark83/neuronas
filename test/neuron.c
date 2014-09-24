#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>

#include "parameters.h"



int main (int argc, char *argv[]) {

	const size_t global_work_size[] = {4000, 1};
	const size_t local_work_size[] = {2, 1};
	const char *source = "#include \"neuron_kernel.cl\"\n";
	const char *kernelName = "neuron";

	#include "openCL_start.h"

	cl_event event;
	clEnqueueNDRangeKernel (queue, kernel, 
			1,			// WORKING DIMENSIONS
 			NULL,			// GLOBAL OFFSET (USELESS)
 			global_work_size,	// GLOBAL WORK SIZE
 			NULL,			// LOCAL  WORK SIZE
 			//local_work_size,	// LOCAL  WORK SIZE
			0,			// NUM EVENTS IN WAIT LIST
			NULL,			// WAIT LIST
			&event);		// EVENT FOR MEASURING 
	clFinish(queue);

	unsigned long int c0, c1;
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_START, sizeof (cl_ulong), &c0, NULL);
	clGetEventProfilingInfo (event, CL_PROFILING_COMMAND_END, sizeof (cl_ulong), &c1, NULL);
	printf ("CPU time = %.2f miliseconds\n", (c1-c0) / 1.0e6);

	return 0;
}	

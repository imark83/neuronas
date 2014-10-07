#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/cl.h>


#include "parameters.h"

void fileToSource (char *filename, char **source);



int main (int argc, char *argv[]) {
	int i, j, k;
	size_t global_work_size [] = {M, N};
	size_t local_work_size [] = {1, 1};

	const char *source = "#include \"neuron_kernel.cl\"\n";
	const char *kernelName = "neuron";


	#include "openCL_start.h"

	// ALLOCATE SPACE FOR GLOBAL VARIABLES IN DEVICE


	real_t VSHIFT;
	//VSHIFT=-0.01928000;		// ESTABLE
	//VSHIFT=-0.01927800;		// ESTABLE
	//VSHIFT=-0.01927700;		// ESTABLE
	//VSHIFT=-0.01927700;		// ESTABLE
	//VSHIFT=-0.01927000;		// INESTABLE
	VSHIFT=-0.01871;

		
	cl_mem d_delay = clCreateBuffer (context, CL_MEM_WRITE_ONLY, 3*CUTNUMBER * N * M * sizeof (real_t), NULL, NULL);
	cl_mem d_VSHIFT = clCreateBuffer (context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof (real_t), &VSHIFT, NULL);

	// SET KERNEL ARGUMENTS
	clSetKernelArg (kernel, 0, sizeof (d_delay), (void*) &d_delay);
	clSetKernelArg (kernel, 1, sizeof (d_VSHIFT), (void*) &d_VSHIFT);
	// FOR MEASURING TIME 
	cl_event prof_event;

	// LAUNCH KERNEL
	clEnqueueNDRangeKernel (queue, 	// QUEUE
		kernel, 		// KERNEL
		2, 			// WORK DIMENSIONS
		NULL,			// GLOBAL WORK OFFSET (NULL)
		global_work_size,	// GLOBAL WORK SIZE
		NULL,			// LOCAL WORK SIZE
		//local_work_size,	// LOCAL WORK SIZE
		0,			// NUM EVENTS IN WAIT LIST
		NULL,			// WAIT LIST
		&prof_event		// EVENT FOR MEASURING TIME
	);

	// WAIT UNTIL FINISH
	clFinish (queue);
	//clWaitForEvents (1, &prof_event);
		// READ AUX VARIABLE
	real_t delay[3*CUTNUMBER*M*N];
	clEnqueueReadBuffer (queue, d_delay, CL_TRUE, 0, 3*M*N*CUTNUMBER * sizeof (real_t), delay, 0, NULL, NULL);

		FILE *fout = fopen (FILENAME, "w");
	for (i=0; i<M*N; i++) {
		for (j=0; j<3*CUTNUMBER; j++)
			fprintf (fout, "%.15le  ", delay[i + M*N*j]);
		fprintf (fout, "\n");
	}
	fclose (fout);
		
	clReleaseMemObject (d_VSHIFT);
	clReleaseMemObject (d_delay);

	// CPU -- GPU time
	cl_ulong time_start, time_end;
	clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);	
	printf("\nExecution time in milliseconds = %0.3f ms\n", ((real_t) (time_end - time_start) / 1.e6));



	// CLEAN UP OPENCL OBJECTS
	clReleaseKernel (kernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);
	

	return 0;
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



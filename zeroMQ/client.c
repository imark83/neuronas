#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <CL/cl.h>


#include "my_protocol.h"

int main (int argc, char **argv) {

	int i;
	FILE *file;
	// TASK LEN

	size_t len = 8;
	if (argc > 1) len = atoi (argv[1]);


	// OpenCL STARTUP
	const size_t global_work_size[] = {len, 1};
	const size_t local_work_size[] = {1, 1};
	const char *source = "#include \"neuron_kernel.cl\"\n";
	const char *kernelName = "neuron";
	cl_event event;
	#include "openCL_start.h"

	// CREATE CL MEM BUFFER
	cl_mem d_endPoint = clCreateBuffer (context, CL_MEM_READ_WRITE, len * sizeof (int), NULL, NULL);

	// SET KERNEL ARGUMENT	
	clSetKernelArg (kernel, 0, sizeof (cl_mem), (void*) (&d_endPoint));

	// zmq_context of zeroMQ
	void *zmq_context = zmq_ctx_new ();
	void *socket  = zmq_socket (zmq_context, ZMQ_REQ);
//	int errMsg = zmq_connect (socket, "tcp://155.210.85.57:5555");
	int errMsg = zmq_connect (socket, "tcp://localhost:5555");
	if (errMsg != 0) {
		fprintf (stderr, "Error binding socket\n");
		return errMsg;
	}

	message_t message;
	attach_t attach = (attach_t) malloc (ATTACH_MAX_SIZE * sizeof (int));

	while (1) {
	
		// CHECK IF THERE IS MESSAGE IN DISK
		file = fopen ("assignedTask.bin", "rb");
	
		if (file == NULL) {
			message.header = SEND_ME;
			message.len = len;
			zmq_send (socket, &message, sizeof (message_t), 0);
			zmq_recv (socket, &message, sizeof (message_t), 0);
			if (message.header == NO_MORE) {
				fprintf (stderr, "Server has no more tasks\n");
				break;
			}
			// SAVE MESSAGE TO DISK
			file = fopen ("assignedTask.bin", "wb");
			fwrite (&message, sizeof (message_t), 1, file);
			fclose (file);
		} else {
			fread (&message, sizeof (message_t), 1, file);
			fclose (file);
		}
		
printf ("press enter to continue\n"); getchar ();
		// PROCESS TASK
		for (i=message.index; i<message.index + message.len; ++i)
			attach[i-message.index] = i;	
		for (i=message.index+message.len; i<message.index + len; ++i)
			attach[i-message.index] = -1;	
			
		clEnqueueWriteBuffer (queue, d_endPoint, CL_TRUE, 0, len * sizeof (int), attach, 0, NULL, &event);
		clFinish (queue);


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

		clEnqueueReadBuffer (queue, d_endPoint, CL_TRUE, 0, len * sizeof (int), attach, 0, NULL, NULL);
		clFinish (queue);


		// SEND COMPLETED TASK
		message.header = WORK_DONE;
		zmq_send (socket, &message, sizeof (message_t), ZMQ_SNDMORE);
		zmq_send (socket, attach, message.len*sizeof (int), 0);
		zmq_recv (socket, &message, sizeof (message_t), 0);
		remove ("assignedTask.bin");
		if (message.header == THANK_YOU_NO_MORE) {
			fprintf (stderr, "Server has no more tasks\n");
			break;
		}
		if (message.header != THANK_YOU) {
			fprintf (stderr, "Stupid Flanders Server.\n");
			return 0;
		}
	}

	
	

	clReleaseKernel (kernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);
	clReleaseMemObject (d_endPoint);
	
	
	zmq_close (socket);
	zmq_ctx_destroy (zmq_context);
	
	free (attach);

	return 0;
}










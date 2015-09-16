#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include "parameters.h"


#include "my_protocol.h"



int main (int argc, char **argv) {
	int i, j;
	
	// context
	void *context = zmq_ctx_new ();
	void *socket  = zmq_socket (context, ZMQ_REP);
	int errMsg = zmq_bind (socket, "tcp://*:5555");
	if (errMsg != 0) {
		fprintf (stderr, "Error binding socket\n");
		return errMsg;
	}

	unsigned int pending, completed;
	pending = N*M;
	completed = 0;
	
	message_t message;
	attach_t attach;
		attach = (attach_t) malloc (ATTACH_MAX_SIZE * sizeof (int));
	int *rop = (int*) malloc (M*N * sizeof (int));
	
	do {
		printf ("waiting orders...\n");
		zmq_recv (socket, &message, sizeof (message_t), 0);
		printf ("client sent message: ");
		switch (message.header) {
			case SEND_ME:
				printf ("requests tasks\n");
				if (!pending) {
					// ANSWER CLIENT NO MORE TASKS
					message.header = NO_MORE;	
					zmq_send (socket, &message, sizeof (message_t), 0);
				} else {
					// PREPARE TASKS FOR CLIENT
					message.header = SEND_YOU;
					message.index = M*N - pending;
					if (message.len > pending) message.len = pending;
					pending -= message.len;
					zmq_send (socket, &message, sizeof (message_t), 0);
				}
				break;
			case WORK_DONE:
				printf ("request send completed task\n");
				// RECIVE THE COMPLETED TASKS FROM THE CLIENT
				zmq_recv (socket, attach, message.len*sizeof (int), 0);

	printf ("attach = %2hhi", attach[0]);
	for (i=1; i<message.len; ++i) printf (", %2hhi", attach[i]);
	printf ("\n");

				for (i=0; i<message.len; ++i) rop[message.index+i] = attach[i];
				completed += message.len;
				// ANSER THE CLIENT
				message.header = THANK_YOU;
				zmq_send (socket, &message, sizeof (message_t), 0);
				break;
			default:
				fprintf (stderr, "bad message\n");
				break;				
		}
	} while (completed < M*N);
	
	
	printf ("rop = %2hhi", rop[0]);
	for (i=1; i<M*N; ++i) printf (", %i", rop[i]);
	printf ("\n");

	FILE *fout = fopen ("control.txt", "w");
	for (i=0; i<M; ++i) {
		for (j=0; j<N; ++j) fprintf (fout, "%i ", rop[N*i+j]);
		fprintf (fout, "\n");
	}
	fclose (fout);

	zmq_close (socket);
	zmq_ctx_destroy (context);
	free (rop);
	free (attach);
	return 0;
	

}
	


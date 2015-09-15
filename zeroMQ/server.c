#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>


#define N	8
#define M	8

#include "my_protocol.h"



int main (int argc, char **argv) {
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
		attach = (attach_t) malloc (512 * sizeof (char));
	char *rop = (char*) malloc (M*N * sizeof (char));
	int i;
	
	do {
		printf ("waiting orders...\n");
		zmq_recv (socket, &message, sizeof (message_t), 0);
		printf ("client sent message: ");
		switch (message.header) {
			case SEND_ME:
				printf ("requests tasks\n");
				if (!pending) {
					// ANSER CLIENT NO MORE TASKS
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
				zmq_recv (socket, attach, message.len, 0);

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
	for (i=1; i<M*N; ++i) printf (", %2hhi", rop[i]);
	printf ("\n");

	zmq_close (socket);
	zmq_ctx_destroy (context);
	free (rop);
	return 0;
	

}
	


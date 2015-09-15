#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>


#define N	64
#define M	64

#include "my_protocol.h"

int main (int argc, char **argv) {
	// context of zeroMQ
	void *context = zmq_ctx_new ();
	void *socket  = zmq_socket (context, ZMQ_REQ);
	int errMsg = zmq_connect (socket, "tcp://localhost:5555");
	if (errMsg != 0) {
		fprintf (stderr, "Error binding socket\n");
		return errMsg;
	}

	message_t message;
	attach_t attach;
		attach = (attach_t) malloc (512 * sizeof (char));

	size_t len = 16;
	message.header = SEND_ME;
	message.len = len;
	zmq_send (socket, &message, sizeof (message_t), 0);
	zmq_recv (socket, &message, sizeof (message_t), 0);
	if (message.header == NO_MORE) {
		fprintf (stderr, "Server has no more tasks\n");
		return 0;
	}

	printf ("task index = %u, task len = %zu\n", message.index, message.len);
	// PROCESS TASK
	printf ("press enter to process task\n"); getchar ();
	int i;
	for (i=message.index; i<message.index + message.len; ++i)
		attach[i-message.index] = i;

	// SEND COMPLETED TASK
	message.header = WORK_DONE;
	zmq_send (socket, &message, sizeof (message_t), ZMQ_SNDMORE);
	zmq_send (socket, attach, message.len, 0);
	zmq_recv (socket, &message, sizeof (message_t), ZMQ_SNDMORE);
	if (message.header != THANK_YOU) {
		fprintf (stderr, "Stupid Flanders Server.\n");
		return 0;
	}



	return 0;
}










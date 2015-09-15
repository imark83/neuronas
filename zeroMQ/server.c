#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>


#define N	64
#define M	64

#include "my_protocol.h"



int main (int argc, char **argv) {
	// context
	void *context = zmq_ctx_new ();
	void *socket  = zmq_socket (context, ZMQ_REP);
	int errMsg = zmq_bind (socket, "tcp://eth0:5555");
	if (errMsg != 0) {
		fprintf (stderr, "Error binding socket\n");
		return errMsg;
	}

	unsigned int pending, completed;
	pending = N*M;
	completed = 0;
	
	message_t buffer;
	char *rop = (char*) malloc (M*N * sizeof (char));
	
	do {
		zmq_recv (socket, &buffer, sizeof (message_t), 0);
		switch (buffer.header) {
			case SEND_ME:
				if (!pending) {
					buffer.header = NO_MORE;					
				} else {
					buffer.header = SEND_YOU;
					buffer.index = M*N - pending;
					++pending;
				}
				break;
			case WORK_DONE:
				rop[buffer.index] = buffer.rop;
				buffer.header = THANK_YOU;
				++completed;
				break;
			default:
				fprintf (stderr, "bad message\n");
				break;				
		}
		zmq_send (socket, &buffer, sizeof (message_t), 0);	
	} while (completed < M*N);
	
	

	zmq_close (socket);
	zmq_ctx_destroy (context);
	free (rop);
	return 0;
	

}
	


#ifndef __my_protocol_h__
#define __my_protocol_h__

typedef enum {SEND_ME=0, SEND_YOU, NO_MORE, WORK_DONE, THANK_YOU} header_t;

typedef struct _message_t {
	header_t header;		// header of the message
	unsigned int index;		// position of data processed
	unsigned int len;		// length of data processed
} message_t;

typedef char* attached_t;	// data processed

#endif


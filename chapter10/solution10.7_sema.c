#include <u.h>
#include <libc.h>

enum { Nmsgs = 4 };

typedef struct Sem Sem;
struct Sem {
	int fd[2];
};

typedef struct Buffer Buffer;
struct Buffer {
	Sem* mutex; 		// for mutual exclusion
	char* msgs[Nmsgs];	// messages in buffer
	int hd;			// head of the queue
	int tl;			// tail. First empty slot
	int nmsgs;		// number of messages
	Sem* smsgs;		// (0 tickets) acquire a msg
	Sem* sholes;		// (Nmsgs tickets) acquire a hole
};

Sem*
newsem(int n)
{
	Sem* s;

	s = malloc(sizeof(*s));
	if(pipe(s->fd) < 0){
		free(s);
		return nil;
	}
	while(n-- > 0)
		write(s->fd[1], "x", 1);
	return s;
}

void
init(Buffer* b)
{
	memset(b, 0, sizeof(*b));
	b->mutex = newsem(1);
	b->smsgs = newsem(0);
	b->sholes = newsem(Nmsgs);
}

void
semsignal(Sem* s)
{
	write(s->fd[1], "x", 1);
}

void
semwait(Sem *s)
{
	char buf[1];
	read(s->fd[0], buf, 1);
}

void
put(Buffer* b, char* msg)
{
	semwait(b->sholes);
	semwait(b->mutex);
	b->msgs[b->tl] = strdup(msg);
	b->tl = ++b->tl % Nmsgs;
	b->nmsgs++;
	semsignal(b->mutex);
	semsignal(b->smsgs);
}

char*
get(Buffer* b)
{
	char* msg;

	semwait(b->smsgs);
	semwait(b->mutex);
	msg = b->msgs[b->hd];
	b->hd = ++b->hd % Nmsgs;
	b->nmsgs--;
	semsignal(b->mutex);
	semsignal(b->sholes);
	return msg;
}

void
producer(Buffer* b, char id)
{
	char msg[20];
	int i;

	for(i=0; i<5; i++){
		seprint(msg, msg+20, "%c%d", id, i);
		put(b, msg);
	}
	exits(nil);
}

void
consumer(Buffer* b)
{
	char* msg;
	while(msg = get(b)){
		// consume it
		print("%s ", msg);
		free(msg);
	}
	exits(nil);
}

Buffer buf;

void
main(int, char*[])
{
	init(&buf);

	if (rfork(RFPROC|RFMEM|RFNOWAIT) == 0)
		producer(&buf, 'a');
	if (rfork(RFPROC|RFMEM|RFNOWAIT) == 0)
		producer(&buf, 'b');

	consumer(&buf);
}

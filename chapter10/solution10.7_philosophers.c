#include <u.h>
#include <libc.h>
#include <thread.h>

enum { Nphilosophers = 5 };
Channel* bufc;

void
producer(void* arg)
{
}

void
consumer(void*)
{
}

void
threadmain(int, char*[])
{
	int i;

	for(i=0; i<Nphilosophers; i++){
	}
}

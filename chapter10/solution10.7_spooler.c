#include <u.h>
#include <libc.h>

enum { Nmaxjobs = 5, Ndatasiz = 512 };

typedef struct Printjob Printjob;
struct Printjob {
	char* data;
};

typedef struct Spooler Spooler;
struct Spooler {
	QLock lck;
	Printjob jobs[Nmaxjobs];
	int njobs;
};

Spooler spooler;

void
spoolerinit(Spooler* s)
{
	s->njobs = 0;
}

void
printer(void)
{
	for(;;){
		qlock(&spooler.lck);
		if(spooler.njobs > 0){
			print("printer: printing %d %s\n",
				spooler.njobs, spooler.jobs[--spooler.njobs].data);
		}
		qunlock(&spooler.lck);
		sleep(100);
	}
}

void
reader(void)
{
	char buf[Ndatasiz];
	int nr;

	for(;;){
		nr = read(0, buf, sizeof(buf)-1);
		if(nr <= 0)
			break;
		buf[nr] = 0;
		qlock(&spooler.lck);
		print("reader: sending job %d to printer\n", spooler.njobs);
		spooler.jobs[spooler.njobs++].data = strdup(buf);
		qunlock(&spooler.lck);
	}
	exits(nil);
}

void
main(int, char*[])
{
	spoolerinit(&spooler);
	if(rfork(RFPROC|RFMEM|RFNOWAIT) == 0)
		printer();
	reader();
}

#include <u.h>
#include <libc.h>

void
main(int argc, char* argv[])
{
	Waitmsg *m;
	int pid;

	if(argc < 2){
		fprint(2, "usage: %s command..\n", argv0);
		exits("usage");
	}

	pid = fork();
	switch(pid){
	case -1:
		sysfatal("fork: %r");
	case 0:
		exec(argv[1], &argv[1]);
		sysfatal("exec: %r");
	default:
		while(m = wait()){
			if(m->pid == pid){
				if(m->msg[0] == 0){
					print("%ld.%.2ldu %ld.%.2lds %ld.%.2ldr %s\n",
						m->time[0]/1000, (m->time[0]%1000)/10,
						m->time[1]/1000, (m->time[1]%1000)/10,
						m->time[2]/1000, (m->time[2]%1000)/10,
						argv[1]);
					free(m);
					exits(nil);
				}
			}
			free(m);
		}
	}
	exits(nil);
}

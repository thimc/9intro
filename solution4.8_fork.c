#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	Waitmsg *m;
	int f1, f2;
	int ret;

	f1 = fork();
	f2 = fork();

	switch(f1){
	case -1:
		sysfatal("fork1: %r");
	case 0:
		print("hi from %d\n", getpid());
		exits(nil);
	default:
		while(m = wait()){
			if(m->pid == f1){
				if(m->msg[0] == 0){
					ret = 0;
				} else{
					werrstr(m->msg);
					ret = -1;
				}
				free(m);
				if(ret < 0)
					sysfatal("fork1: %r");
			}
		}
	}

	switch(f2){
	case -1:
		sysfatal("fork2: %r");
	case 0:
		print("hi from %d\n", getpid());
		exits(nil);
	default:
		while(m = wait()){
			if(m->pid == f2){
				if(m->msg[0] == 0){
					ret = 0;
				} else{
					werrstr(m->msg);
					ret = -1;
				}
				free(m);
				if(ret < 0)
					sysfatal("fork2: %r");
			}
		}
	}

	print("hi from %d\n", getpid());
	exits(nil);
}


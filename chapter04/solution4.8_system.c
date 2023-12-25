#include <u.h>
#include <libc.h>

char*
system(char* cmd)
{
	Waitmsg *m;
	char *msg;
	char *args[] = {"rc", "-c", cmd, nil};
	int pid;

	pid = fork();
	switch(pid){
	case -1:
		sysfatal("fork: %r");
	case 0:
		exec("/bin/rc", args);
		sysfatal("exec: %r");
	default:
		while(m = wait()){
			if(m->pid == pid){
				if(m->msg[0] == 0){
					free(m);	
					return nil;
				}else{
					msg = strdup(m->msg);
					free(m);
				}
			}
		}
	}
	return msg;
}

void
main(int argc, char* argv[])
{
	char *msg;

	msg = system("ls -l /tmp");
	if(msg != nil){
		print("uh oh: %s\n", msg);
		free(msg);
	}

	exits(nil);
}

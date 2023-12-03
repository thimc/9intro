#include <u.h>
#include <libc.h>

int
run(char* cmd, char* argv[])
{
	Waitmsg* m;
	int ret;
	int pid;
	pid = fork();
	switch(pid){
	case -1:
		return -1;
	case 0:		// child
		exec(cmd, argv);
		sysfatal("exec: %r");
	default:
		while(m = wait()){
			if (m->pid == pid){
				if (m->msg[0] == 0)
					ret = 0;
				else {
					werrstr(m->msg);
					ret  = -1;
				}
				free(m);
				return ret;
			}
			free(m);
		}
		return -1; // needed due to `35bbbb.c:30 no return at end of function: run`
	}
}

void
main(int, char*[])
{
	char* args[] = { "du", "-a", "/tmp", nil };
	if(run("/bin/du", args) < 0)
		sysfatal("run: %r");
	print("parent done\n");

	Waitmsg *m;
	if (fork() == 0) {
		// do something in this child...
	} else {
		run("/bin/du", args);
		m = wait();
		// ...
		print("is m nil? %s\n", m==nil ? "yes" : "no");
		free(m);
	}
	exits(nil);
}

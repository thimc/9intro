#include <u.h>
#include <libc.h>

int
run(char* cmd, char* argv[])
{
	Waitmsg* m;
	int ret;
	switch(fork()){
	case -1:
		return -1;
	case 0:		// child
		exec(cmd, argv);
		sysfatal("exec: %r");
	default:
		m = wait();
		if (m->msg[0] == 0)
			ret = 0;
		else {
			werrstr(m->msg);
			ret = -1;
		}
		free(m);
		return ret;
	}
}

void
main(int, char*[])
{
	char* args[] = { "du", "-a", "/tmp", nil };
	if(run("/bin/du", args) < 0)
		sysfatal("run: %r");
	print("parent done\n");
	exits(nil);
}

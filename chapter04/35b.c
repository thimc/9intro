#include <u.h>
#include <libc.h>

int
run(char* cmd, char* argv[])
{
	switch(fork()){
	case -1:
		return -1;
	case 0:		// child
		exec(cmd, argv);
		sysfatal("exec: %r");
	default:
		// parent
		return 0;
	}
}

void
main(int, char*[])
{
	char* args[] = { "ls", "-l", "/", nil };
	if(run("/bin/ls", args) < 0)
		sysfatal("run: %r");
	exits(nil);
}

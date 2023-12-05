#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	int fd;
	switch(fork()){
	case -1:
		sysfatal("fork: %r");
	case 0:
		close(0); // WRONG!
		fd = open("NOTICE", OREAD);
		assert(fd == 0);
		execl("/bin/cat", "cat", nil);
		sysfatal("exec: %r");
	default:
		waitpid();
	}
	exits(nil);
}

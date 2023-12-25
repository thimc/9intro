#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	int fd;
	switch(fork()){
	case -1:
		sysfatal("fork failed");
	case 0:
		fd = open("NOTICE", OREAD);
		dup(fd, 0);
		close(fd);
		fd = create("outfile", OWRITE, 0644);
		dup(fd, 1);
		close(fd);
		execl("/bin/cat", "cat", nil);
		sysfatal("exec: %r");
	default:
		waitpid();
	}
	exits(nil);
}

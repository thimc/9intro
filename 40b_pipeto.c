#include <u.h>
#include <libc.h>

// TODO: Unfinished example from the book

long
cmdoutput(char* cmd, char *buf, long len)
{
	int fd[2];
	long tot, nr;
	if (pipe(fd) < 0)
		return -1;	// failed to create a pipe
	switch(fork()){
	case -1:
		return -1;
	case 0:
		close(fd[0]);
		dup(fd[1], 1);
		close(fd[1]);
		execl("/bin/rc", "rc", "-c", cmd, nil);
		sysfatal("exec");
	default:
		close(fd[1]);
		for(tot = 0; len - tot > 1; tot += nr){
			nr = read(fd[1], buf+tot, len - tot);
			if (nr <= 0){
				print("no output\n");
				break;
			}
		}
		close(fd[0]);
		waitpid();
		buf[tot] = 0;	// terminate string
		return tot;
	}
}

void
main(int, char*[])
{
	char buf[1024];
	long nr;

	nr = cmdoutput("wc *.c", buf, (long)sizeof(buf));
	if (nr <= 0)
		sysfatal("cmdoutput: %r");
	write(1, buf, nr);

	exits(nil);
}


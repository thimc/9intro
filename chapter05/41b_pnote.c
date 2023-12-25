#include <u.h>
#include <libc.h>

int
cleanup(void*, char* msg)
{
	print("note: %s\n", msg);
	if (strcmp(msg, "interrupt") == 0)
		remove("/tmp/tempfile");
	return 1;
}

void
main(int, char*[])
{
	int fd;

	fd = create("/tmp/tempfile", ORDWR|ORCLOSE, 0644);
	write(fd, "waiting for interrupt\n", 24);
	atnotify(cleanup, 1);
	sleep(3600 * 1000);	// one hour to play
	print("done (%r)\n");
	close(fd);
	exits(nil);
}

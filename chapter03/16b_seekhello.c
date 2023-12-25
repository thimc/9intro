#include <u.h>
#include <libc.h>
void
main(int, char*[])
{
	int fd;

	fd = open("afile", OWRITE);
	seek(fd, 0, 2); /* move to the end */
	write(fd, "there\n", 6);
	close(fd);
	exits(nil);
}

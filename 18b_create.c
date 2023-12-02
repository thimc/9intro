#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	int fd;

	fd = create("adir", OREAD, DMDIR|0755);
	close(fd);

	exits(nil);
}

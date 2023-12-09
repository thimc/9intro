#include <u.h>
#include <libc.h>

void
main(int argc, char* argv[])
{
	int fd;
	char* addr, *sys;
	char buf[128];
	long nr;

	sys = getenv("sysname");
	addr = netmkaddr(sys, "tcp", "time");
	fd = dial(addr, nil, nil, nil);
	if (fd < 0)
		sysfatal("dial: %s: %r", addr);

	nr = read(fd, buf, sizeof buf);
	write(1, buf, nr);

	close(fd);
	exits(nil);
}

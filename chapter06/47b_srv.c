#include <u.h>
#include <libc.h>

void
main(int argc, char* argv[])
{
	int fd, srvfd;
	char* addr;
	char fname[128], dir[64];

	if (argc != 2){
		fprint(2, "usage: %s netaddr\n", argv0);
		exits("usage");
	}

	addr = netmkaddr(argv[1], "tcp", "9fs");
	fd = dial(addr, nil, dir, nil);
	if (fd < 0)
		sysfatal("dial: %s: %r", addr);
	print("dial: %s\n", dir);
	seprint(fname, fname+sizeof(fname), "/srv/%s", argv[1]);
	srvfd = create(fname, OWRITE, 0664);
	if (srvfd < 0)
		sysfatal("can't post: %s: %r", fname);
	if (fprint(srvfd, "%d", fd) < 0)
		sysfatal("can't post file descriptor: %r");
	close(srvfd);
	close(fd);
	exits(nil);
}

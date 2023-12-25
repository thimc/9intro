#include <u.h>
#include <libc.h>
#include <plumb.h>

void
main(int, char*[])
{
	int fd;
	Plumbmsg m;
	char buf[128];
	getwd(buf, sizeof(buf));

/*
	fd = plumbopen("send", OWRITE);
	if (fd < 0)
		sysfatal("open: %r");
	if (plumbsendtext(fd, argv0, nil, buf, "NOTICE") < 0)
		sysfatal("send: %r");
*/

	fd = plumbopen("send", OWRITE);
	if (fd < 0)
		sysfatal("open: %r");
	m.src = m.dst = nil;
	m.type = "text";
	m.attr = nil;
	m.data = "NOTICE";
	m.ndata = strlen(m.data);
	m.wdir = buf;

	if (plumbsend(fd, &m) < 0)
		sysfatal("send: %r");

	close(fd);
	exits(nil);
}

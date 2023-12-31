#include <u.h>
#include <libc.h>
#include <bio.h>

void
usage(void)
{
	fprint(2, "usage: %s [-b bufsz] infile outfile\n", argv0);
	exits("usage");
}

void
main(int argc, char* argv[])
{
	char *buf;
	long nr, bufsz = 8*1024;
	Biobuf* bin;
	Biobuf* bout;

	ARGBEGIN{
	case 'b':
		bufsz = atoi(EARGF(usage));
		break;
	default:
		usage();
	}ARGEND;
	if (argc != 2)
		usage();
	buf = malloc(bufsz);
	if (buf == nil)
		sysfatal("no more memory");
	bin = Bopen(argv[0], OREAD);
	if (bin == nil)
		sysfatal("%s: %s: %r", argv0, argv[0]);
	bout = Bopen(argv[1], OWRITE);
	if (bout == nil)
		sysfatal("%s: %s: %r", argv0, argv[0]);
	for (;;) {
		nr = Bread(bin, buf, bufsz);
		if (nr <= 0)
			break;
		Bwrite(bout, buf, nr);
	}
	Bterm(bin);
	Bterm(bout);
	exits(nil);
}
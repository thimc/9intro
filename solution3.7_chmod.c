#include <u.h>
#include <libc.h>

void
usage(void)
{
	fprint(2, "usage: %s <octal> file ... \n", argv0);
	exits("usage");
}

void
main(int argc, char* argv[])
{
	Dir d;
	int fd, i;
	ulong perm;

	if(argc<2)
		usage();

	perm = strtoul(argv[1], nil, 8);

	for(i = 2; i < argc; i++){
		nulldir(&d);
		d.mode = perm;
		if(dirwstat(argv[i], &d) < 0)
			sysfatal("dirwstat: %r");
	}

	exits(nil);
}
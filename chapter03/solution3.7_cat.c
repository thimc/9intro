#include <u.h>
#include <libc.h>
#include <bio.h>

void
usage(void)
{
	fprint(2, "usage: %s file ..\n", argv0);
	exits("usage");
}

void
main(int argc, char* argv[])
{
	Biobuf bout;
	Biobuf *b;
	char *buf;
	long nr, i, bufsz = 1024;

	if (argc < 2)
		usage();

	Binit(&bout, 1, OWRITE);
	buf = malloc(bufsz);
	if(buf==nil)
		sysfatal("malloc: %r");

	for(i = 1; i < argc; i++){
		b = Bopen(argv[i], OREAD);
		if(b==nil)
			sysfatal("Bopen: %r");
		for(;;){
			nr = Bread(b, buf, bufsz);
			if(nr <= 0)
				break;
			Bwrite(&bout, buf, nr);
		}
		Bterm(b);
	}

	Bterm(&bout);
	exits(nil);
}
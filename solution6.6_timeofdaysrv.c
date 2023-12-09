#include <u.h>
#include <libc.h>

void
main(int argc, char* argv[])
{
	int cfd, lfd, dfd;
	char adir[40];
	char ldir[40];
	char buf[1024];
	Tzone *tz;
	Tm tm;

	tmfmtinstall();
	tz = tzload("local");
	if(tz == nil)
		sysfatal("timezone: %r");

	cfd = announce("tcp!*!37", adir);
	if (cfd < 0)
		sysfatal("announce: %r");
	print("announced in %s\n", adir);

	for(;;) {
		lfd = listen(adir, ldir);
		if (lfd < 0)
			sysfatal("listen: %r");

		switch(fork()){
		case -1:
			sysfatal("fork: %r");
		case 0:
			close(cfd);
			dfd = accept(lfd, ldir);
			if (dfd < 0)
				sysfatal("can't accept: %r");
			close(lfd);
			print("accepted call at %s\n", ldir);
			fprint(dfd, "%τ\n", tmfmt(tmnow(&tm, tz), nil));
			print("terminated call at %s\n", ldir);
			exits(nil);
		default:
			close(lfd);
		}
	}
}

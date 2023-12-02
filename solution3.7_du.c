#include <u.h>
#include <libc.h>

int
printstat(Dir *d)
{
	print("%d %s\n", d->length, d->name);
	return d->length;
}

void
iteratedir(char *name)
{
	Dir *dents;
	int ndents, fd, i, tot;

	fd = open(name, OREAD);
	if(fd<0)
		sysfatal("open: %r");

	ndents = dirread(fd, &dents);
	if(ndents <= 0){
		dents = dirstat(name);
		if(dents == nil)
			sysfatal("dirstat: %r");
		printstat(dents);
		return;
	}

	tot=0;
	for(i = 0; i < ndents; i++)
		tot += printstat(&dents[i]);

	print("total: %d bytes\n", tot);
	free(dents);
	close(fd);
}

void
main(int argc, char *argv[])
{
	int i;

	if(argc <= 1){
		iteratedir(".");
	}else{
		for(i = 1; i < argc; i++){
			iteratedir(argv[i]);
		}
	}

	exits(nil);
}
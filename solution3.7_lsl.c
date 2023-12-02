#include <u.h>
#include <libc.h>

void
printstat(Dir *d)
{
	/* TODO: Convert d->mode to char representations */
	/* TODO: Add padding */

	char* t = ctime(d->mtime);
	char time[28];
	memmove(time, t, 28);
	time[28]=0;

	print("%o %C %d %s %s %ud %s %s\n",
		d->mode,
		d->type,
		d->dev,
		d->uid,
		d->gid,
		d->length,
		time,
		d->name);
}

void
iteratedir(char *name)
{
	Dir *dents;
	int ndents, fd, i;

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

	for(i = 0; i < ndents; i++)
		printstat(&dents[i]);

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
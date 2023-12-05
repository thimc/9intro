#include <u.h>
#include <libc.h>

#define LEN(x) ((sizeof x) / (sizeof x[0]))


int
handler(void*, char *msg)
{
	if(!strcmp(msg,"alarm")){
		fprint(2, "timed out\n");
		return 1;
	}
	return 0;
}


long
robustreadn(int fd, char *buf, long n)
{
	long nr, tot;
	char err[ERRMAX];

	for(tot=0; tot<n; tot+=nr){
		nr = read(fd, buf+tot, n-tot);
		if(nr==0)
			break;
		if(nr<0){
			rerrstr(err, sizeof(err));
			if(strcmp(err, "interrupted")==0)
				nr=0;
			else
				break;
		}
	}
	return tot;
}

void
main(int, char *[])
{
	char buf[1024];
	long nr;

	atnotify(handler, 1);
	print("type something: ");
	alarm(5 * 1000);
	nr = read(0, buf, sizeof buf);
	alarm(0);
	if(nr>=0)
		write(1, buf, nr);

	exits(nil);
}

#include <u.h>
#include <libc.h>

void
httpservice(void)
{
	sleep(50000);
}

int
httpinit(void)
{
	sleep(2000);
	return 0;
}

void
main(int, char*[])
{
	int i;
	int childsts;

	switch(rfork(RFPROC|RFNOTEG|RFNOWAIT)){
	case 0:
		if(httpinit() < 0)
			rendezvous(&main, (void*)-1);
		else
			rendezvous(&main, (void*)0);
		httpservice();	// do the job
		exits(nil);
	case -1:
		sysfatal("rfork: %r");
	default:
		childsts = (int)rendezvous(&main, (void*)0);
		if(childsts == 0)
			exits(nil);
		else {
			fprint(2, "httpinit failed\n");
			exits("httpinit failed");
		}
	}
}

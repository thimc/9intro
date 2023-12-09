#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	switch(rfork(RFFDG|RFREND|RFPROC|RFNOWAIT)){
	case -1:
		sysfatal("fork failed");
	case 0:
		print("I am the child");
		break;
	default:
		print("I am the parent");
	}
	exits(nil);
}

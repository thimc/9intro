#include <u.h>
#include <libc.h>

void
usage(void)
{
	fprint(2, "usage: %s [-ab] [-d args]\n");
	exits("usage");
}

void
main(int argc, char *argv[])
{
	int i, d;
	char *args, *tmp;

	ARGBEGIN{
	case 'a':
		putenv("opta", "yes\n");
		break;
	case 'b':
		putenv("optb", "yes\n");
		break;
	case 'd':
		putenv("optc", "yes\n");
		break;
	default:
		usage();
	}ARGEND;
	args=nil;

	for(i=0; i<argc; i++){
		args=getenv("args");
		if(args == nil || strcmp(args, "") == 0){
			args=argv[i];
		} else {
			args=strcat(args, " ");
			args=strcat(args, argv[i]);
		}
		putenv("args", args);
	}

	args=strcat(getenv("args"), "\n");
	putenv("args", args);

	exits(nil);
}
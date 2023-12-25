#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	char* home;
	print("running ls\n");
	home = getenv("home");
	execl("/bin/ls", "-l", home, nil);
	print("exec failed: %r\n");
}

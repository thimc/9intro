#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	print("running ls\n");
	execl("ls", "-l", "/usr/glenda", nil);
	print("exec failed: %r\n");
}

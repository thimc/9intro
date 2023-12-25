#include <u.h>
#include <libc.h>

// TODO: Unfinished example from the book

long
robustreadn(int fd, char* buf, long n)
{
	long nr, tot;
	char err[128];

	for (tot = 0; tot < n; tot += nr){
		nr = read(fd, buf+tot, n-tot);
		if (nr == 0)
			break;
		if (nr < 0){
			rerrstr(err, sizeof(err));
			if (strcmp(err, "interrupted") == 0){
				fprint(2, "interrupted, retry\n");
				nr = 0; // retry
			} else {
				break;
			}
		}
	}
	return tot;
}

int
handler(void*, char* msg)
{
	print("note: %s\n", msg);
	return 0;
}

void
main(int, char*[])
{
}

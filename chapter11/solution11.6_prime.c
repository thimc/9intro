#include <u.h>
#include <libc.h>
#include <thread.h>

typedef struct Context Context;
struct Context {
	QLock lck;
	int start, end;
};
Context ctx;

int
isprime(int n)
{
	int i;

	if(n <= 1) return 0;
	for(i=2; i*i <= n; i++)
		if(n%i == 0) return 0;
	return 1;
}

void
primethread(void* arg)
{
	Context* ctx = arg;
	int i;

	for(i=ctx->start; i<=ctx->end; i++){
		qlock(&ctx->lck);
		if(isprime(i)){
			print("%d is prime\n", i);
		}
		qunlock(&ctx->lck);
	}
	threadexits(nil);
}

void
threadmain(int, char*[])
{
	ctx.start = 1;		// minimum value
	ctx.end = 8*1024;	// maximum value

	threadcreate(primethread, &ctx, 8*1024);
	threadexits(nil);
}

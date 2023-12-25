#include <u.h>
#include <libc.h>
#include <thread.h>

enum { Ncars = 5, Ncrosstime = 200 };

Channel* bridgec;

typedef struct Car Car;
struct Car {
	int fd;
};

void
bridgethread(void*)
{
	Car* car;

	threadsetname("bridge");
	while(car = recvp(bridgec)){
		print("Car %d is crossing the bridge\n", car->fd);
		sleep(Ncrosstime);
		yield();
	}
	print("All cars have passsed the bridge\n");
	threadexits(nil);
}

void
threadmain(int, char*[])
{
	int i;
	Car* car;

	bridgec = chancreate(sizeof(Car), 0);
	threadcreate(bridgethread, nil, 8*1024);
	for(i=0; i<Ncars; i++){
		car = malloc(sizeof(*car));
		car->fd = i;
		print("Car %d is heading towards the bridge\n", car->fd);
		send(bridgec, &car);
	}
	sendp(bridgec, nil);
	threadexits(nil);
}

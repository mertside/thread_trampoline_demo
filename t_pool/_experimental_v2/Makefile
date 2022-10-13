CC=gcc
CFLAGS=-Wall -lpthread
poolAppName=thread_pool_sample

all: threadpool.o version2

version2: threadpool.o $(poolAppName)_v3.c 
	$(CC) $(CFLAGS) threadpool.o $(poolAppName)_v3.c -o $(poolAppName)_v2.out

threadpool.o: threadpool.c threadpool.h
	$(CC) $(CFLAGS) -c threadpool.c

clean:
	rm -rf $(poolAppName)_*.exe

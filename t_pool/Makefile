CC=gcc
appName=thread_trampoline_sample
poolAppName=thread_pool_sample

all: pool2 

pool1: $(poolAppName)_v1.c
	$(CC) -Wall $^ -lpthread -o $(poolAppName)_v1.exe  

pool2: $(poolAppName)_v2.c                                                    
	$(CC) -Wall $^ -lpthread -o $(poolAppName)_v2.exe

clean:
	rm -rf $(poolAppName)_*.exe

CC=gcc
progName=xfer_test
asmbName=xbrtime_api_morello_asm
execName=test

all: version1 

version1: $(progName)_v1.c 
	$(CC) $^ $(asmbName).s -o $(execName)_v1.exe  

version2: $(progName)_v2.c 
	$(CC) $^ $(asmbName).s -o $(execName)_v2.exe 

clean:
	rm -rf $(execName)_*.exe

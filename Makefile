CC=gcc
appName=thread_trampoline_sample

all: version1 version2 version3 version4 version5 version6 version7

version1: $(appName)_v1.c
	$(CC) -Wall $^ -lpthread -o $(appName)_v1.exe

version2: $(appName)_v2.c
	$(CC) -Wall $^ -lpthread -o $(appName)_v2.exe

version3: $(appName)_v3.c
	$(CC) -Wall $^ -lpthread -o $(appName)_v3.exe

version4: $(appName)_v4.c
	$(CC) -Wall $^ -lpthread -o $(appName)_v4.exe

version5: $(appName)_v5.c
	$(CC) -Wall $^ -lpthread -o $(appName)_v5.exe

version6: $(appName)_v6.c
	$(CC) -Wall $^ -lpthread -o $(appName)_v6.exe

version7: $(appName)_v7.c                                                       
	$(CC) -Wall $^ -lpthread -o $(appName)_v7.exe 

test:
	./$(appName)_v1.exe
	./$(appName)_v2.exe
	./$(appName)_v3.exe
	./$(appName)_v4.exe
	./$(appName)_v5.exe
	./$(appName)_v6.exe
	./$(appName)_v7.exe

clean:
	rm -rf *.exe

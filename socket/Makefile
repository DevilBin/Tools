all:	server.cpp client.cpp padfile.c
	@g++ -m32 -pthread -o server server.cpp
	@g++ -m32 -pthread -o client client.cpp
	@gcc -m32 -o padfile padfile.c
clean:
	@rm -rf server client padfile

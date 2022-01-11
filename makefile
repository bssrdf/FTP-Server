all: socket_utilities.c common.c main.c protocol.c
	cc -std=c99 -D_XOPEN_SOURCE=600 -D_DEFAULT_SOURCE -g -pedantic -Wall -W -Wmissing-prototypes -Wno-sign-compare -Wimplicit-fallthrough -Wno-unused-parameter -pthread -o ftp_server protocol.c common.c socket_utilities.c main.c
clean:
	rm -f main.o common.o socket_utilities.o protocol.o ftp_server


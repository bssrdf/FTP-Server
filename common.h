#ifndef COMMON_HEADERS
#define COMMON_HEADERS

// General
#include <limits.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>
// Networking
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
// ############# Server parameters #############

#define CLIENTS_PER_THREAD 200
#define TOTAL_NO_THREADS 500
#define MAX_EVENTS (2*CLIENTS_PER_THREAD+1)

// #############################################

// Macros
#define FD_SIZE sizeof(int)
#define MASTER_PORT 7
#define TRUE 1
#define FALSE 0
#define BACKLOG 100000
#define MAX_OPEN_DESC 1024
#define THREAD_PRIORITY_LOW 20
#define THREAD_PRIORITY_HIGH 50
#define REQ_COMMAND_LENGTH 20
#define REQ_ARG_LENGTH 40
#define BUFF_SIZE 1024
#define FILE_NAME_LEN 20

int clients_active = 0;
pthread_mutex_t mutex;

// Structs
typedef struct arguments
{
	int cli_sock;
}arguments_t;


struct client_s
{
	int client_fd;
	int data_fd;
	int file_fd;
	struct sockaddr_in act_mode_client_addr;
};


void increment_clients_count()
{
        // Lock
        pthread_mutex_lock(&mutex);
        clients_active++;
        // Unlock
        pthread_mutex_unlock(&mutex);
}

void decrement_clients_count()
{
        // Lock
        pthread_mutex_lock(&mutex);
        clients_active--;
        // Unlock
        pthread_mutex_unlock(&mutex);
}


void set_res_limits()
{
	// Set MAX FD's to 100000
	struct rlimit res;
	res.rlim_cur = 1000000;
	res.rlim_max = 1000000;
	if( setrlimit(RLIMIT_NOFILE, &res) == -1 )
	{
		perror("Resource FD limit");
		exit(0);
	}
	printf("FD limit set to 1000000\n");	
	if( setrlimit(RLIMIT_RTPRIO, &res) == -1 )
	{
		perror("Resource Prioiry limit");
		exit(0);
	}
	printf("Prioirty limit set to 100\n");
}

int read_descriptor(int slave, struct client_s* client)
{
	int client_fd;
	int n = Read(slave,(char*)&client_fd,FD_SIZE,client);
	if( n == FD_SIZE )
	{
		return client_fd;
	}
	return -1;
}


void sig_term_handler()
{
	// Kill all threads
	printf("FTP Server exiting\n");
	exit(0);
}

void sig_pipe_handler()
{
	printf("Client terminated because of Pipe termination\n");
	exit(0);
}
#endif

#include "common.h"
#include "socket_utilities.h"


volatile int clients_active = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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

void monitor()
{
	while(1)
	{
		 
		time_t current_time;
        time(&current_time);
		char *t = ctime(&current_time);
		if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
		printf("%s, Count : %d\n", t, clients_active);
		sleep(2);
	}
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

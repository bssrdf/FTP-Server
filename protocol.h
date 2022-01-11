#ifndef PROTOCOL_H
#define PROTOCOL_H
//#include "common.h"
/*
	This header file contains all the protocol header required for the FTP
*/


typedef struct ftp_request
{
	char command[REQ_COMMAND_LENGTH];
	char arg[REQ_ARG_LENGTH]; 
}ftp_request_t;


void store_ip_port_active(char* arg,struct sockaddr_in* active_client_addr);
#endif

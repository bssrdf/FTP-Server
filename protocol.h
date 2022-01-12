#ifndef PROTOCOL_H
#define PROTOCOL_H
//#include "common.h"
/*
	This header file contains all the protocol header required for the FTP
*/

extern char* error;
extern char* allow_user;
extern char* system_str;
extern char* port_reply;
extern char* type_ok;
extern char* close_con;
extern char* file_error;
extern char* file_ok;
extern char* data_open_error;
extern char* greeting;
extern char* file_done;
extern char* close_con;


typedef struct ftp_request
{
	char command[REQ_COMMAND_LENGTH];
	char arg[REQ_ARG_LENGTH]; 
}ftp_request_t;


void store_ip_port_active(char* arg,struct sockaddr_in* active_client_addr);
#endif

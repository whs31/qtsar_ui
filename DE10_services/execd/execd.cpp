#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <sstream>
#include <libgen.h>
#include <linux/limits.h>   // PATH_MAX
//#include <dir.h>

#include "config_file.h"
#include <sys/stat.h>

#include <stdio.h>
#include <time.h>

void printTime(){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("[%02d-%02d-%d %02d:%02d:%02d] ", tm.tm_mday, tm.tm_mon + 1,  tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void printClient(struct sockaddr_in client){
    printf("%s:%d", inet_ntoa(client.sin_addr), (int) ntohs(client.sin_port) );
}

void flushOut(){
    fflush(stdout);
    fflush(stderr);
}

static void doDaemonize()
{
	pid_t pid = 0;
	int fd;

	/* Fork off the parent process */
	pid = fork();

	/* An error occurred */
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	/* Success: Let the parent terminate */
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	/* On success: The child process becomes session leader */
	if (setsid() < 0) {
		exit(EXIT_FAILURE);
	}

	//signal(SIGCHLD, SIG_IGN);

	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	umask(0);


	//chdir("/");

}


std::string exec(std::string cmd, int fd) {
    char buffer[16];
    std::string result = "";
	int resp = 1;
    
    cmd += " 2>&1";
    
    //std::cout << "Command: " << cmd << "\n";
    
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL && resp != -1) {	
			resp = send ( fd, buffer, strlen(buffer), MSG_NOSIGNAL );
            printf(buffer);
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    printf("\n");
    pclose(pipe);
    return result;
}



int main(int argc, char const *argv[]){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    int port = 5053;
    std::string ip;
    std::string script_path = "./scripts/";
    std::string log;
    bool daemonize = false;
    
    
    std::ifstream cfg("execd.cfg");
    if(!cfg){
        printTime();
        printf("Error reading file !\n");
        return 1;
    }
    else{
        CFG::ReadFile(cfg, {"ip", "port", "script_path", "log", "daemonize"}, ip, port, script_path, log, daemonize);
        cfg.close();
    }
    
    if(daemonize){
        doDaemonize();
        freopen( log.c_str() , "a+" , stdout);
        freopen( log.c_str() , "a+" , stderr);
    }
    
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printTime();
        perror("socket failed");
        flushOut();
        exit(EXIT_FAILURE);
    }
       
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt))){
        printTime();                                              
        perror("setsockopt");
        flushOut();
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons( port );
    
    printTime();
    if( ip.empty() ){
        address.sin_addr.s_addr = htonl(INADDR_ANY);
        printf("execd binded to INADDR_ANY:%d\n", port);
    }else{
        address.sin_addr.s_addr = inet_addr(ip.c_str());
        printf("execd binded to %s:%d\n", ip.c_str(), port);
    }
    flushOut();
       

    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0){
        printTime();
        perror("bind failed");
        flushOut();
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0){
        printTime();
        perror("listen");
        flushOut();
        exit(EXIT_FAILURE);
    }

    
    
    while(1){
    
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
            printTime();
            perror("accept");
            flushOut();
            exit(EXIT_FAILURE);
        }
        printTime();
        printf("client ");
        //printClient(client);
        printf(" connected\n");
        fflush(stdout);
        valread = -100;
        while(valread) {                                                                                                                                      	
            valread = read( new_socket , buffer, 1024);
            
            if(valread == -1){
                printTime();
                printf("Read with error\n");
                break;
            }
           
            if(valread> 0){
                buffer[valread] = 0;
                exec( "bash " + script_path + std::string(buffer), new_socket);
            }
        }
        printTime();
        printf("Client lost\n");
        close(new_socket);

    }

    return 0;
}

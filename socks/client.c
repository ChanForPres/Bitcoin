#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  
#include <errno.h>
#include <string.h>


int main() {


    // client has to a) create socket b) connect to server c) send/rcv data
    int sock_fd = socket(AF_INET, SOCK_STREAM,0); //sock create
    if (sock_fd < 0)
        strerror(errno);
    else
        printf("socket created...\n");

    struct sockaddr_in  sock_addr;
    /* sockaddr has these fields:
     * sa_family_t    sin_family
    in_port_t      sin_port
    struct in_addr sin_addr
    unsigned char  sin_zero[8]
     *
     */


    sock_addr.sin_family=  AF_INET;
    sock_addr.sin_port = htons(22000) ; //port number = allows any port to connect 
    memset((void*)&sock_addr , 0,sizeof(sock_addr) );//void *memset(void *s, int c, size_t n);


    // client doesn't bind to a port, only server does
    // use connect instead
    int connect_id = connect(sock_fd,(struct sockaddr*)&sock_addr,sizeof(sock_addr) ); // connect to address of server, connect(socket_id, sockaddr, addr_len)
    if (connect_id < 0)
        strerror(errno);
    else
        printf("connection established...\n");
    // send/rcv data
    // read/write syscalls
    
    char cbuff[] = "fg";
    int fd = open("./a.txt", O_RDWR|O_EXCL); // read/write + don't replicate existing file 
    read(fd, (void*)cbuff, sizeof(cbuff) ); // read from buffer to fd 


    if ( close(sock_fd) < 0 )
        printf("error: not closed\n");

    return 0;
}

#include <sys/socket.h>   //connect,send,recv,setsockopt等
#include <sys/types.h>      

#include <netinet/in.h>     // sockaddr_in, "man 7 ip" ,htons
#include <poll.h>             //poll,pollfd
#include <arpa/inet.h>   //inet_addr,inet_aton
#include <unistd.h>        //read,write
#include <netdb.h>         //gethostbyname

#include <error.h>         //perror
#include <stdio.h>
#include <errno.h>         //errno

#include <string.h>          // memset
#include<stdlib.h>

#define EHCO_PORT 8087

int main(int argc, char **argv)
{
int socketfd;
char buf[100] = {};
socketfd = socket(AF_INET, SOCK_STREAM, 0);
if(socketfd == -1)
{
printf("errno=%d ", errno);
exit(1);
}
else
{
printf("socket create successfully ");
}
struct sockaddr_in sa;
bzero(&sa, sizeof(sa));
sa.sin_family = AF_INET;
sa.sin_port = htons(EHCO_PORT);
inet_aton("127.0.0.1",&sa.sin_addr);
bzero(&(sa.sin_zero), 8);
if(connect(socketfd, (struct sockaddr *)&sa, sizeof(sa))!= 0)
{
printf("connect failed ");
printf("errno=%d ", errno);
exit(1);
}
else
{
printf("connect successfully ");
}
while(1)
{
send(socketfd, "123",5, 0);
recv(socketfd, buf, sizeof(buf), 0);
printf("服务说:%s\n", buf);
sleep(1);
}
//5.关闭
close(socketfd);
return 0;
}


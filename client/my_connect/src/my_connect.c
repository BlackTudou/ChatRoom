#include "../../include/myhead.h"

int my_connect(const char *ip, int port)
{
    int sfd;
    
    struct sockaddr_in serveraddr;

    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
	exit(1);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);

    if(connect(sfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect error");
	close(sfd);
	exit(1);
    }

    return sfd;
}

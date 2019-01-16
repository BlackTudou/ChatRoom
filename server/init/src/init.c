#include "../../include/myhead.h"

int init(const char * ip, int port)
{
    int sfd;
    int opt = 1;
    struct sockaddr_in serveraddr;
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr,"socket error:%s\n",strerror(errno));
	exit(1);
    }

    printf("socket success!\n");

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);

    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if((bind(sfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr))) == -1)
    {
        perror("bind error");
	close(sfd);
	exit(1);
    }
    printf("bind success!\n");

    if(listen(sfd, 10) == -1)
    {
        perror("listen error");
	close(sfd);
	exit(1);
    }
    printf("listen success!\n");

    return sfd;
}

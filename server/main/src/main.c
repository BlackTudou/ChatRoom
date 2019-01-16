#include "../../include/myhead.h"

//Link head = NULL;

int main(int argc, char **argv)
{
    int sfd;
    int cfd;

    pthread_t id;
    
    //Msg *msg = (Msg *)malloc(sizeof(Msg));
    
    if(argc != 2)
    {
        printf("Please input IP!\n");
	exit(1);
    }

    sfd = init(argv[1], PORT);
#if 0
    if((head = (Link)malloc(sizeof(Online))) == NULL)
    {
        perror("head malloc error");
	exit(1);
    }
#endif
    while(1)
    {
        cfd = my_accept(sfd);
	    pthread_create(&id, NULL, pthread_read, (void *)&cfd);
    }
    
    close(sfd);
    return 0;
}

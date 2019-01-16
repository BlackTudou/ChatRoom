#ifndef __MYHEAD__H
#define __MYHEAD__H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sqlite3.h>
#include <pthread.h>
#include <time.h>
#include <termios.h>

#define MAX_SIZE 1024
#define PORT 5000
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

enum action{REG, LOGIN, LIST, CHAT, STOALL, OFFLINE, CHANGEPWD, CHANGENAME, VIEWMSG, OFFLINEMSG, OUT,BAN,RMBAN,NAME,ID};
enum result{SUCCESS = 1, FAILURE, PWERR, NOUSR, EMPTY,NOTONLINE,ONLINE,SINGAL,ALL};

struct message
{
    int action;

    int flag;
    char name[MAX_SIZE];
    long id;
    char password[MAX_SIZE];
    char toname[MAX_SIZE];
    char msg[MAX_SIZE];
};

struct online
{
    int cfd;
    int flag;

    char name[MAX_SIZE];
};

typedef struct message Msg;
typedef struct online Online;

extern int interface_chat();
extern int interface_login();
extern int my_connect(const char *ip, int port);
extern int init(const char *ip, int port);
extern int reg(int sfd, Msg *msg);
extern int login(int sfd, Msg *msg, char *str);
extern void *pthread_read(void *arg);
extern int list(Msg *msg);
extern int set_disp_mode(int cfd, int option);

#endif

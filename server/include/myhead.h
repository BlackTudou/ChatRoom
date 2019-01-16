#ifndef _MYHEAD_H_
#define _MYHEAD_H_

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

#define MAX_SIZE 1024
#define PORT 5000

enum action{REG, LOGIN, LIST, CHAT,STOALL, OFFLINE, CHANGEPWD, CHANGENAME, VIEWMSG, OFFLINEMSG, OUT, BAN, RMBAN,NAME,ID};
enum result{SUCCESS = 1, FAILURE, PWERR, NOUSR, EMPTY, NOTLINE, ONLINE,SINGAL,ALL};

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
    struct online *next;
};

typedef struct message Msg;
typedef struct online Online;
typedef struct online * Link;

extern int ban(int cfd, Msg *msg);
extern int chat(int cfd, Msg *msg);
extern int insertmsg(Msg *msg);
extern int init(const char *ip, int port);
extern int my_accept(int sfd);
extern void *pthread_read(void *arg);
extern int reg(int cfd, Msg *msg);
extern int login(int cfd, Msg *msg);
extern int online(int cfd, Msg *msg);
extern int list(int cfd, Msg *msg);
extern int viewmsg(int cfd, Msg *msg);
extern int viewoffmsg(int cfd, Msg *msg);
extern int changename(int cfd, Msg *msg);
extern int changepwd(int cfd, Msg *msg);
extern int insertmsgall(Msg *msg);
extern int insertoffmsg(int cfd, Msg *msg);
extern int offline(int cfd, Msg *msg);
extern int rmban(int cfd, Msg *msg);
extern int stoall(int cfd, Msg *msg);
extern int out(int cfd,Msg *msg);

#endif

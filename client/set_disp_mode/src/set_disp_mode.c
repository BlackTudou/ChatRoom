#include"../../include/myhead.h"

int set_disp_mode(int fd, int option) //取消登录密码回显
{
    int err;
    struct termios term;
    if(tcgetattr(fd,&term) == -1)
    {
        perror("cannot get the attribution of the terminal");
        return 1;
    }
    if(option)
    {
        term.c_lflag |= ECHOFLAGS;
    }
    else
    {
        term.c_lflag &= ~ECHOFLAGS;
    }
    err = tcsetattr(fd,TCSAFLUSH,&term);
    if(err == -1 && err == EINTR)
    {
        perror("cannot set the attribution of the terminal");
        return 1;
    }
    return 0;
}

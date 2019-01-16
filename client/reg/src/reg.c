#include "../../include/myhead.h"

int reg(int sfd, Msg *msg)
{
    bzero(msg, sizeof(Msg));
    
    printf("\t\t请输入用户名:\n");
    scanf("%s", msg->name);
    printf("\t\t请输入密码  :\n");
	set_disp_mode(STDIN_FILENO,0);
	getchar();
    scanf("%s",msg->password);
	set_disp_mode(STDIN_FILENO,1);
    msg->action = REG;

    write(sfd, msg, sizeof(Msg));

    bzero(msg,sizeof(Msg));
    read(sfd, msg, sizeof(Msg));
    
    if(msg->action == FAILURE)
    {
        printf("注册失败,该用户名已存在!\n");
	return FAILURE;
    }

    else if(msg->action == SUCCESS)
    {
        printf("\t\t注册成功!\n");
	    printf("\t\t您的ID为:%ld,请牢记!\n",msg->id);
    }
    return SUCCESS;
}

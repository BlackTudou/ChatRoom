#include "../../include/myhead.h"

int interface_chat()
{
    system("clear");
	printf("\t\t+=====================================================+\n");
    printf("\t\t|                                                     |\n");
    printf("\t\t|                   欢迎来到雨落聊天室                |\n");
    printf("\t\t|                                                     |\n");
    printf("\t\t|     *查看在线用户(online)   *进行聊天(chatone)      |\n");
    printf("\t\t|     *群发消息 (chatall)     *退出登录(quit)         |\n");
    printf("\t\t|     *修改密码(changepwd)    *修改昵称(changename)   |\n");
    printf("\t\t|     *查看帮助(help)         *查看聊天记录(viewmsg)  |\n");
    printf("\t\t|     *发送离线消息(offmsg)   *退出聊天室(exit)       |\n");
    printf("\t\t|                                                     |\n");
    printf("\t\t+=====================================================+\n");

    return SUCCESS;
}

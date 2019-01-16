#include "../../include/myhead.h"

int login(int sfd, Msg * msg, char *str)
{
    char menu[MAX_SIZE];
    
	printf("\t\t现提供如下登录方式:\n");
    printf("\t\t1.用户名登录(name)\n");
    printf("\t\t2.账号登录(id)\n");
    printf("\t\t请选择登录方式(name/id):");
    
	scanf("%s",menu);
        
	if(strcmp(menu,"name") == 0)
	{
    	bzero(msg, sizeof(Msg));
	    printf("\t\t请输入用户名:");
	    scanf("%s",str);
	    strcpy(msg->name,str);
	    printf("\t\t请输入密码:");
		set_disp_mode(STDIN_FILENO,0);
		getchar();
	    scanf("%s",msg->password);
		set_disp_mode(STDIN_FILENO,1);
	
	    msg->flag = NAME;
	    msg->action = LOGIN;

	    write(sfd, msg, sizeof(Msg));

	    bzero(msg, sizeof(Msg));
	    read(sfd, msg, sizeof(Msg));
	    switch(msg->action)
	    {
	        case SUCCESS:
			{
		    	printf("\n\n");
				printf("\t\t登录成功!\n");
				printf("\t\tloading......\n");
				sleep(2);
		    	break;
			}
			case NOUSR:
			{
		    	printf("\n\n");
				printf("\t\t没有该用户,请先注册!\n");
		    	return NOUSR;
		    	break;
			}
			case PWERR:
			{
		    	printf("\n\n");
				printf("\t\t密码错误,请重新登录!\n");
		    	return PWERR;
		    	break;
			}
	    }
	}
	else if(strcmp(menu,"id") == 0)
	{
    	bzero(msg, sizeof(Msg));
	   	printf("\t\t请输入账号:");
	    scanf("%ld",&msg->id);
	    
	   	printf("\t\t请输入密码:");
		set_disp_mode(STDIN_FILENO,0);
		getchar();
	    scanf("%s",msg->password);
		set_disp_mode(STDIN_FILENO,1);

	    msg->action = LOGIN;
	    msg->flag = ID;

	    write(sfd, msg, sizeof(Msg));

	    bzero(msg, sizeof(Msg));
	    read(sfd, msg, sizeof(Msg));
	    switch(msg->action)
	    {
	    	case SUCCESS:
			{
		    	strcpy(str,msg->name);
		    	printf("\n\n");
				printf("\t\t登录成功!\n");
				printf("\t\tloading......\n");
				sleep(2);
		    	break;
			}
			case NOUSR:
			{
		    	printf("\n\n");
				printf("\t\t没有该用户,请先注册!\n");
		    	return NOUSR;
		    	break;
			}
			case PWERR:
			{
		    	printf("\n\n");
				printf("\t\t密码错误,请重新登录!\n");
		    	return PWERR;
		    	break;
			}
	    }
	}
    else
	{
    	printf("\n");
		printf("\t\t您输入的格式不正确!\n");
		return FAILURE;
	}
    
	return SUCCESS;
}

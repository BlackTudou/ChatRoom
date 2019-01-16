#include "../../include/myhead.h"

void * pthread_read(void *arg)
{
    int sfd = *((int *)arg);
    int n_read;
	time_t t;
	time(&t);

    Msg *msg = (Msg*)malloc(sizeof(Msg));
    
    while(1)
    {
        bzero(msg, sizeof(Msg));
		n_read = read(sfd, msg, sizeof(Msg));
	
		if(n_read == 0)
		{
	    	printf("server close!\n");
	    	break;
		}
		switch(msg->action)
		{
	    	case LIST:
	    	{
				if(msg->flag == EMPTY)
				{
		    		printf("\t\t暂时没有用户上线!\n");
				}
				else if(msg->flag == SUCCESS)
				{
		    		list(msg);
				}
				break;
	    	}
	    	case CHAT:
	    	{
	        	if(msg->flag == ONLINE)
				{
		    		printf("%s",ctime(&t));
					printf("%s悄悄对我说:%s\n",msg->name, msg->msg);
				}
				else if(msg->flag == NOTONLINE)
				{
		    		printf("%s",ctime(&t));
		    		printf("%s不在线,您可以选择offmsg功能来发送消息\n",msg->toname);
				}
				else if(msg->flag == BAN)
				{
				    printf("您已被禁言,无法享有聊天功能,请联系管理员解禁!\n");
				}
				else if(msg->flag == RMBAN)
				{
				    printf("对方已经被禁言,可能无法及时回复您,您可以帮他联系管理员将他解禁!\n");
				}
				break;
	    	}
	    	case STOALL:
            {
		        if(msg->flag == ONLINE)
				{
					printf("%s",ctime(&t));
	        		printf("%s 对大家说:%s\n",msg->name, msg->msg);
				}
				else if(msg->flag == BAN)
				{
				    printf("您已经被管理员禁言,暂时不享有这项功能,请自行联系管理员解禁!\n");
				}
				else if(msg->flag == RMBAN)
				{
				    printf("%s 被管理员禁言,收到消息后可能无法回复您,您可以帮其联系管理员将其解禁!\n",msg->toname);
				}
				break;
	    	}
			case OFFLINE:
			{
				printf("%s",ctime(&t));
			    printf("%s 下线成功!\n",msg->name);
				break;
			}
			case CHANGEPWD:
			{
			    if(msg->flag == SUCCESS)
				{
		    	   printf("%s",ctime(&t));
				   printf("密码修改成功,请记住新密码!\n");
				   printf("密码已修改,请重新登录!\n");
				}
				else if(msg->flag == FAILURE)
				{
		    	    printf("%s",ctime(&t));
				    printf("密码修改失败,请检查操作!\n");
				}
				break;
			}
			case CHANGENAME:
			{
			    if(msg->flag == SUCCESS)
				{
				    printf("昵称修改成功!\n");
					printf("用户名已修改,请重新登录!\n");
				}
				else if(msg->flag == FAILURE)
				{
				    printf("该用户名已存在!请再想个昵称!\n");
				}
			    break;
			}
			case VIEWMSG:
			{
			    //printf("**********聊天记录**********\n");
				if(msg->flag == SINGAL)
				{
				    printf("%s 对 %s 说:%s\n",msg->name,msg->toname,msg->msg);
				}
				//printf("群聊消息:\n");
				else if(msg->flag == ALL)
				{
					printf("%s 对大家说:%s\n",msg->name, msg->msg);
				}
			    break;
			}
			case OFFLINEMSG:
			{
			    printf("offlinemsg:\n");
				if(msg->flag==SUCCESS)
				{
		    	    printf("%s",ctime(&t));
				    printf("在您离线时,%s 悄悄对您说:%s\n",msg->toname,msg->msg);
				}
				else
				{
				    ;
				}
				break;
			}
			case OUT:
			{
		    	if(msg->flag == SUCCESS)
				{
					printf("您已被管理员踢出聊天室,请重新登录!\n");
				}
				else if(msg->flag == FAILURE)
				{
				    printf("对方并没有在线哦,等他上线了再踢他吧!\n");
				}
				break;
			}
			case BAN:
			{
			    if(msg->flag == SUCCESS)
				{
					printf("您已被禁言,请联系管理员解禁!\n");
				}
				else if(msg->flag == OFFLINE)
				{
				    printf("对方不在线,等到对方上线后再禁言他/她吧!\n");
				}
				break;
			}
			case RMBAN:
			{
			    if(msg->flag == SUCCESS)
				{
					printf("您已经被管理员解禁,又可以愉快地聊天了!\n");
				}
				else if(msg->flag == OFFLINE)
				{
					printf("对方不在线,等到对方上线后再解禁他/她吧!\n");
				}
			    break;
			}
		}
    }

	return NULL;
}
	    

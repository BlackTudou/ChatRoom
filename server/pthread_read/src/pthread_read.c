#include "../../include/myhead.h"

void * pthread_read(void *arg)
{
    int cfd = *((int *)arg);
    int n_read;
    Msg *msg;

    if((msg = (Msg*)malloc(sizeof(Msg))) == NULL)
    {
        perror("msg malloc error");
	    exit(1);
    }

    while(1)
    {
        bzero(msg, sizeof(Msg));
	    n_read = read(cfd, msg, sizeof(Msg));
	
		if(n_read == 0)
		{
	    	printf("client close!\n");
	    	break;
		}

		switch(msg->action)
		{
	    	case REG:
	    	{
	        	reg(cfd, msg);
				break;
	    	}
	    	case LOGIN:
	    	{
	        	if(login(cfd, msg) == SUCCESS)
				{
		    		if(online(cfd, msg) == SUCCESS)
		    		{
		        		viewoffmsg(cfd, msg);
						printf("online successfully!\n");
		    		}
				}
		    	break;
	    	}
	    	case LIST:
	    	{
	        	printf("In list\n");
		    	list(cfd, msg);
		    	break;
	    	}
	    	case CHAT:
	    	{
	        	chat(cfd, msg);
		    	break;
	    	}
	    	case STOALL:
	    	{
	        	stoall(cfd, msg);
				break;
	    	}
			case OFFLINE:
			{
		    	offline(cfd, msg);
				break;
			}
			case CHANGEPWD:
			{
		    	changepwd(cfd, msg);
				break;
			}
			case CHANGENAME:
			{
		    	changename(cfd, msg);
				break;
			}
			case VIEWMSG:
			{
			    viewmsg(cfd, msg);
				break;
			}
			case OFFLINEMSG:
			{
			    insertoffmsg(cfd, msg);
				break;
			}
			case OUT:
			{
			    out(cfd, msg);
				break;
			}
			case BAN:
			{
			    ban(cfd, msg);
				break;
			}
			case RMBAN:
			{
			    rmban(cfd, msg);
				break;
			}
	    	default:
	    	{
	        	break;
	    	}
		}
    }

	return NULL;
}
	    

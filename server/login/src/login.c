#include "../../include/myhead.h"

int login(int cfd, Msg *msg)
{
    int i;
    int count = 0;
    int ret = 0;
    int row;
    int column;
    
    char *errmsg;
    char **result;

    sqlite3 *db;
    
    ret = sqlite3_open("resource/usr.db",&db);

    if(ret != SQLITE_OK)
    {
        printf("sqlite3 open error!\n");
	exit(1);
    }
    
    if(SQLITE_OK != sqlite3_get_table(db,"select * from usr",&result,&row,&column,&errmsg))
    {
        printf("select from usr error:%s\n",errmsg);
	    exit(1);
    }

    if(msg->flag == NAME)
    {
        for(i = 1; i <= row; i++)
        {
            if(strcmp(result[column * i], msg -> name) == 0)
	    	{
                if(strcmp(result[column * i + 2], msg->password) == 0)
				{
		    		msg->action = SUCCESS;
		    		write(cfd, msg, sizeof(Msg));
				}
				else
				{
		    		msg->action = PWERR;
		    		write(cfd, msg, sizeof(Msg));
		    		return PWERR;
				}
	    	}
	    	else
	    	{
	        	count++;
	    	}
        }
		if(count == row)
		{
	    	msg->action = NOUSR;
	    	write(cfd, msg, sizeof(Msg));
	    	return NOUSR;
		}
    }	
    else if(msg->flag == ID)
    {
        for(i = 1; i <= row; i++)
        {
            //printf("id = %ld\n",atoi(result[column*i +1]));
	    	if(atoi(result[column * i + 1]) == msg -> id)
	    	{
                if(strcmp(result[column * i + 2], msg->password) == 0)
				{
		    		strcpy(msg->name,result[column*i]);
					msg->action = SUCCESS;
		    		write(cfd, msg, sizeof(Msg));
				}
				else
				{
		    		msg->action = PWERR;
		    		write(cfd, msg, sizeof(Msg));
		    		return PWERR;
				}
	    	}
	    	else
	    	{
	        	count++;
	    	}
        }
		if(count == row)
		{
	    	msg->action = NOUSR;
	    	write(cfd, msg, sizeof(Msg));
	    	return NOUSR;
		}
    }	
    
    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

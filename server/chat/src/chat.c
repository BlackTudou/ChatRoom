#include "../../include/myhead.h"

int chat(int cfd, Msg *msg)
{
    int i;
    int to_fd;
    int ret = 0;
    int count = 0;
    int row;
    int column;
    
    char *errmsg;
    char **result;
	char sql[MAX_SIZE];
	memset(sql, 0, sizeof(sql));
    
    sqlite3 *db;
    
    ret = sqlite3_open("resource/online.db",&db);

    if(ret != SQLITE_OK)
    {
        printf("sqlite3 open online.db error!\n");
	    exit(1);
    }
	sprintf(sql, "select flag from online where name='%s';",msg->name);
	if(sqlite3_get_table(db,sql,&result,&row,&column,&errmsg) != SQLITE_OK)
	{
	     printf("select flag error:%s\n",errmsg);
		 exit(1);
	}

	if((strcmp(result[column],"0")) == 0)
	{
	    msg->flag = BAN;
		msg->action = CHAT;
		write(cfd, msg, sizeof(Msg));
		return FAILURE;
	}
    
	if(SQLITE_OK != sqlite3_get_table(db,"select * from online",&result,&row,&column,&errmsg))
    {
        printf("select from online error:%s\n",errmsg);
	    exit(1);
    }
    for(i = 1; i <= row; i++)
    {
        if(strcmp(msg->toname,result[column * i]) == 0)
		{
	    	printf("flag=%d\n",atoi(result[column*i+2]));
	        to_fd = atoi(result[column * i + 1]);
			//if(atoi(result[column * i + 2]) == 1)
	    	//{
    	    	insertmsg(msg);
		    	msg->flag = ONLINE;
				msg->action = CHAT;
				write(to_fd, msg, sizeof(Msg));
	    	//}
			if(atoi(result[column *i + 2]) == 0)
			{
			    msg->flag = RMBAN;
				msg->action = CHAT;
				write(cfd, msg, sizeof(Msg));
			}
		}
	    else
	    {
	        count++;
	    }
    }
    if(count == row)
    {
        msg->flag = NOTLINE;
		msg->action = CHAT;
		write(cfd, msg, sizeof(Msg));
    }
    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

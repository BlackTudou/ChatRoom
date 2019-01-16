#include "../../include/myhead.h"

int stoall(int cfd, Msg *msg)
{
    int i;
    int to_fd;
    int ret = 0;
    int row;
    int column;
    
    char *errmsg;
    char **result;
	char sql[MAX_SIZE];
    
    sqlite3 *db;
    
    ret = sqlite3_open("resource/online.db",&db);

    if(ret != SQLITE_OK)
    {
        printf("sqlite3 open online.db error!\n");
		exit(1);
    }

    sprintf(sql,"select flag from online where name='%s';",msg->name);
	if(SQLITE_OK != (sqlite3_get_table(db,sql,&result,&row,&column,&errmsg)))
	{
	    printf("select flag error:%s\n",errmsg);
		exit(1);
	}

	if((atoi(result[1])) == 0)
	{
	    msg->action = STOALL;
		msg->flag = BAN;
		write(cfd, msg,sizeof(Msg));
        
		sqlite3_free_table(result);

		return FAILURE;
	}
    
    if(SQLITE_OK != sqlite3_get_table(db,"select * from online",&result,&row,&column,&errmsg))
    {
        printf("select from online error:%s\n",errmsg);
		exit(1);
    }
	
	insertmsgall(msg);

    for(i = 1; i <= row; i++)
    {
        //if(atoi(result[column * i + 2]) == 1)
	    //{
			to_fd = atoi(result[column * i + 1]);
        	msg->flag = ONLINE;
	    	msg->action = STOALL;
	    	write(to_fd, msg, sizeof(Msg));
	    //}
		if(atoi(result[column *i +2]) == 0)
		{
		    strcpy(msg->toname,result[column*i]);
			msg->action = STOALL;
			msg->flag = RMBAN;
			write(cfd, msg, sizeof(Msg));
		}
    }

    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

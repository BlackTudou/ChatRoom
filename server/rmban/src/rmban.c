#include "../../include/myhead.h"

int rmban(int cfd, Msg *msg)
{
    int to_fd;
    int ret = 0;
    int column;
	int row;
    
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
    
    sprintf(sql,"select *from online where name='%s';",msg->name);
    if(SQLITE_OK != sqlite3_get_table(db,sql,&result,&row,&column,&errmsg))
    {
        printf("select from online error:%s\n",errmsg);
	    exit(1);
    }
    
	if(row == 0)
	{
	    msg->action = RMBAN;
		msg->flag = OFFLINE;
		write(cfd, msg, sizeof(Msg));
		return FAILURE;
	}

    memset(sql, 0, sizeof(sql));
	sprintf(sql, "update online set flag=%d where name='%s';",1,msg->name);
	if(sqlite3_exec(db, sql, NULL,NULL,&errmsg) != SQLITE_OK)
	{
	    printf("update flag error:%s\n",errmsg);
		exit(1);
	}
	to_fd = atoi(result[column+1]);
    
	msg->action = RMBAN;
	msg->flag = SUCCESS;
	write(to_fd, msg, sizeof(Msg));

    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

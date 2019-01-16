#include "../../include/myhead.h"

int ban(int cfd, Msg *msg)
{
	int to_fd;
    int ret = 0;
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
    #if 1
    sprintf(sql,"select *from online where name='%s';",msg->name);
    if(SQLITE_OK != sqlite3_get_table(db,sql,&result,&row,&column,&errmsg))
    {
        printf("select from online error:%s\n",errmsg);
	    exit(1);
    }
    #endif
    //strcpy(result[column + 2],"0");

	if(row == 0)
	{
	    msg->action = BAN;
		msg->flag = OFFLINE;

		write(cfd, msg, sizeof(Msg));
		return FAILURE;
	}
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "update online set flag=%d where name='%s';",0,msg->name);
	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("update online error:%s\n",errmsg);
		exit(1);
	}
	//printf("ban:%s\n",result[column + 2]);
	
	to_fd = atoi(result[column + 1]);
	printf("to_fd = %d\n",to_fd);
    
	msg->action = BAN;
	msg->flag = SUCCESS;
	write(to_fd, msg, sizeof(Msg));

    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

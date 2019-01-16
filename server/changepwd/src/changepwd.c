#include "../../include/myhead.h"

int changepwd(int cfd, Msg *msg)
{
    int ret = 0;
    int row;
    int column;
    
    char *errmsg;
    char **result;
    char sql[MAX_SIZE];

	memset(sql, 0, sizeof(sql));

    sqlite3 *db;
    
    ret = sqlite3_open("resource/usr.db",&db);

    if(ret != SQLITE_OK)
    {
        printf("sqlite3 open resource/usr.db error!\n");
		exit(1);
    }
    
	sprintf(sql, "select name from usr where name = '%s'",msg->name);
    if(SQLITE_OK != sqlite3_get_table(db,sql,&result,&row,&column,&errmsg))
    {
        printf("select from usr.db error:%s\n",errmsg);
	    exit(1);
    }
    
    if(row != 1)
	{
	    msg->action = CHANGEPWD;
		msg->flag = FAILURE;

		write(cfd, msg, sizeof(Msg));
		return FAILURE;
	}
    else
	{
	    sprintf(sql, "update usr set password = '%s' where name = '%s';", msg->password, msg->name);
		if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
		{
		    printf("update password error:%s\n",errmsg);
			exit(1);
		}
		
		msg->action = CHANGEPWD;
	    msg->flag = SUCCESS;
	    write(cfd, msg, sizeof(Msg));
	}	

    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

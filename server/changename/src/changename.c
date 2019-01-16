#include "../../include/myhead.h"

int changename(int cfd, Msg *msg)
{
    int row;
    int column;
    
	char sql[MAX_SIZE];
    char *errmsg;
    char **result;

    sqlite3 *db;
    
    if((sqlite3_open("resource/usr.db",&db)) != SQLITE_OK)
	{
	    printf("open usr.db error!\n");
		exit(1);
	}

    sprintf(sql, "select name from usr where name = '%s'",msg->name);
    if(SQLITE_OK != sqlite3_get_table(db, sql, &result, &row, &column, &errmsg))
    {
        printf("select from usr error:%s\n",errmsg);
	    exit(1);
    }
    
    if(row != 1)
	{
	    msg->action = CHANGENAME;
		msg->flag = FAILURE;

		write(cfd, msg, sizeof(Msg));

		return FAILURE;
	}
	else
	{
	    sprintf(sql, "update usr set name = '%s' where name = '%s';",msg->toname, msg->name);
		if(SQLITE_OK != (sqlite3_exec(db, sql, NULL, NULL, &errmsg)))
		{
		    printf("update usr error:%s\n",errmsg);
			msg->action = CHANGENAME;
			msg->flag = FAILURE;

			write(cfd, msg, sizeof(Msg));

			return FAILURE;
		}
		else
		{
			msg->action = CHANGENAME;
			msg->flag = SUCCESS;

			write(cfd, msg, sizeof(Msg));
		}
	}
    
    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

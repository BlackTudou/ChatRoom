#include "../../include/myhead.h"

int insertmsgall(Msg *msg)
{
    sqlite3 *db;

	char *errmsg;
	char sql[MAX_SIZE];

	memset(sql, 0, sizeof(sql));

	if((sqlite3_open("resource/chatmsg.db",&db)) != SQLITE_OK)
	{
	    printf("open chatmsg.db error\n");
		exit(1);
	}

    if((sqlite3_exec(db, "create table if not exists msgall(name text, toname text, msg text);", NULL, NULL, &errmsg)) 
	   != SQLITE_OK)
	{
	    printf("create table all error:%s\n",errmsg);
		exit(1);
	}

	sprintf(sql, "insert into msgall(name, toname, msg) values('%s','%s','%s')",msg->name, msg->toname, msg->msg);
	if((sqlite3_exec(db, sql, NULL, NULL, &errmsg)) != SQLITE_OK)
	{
	    printf("insert table all error:%s\n",errmsg);
		exit(1);
	}

	return SUCCESS;
}

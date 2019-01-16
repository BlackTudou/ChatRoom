#include "../../include/myhead.h"

int insertmsg(Msg *msg)
{
    sqlite3 *db;
	char *errmsg;

	char sql[MAX_SIZE];
	memset(sql,0,sizeof(sql));

	if((sqlite3_open("resource/chatmsg.db",&db)) != SQLITE_OK)
	{
	    printf("open chatmsg.db error\n");
		exit(1);
	}

    sprintf(sql,"create table if not exists %s(name text, toname text, msg text)",msg->name);
	if((sqlite3_exec(db, sql,NULL,NULL,&errmsg)) != SQLITE_OK)
	{
	    printf("create table error:%s\n",errmsg);
		exit(1);
	}

    sprintf(sql,"create table if not exists %s(name text, toname text, msg text)",msg->toname);
	if((sqlite3_exec(db, sql,NULL,NULL,&errmsg)) != SQLITE_OK)
	{
	    printf("create table error:%s\n",errmsg);
		exit(1);
	}

	sprintf(sql,"insert into %s(name, toname ,msg) values('%s','%s','%s');",msg->name,msg->name,msg->toname,msg->msg);
	if((sqlite3_exec(db,sql,NULL,NULL,&errmsg)) != SQLITE_OK)
	{
	    printf("insert into error:%s\n",errmsg);
		exit(1);
	}

	sprintf(sql,"insert into %s(name, toname ,msg) values('%s','%s','%s');",msg->toname,msg->name,msg->toname,msg->msg);
	if((sqlite3_exec(db,sql,NULL,NULL,&errmsg)) != SQLITE_OK)
	{
	    printf("insert into error:%s\n",errmsg);
		exit(1);
	}
    
    sqlite3_close(db);
	return SUCCESS;
}

#include "../../include/myhead.h"

int insertoffmsg(int cfd, Msg *msg)
{
    sqlite3 *db;

	char sql[MAX_SIZE];
	char *errmsg;

	memset(sql,0,sizeof(sql));

	//if(sqlite3_open("resource/online.db",&db) != SQLITE_OK)
	//{
	  //  printf("open online.db error!\n");
		//exit(1);
	//}
	
    if((sqlite3_open("resource/chatmsg.db",&db)) != SQLITE_OK)
	{
	    printf("open chatmsg.db error\n");
		exit(1);
	}

	//sqlite3_exec(db,"drop table if exists offlinemsg;",NULL,NULL,&errmsg);

	if((sqlite3_exec(db,"create table if not exists offlinemsg(name text,toname text,msg text);",NULL,NULL,&errmsg)) != SQLITE_OK)
	{
	    printf("create table offlinemsg error:%s\n",errmsg);
		exit(1);
	}

	sprintf(sql,"insert into offlinemsg(name,toname,msg) values('%s','%s','%s');",msg->name,msg->toname,msg->msg);

	if((sqlite3_exec(db, sql, NULL, NULL,&errmsg)) != SQLITE_OK)
	{
	    printf("insert into offlinemsg error:%s\n",errmsg);
		exit(1);
	}
	insertmsg(msg);
	sqlite3_close(db);

	return SUCCESS;
}

#include "../../include/myhead.h"

int viewmsg(int cfd, Msg *msg)
{
    sqlite3 *db;

	int i;
	int row;
	int column;
	
	char *errmsg;
	char **result;
	char sql[MAX_SIZE];

	memset(sql, 0, sizeof(sql));

	if((sqlite3_open("resource/chatmsg.db",&db)) != SQLITE_OK)
	{
	    printf("open chatmsg.db error!\n");
		exit(1);
	}
    sprintf(sql,"create table if not exists %s(name text,toname text,msg text);",msg->name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
	    printf("create table %s error:%s\n",msg->name,errmsg);
		exit(1);
	}
	memset(sql,0,sizeof(sql));
	sprintf(sql, "select * from %s",msg->name);
	if((sqlite3_get_table(db, sql, &result, &row, &column, &errmsg)) != SQLITE_OK)
	{
	    printf("select from chatmsg error:%s\n",errmsg);
		exit(1);
	}
    
	for(i = 1; i <= row; i++)
	{
	    bzero(msg, sizeof(Msg));
		strcpy(msg->name,result[i*column]);
	    strcpy(msg->toname,result[i*column+1]);
	    strcpy(msg->msg,result[i*column+2]);
		msg->action = VIEWMSG;
		msg->flag = SINGAL;

		write(cfd, msg, sizeof(Msg));
	}
	
    memset(sql, 0, sizeof(sql));
	if(sqlite3_exec(db,"create table if not exists msgall(name text,toname text,msg text);",NULL,NULL,&errmsg) != SQLITE_OK)
	{
	    printf("create table msgall error:%s\n",errmsg);
		exit(1);
	}

    memset(sql, 0, sizeof(sql));
	if((sqlite3_get_table(db, "select * from msgall", &result, &row, &column, &errmsg)) != SQLITE_OK)
	{
	    printf("select from chatmsg error:%s\n",errmsg);
		exit(1);
    }
	for(i = 1; i <= row; i++)
	{
	    bzero(msg, sizeof(Msg));
		strcpy(msg->name,result[i*column]);
	    strcpy(msg->toname,result[i*column+1]);
	    strcpy(msg->msg,result[i*column+2]);
		msg->action = VIEWMSG;
		msg->flag = ALL;

		write(cfd, msg, sizeof(Msg));
	}

	return SUCCESS;
}

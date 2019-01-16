#include "../../include/myhead.h"

int offline(int cfd, Msg *msg)
{
    int ret = 0;
    
    char *errmsg;
    char sql[MAX_SIZE];

    sqlite3 *db;
    
    ret = sqlite3_open("resource/online.db",&db);

    if(ret != SQLITE_OK)
    {
        printf("sqlite3 open online.db error!\n");
	    exit(1);
    }
    
    if(SQLITE_OK != sqlite3_exec(db,"create table if not exists online(name text primary key, cfd integer, flag integer);",
    NULL,NULL,&errmsg))
    {
        printf("create table online error:%s\n",errmsg);
	    exit(1);
    }
    
    sprintf(sql,"delete from online where name = '%s';",msg->name);
    
    if(SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
    {
	    printf("delete from online error:%s\n",errmsg);
	    exit(1);
    }

    sqlite3_close(db);

	msg->action = OFFLINE;
	write(cfd, msg, sizeof(Msg));
    
    return SUCCESS;
}

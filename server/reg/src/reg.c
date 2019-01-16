#include "../../include/myhead.h"

int reg(int cfd, Msg *msg)
{
    int i;
    int ret = 0;
    int row;
    int column;
    unsigned long id;
    
    char *errmsg;
    char **result;
    char sql[MAX_SIZE];

    srand(time(NULL));
    id = (unsigned long)rand()%100000000 + 100000000;
    
    sqlite3 *db;
    
    ret = sqlite3_open("resource/usr.db",&db);

    if(ret != SQLITE_OK)
    {
        printf("sqlite3 open error!\n");
	exit(1);
    }
    
    if(SQLITE_OK != sqlite3_exec(db,"create table if not exists usr(name text primary key,id integer,password text);",
    NULL,NULL,&errmsg))
    {
        printf("create table usr error:%s\n",errmsg);
	exit(1);
    }
    
    if(SQLITE_OK != sqlite3_get_table(db,"select * from usr",&result,&row,&column,&errmsg))
    {
        printf("select from usr error:%s\n",errmsg);
	exit(1);
    }

    for(i = 1; i <= row; i++)
    {
        if(strcmp(result[column * i], msg -> name) == 0)
	{
	    msg->action = FAILURE;
	    write(cfd, msg, sizeof(Msg));
	    return FAILURE;
	}
    }	
	
    sprintf(sql,"insert into usr(name, id, password) values('%s',%ld,'%s');",msg->name,id,msg->password);
    
    if(SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
    {
	printf("insert into usr error:%s\n",errmsg);
	exit(1);
    }

    bzero(msg, sizeof(Msg));
    msg->action = SUCCESS;
    msg->id = id;
    write(cfd, msg, sizeof(Msg));

    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

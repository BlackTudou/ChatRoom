#include "../../include/myhead.h"

int viewoffmsg(int cfd, Msg *msg)
{
    sqlite3 *db1;
	sqlite3 *db2;
	int row1;
	int row2;
	int column1;
	int column2;
	int to_fd;
	int i;
	int count = 0;

	char sql[MAX_SIZE];
	char *errmsg;
	char **result1;
	char **result2;
    
    if(sqlite3_open("resource/online.db",&db1) != SQLITE_OK)
	{
	    printf("open online.db error!\n");
		exit(1);
	}
    if(sqlite3_open("resource/chatmsg.db",&db2) != SQLITE_OK)
	{
	    printf("open chatmsg.db error!\n");
		exit(1);
	}
    sprintf(sql,"select * from online where name = '%s';",msg->name);
	printf("msg->name = %s\n",msg->name);
	if((sqlite3_get_table(db1,sql,&result1,&row1,&column1,&errmsg)) != SQLITE_OK)
	{
	    printf("select from online error:%s\n",errmsg);
		exit(1);
	}

	if(sqlite3_exec(db2,"create table if not exists offlinemsg(name text, toname text, msg text);",NULL,NULL,&errmsg))
	{
	    printf("create table offlinemsg error:%s\n",errmsg);
		exit(1);
	}

	if((sqlite3_get_table(db2,"select *from offlinemsg",&result2,&row2,&column2,&errmsg)) != SQLITE_OK)
	{
	    printf("select from offlinemsg error:%s\n",errmsg);
		exit(1);
    }

	if(row1 == 1)
	{
		to_fd = atoi(result1[column1 + 1]);
	    for(i = 1; i <= row2; i++)
		{
		    if(strcmp(result2[column2*i+1], msg->name) == 0)
			{
			    strcpy(msg->msg,result2[column2*i+2]);
				strcpy(msg->toname, result2[column2*i]);
				msg->action = OFFLINEMSG;
				printf("2.viewoffmsg action = %d\n",msg->action);
				printf("3.viewoffmsg name = %s\n",msg->toname);
				msg->flag = SUCCESS;
				write(to_fd, msg, sizeof(Msg));
			}
			else
			{
			    count++;
			}
		}
		if(count == row2)
		{
			msg->action = OFFLINEMSG;
			msg->flag = FAILURE;
			write(to_fd, msg, sizeof(Msg));
		}
	}

	sqlite3_free_table(result1);
	sqlite3_free_table(result2);
	
	sqlite3_close(db1);
	sqlite3_close(db2);

	return SUCCESS;
}

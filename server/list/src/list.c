#include "../../include/myhead.h"

int list(int cfd, Msg *msg)
{
    int i;
    int ret = 0;
    int row;
    int column;
    
    char *errmsg;
    char **result;
    
    sqlite3 *db;
    
    ret = sqlite3_open("resource/online.db",&db);

    if(ret != SQLITE_OK)
    {
        printf("sqlite3 open online.db error!\n");
		exit(1);
    }
    
    if(SQLITE_OK != sqlite3_get_table(db,"select * from online",&result,&row,&column,&errmsg))
    {
        printf("select from online error:%s\n",errmsg);
		exit(1);
    }

    if(row == 0)
    {
        bzero(msg, sizeof(Msg));
		msg->action = LIST;
		msg->flag = EMPTY;

		write(cfd, msg, sizeof(Msg));

		return EMPTY;
    }
    printf("result\n");    
    for(i = 1; i <= row; i++)
    {
        //if(atoi(result[column * i + 2]) == 1)
	//{
	    bzero(msg, sizeof(Msg));
	    strcpy(msg->name, result[column * i]);
	    msg->action = LIST;
	    msg->flag = SUCCESS;
            
        printf("%s",result[column * i]);

	    write(cfd, msg, sizeof(Msg));
	//}
    }	
    sqlite3_free_table(result);
    sqlite3_close(db);
    
    return SUCCESS;
}

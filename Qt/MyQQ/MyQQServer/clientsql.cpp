#include "clientsql.h"
#include <cstdlib>
#include <cstdio>

ClientSQL::ClientSQL()
{
	
}

ClientSQL::~ClientSQL()
{
	
}

int ClientSQL::initMySQL(MYSQL* mysql)  
{  
    if(mysql == NULL)  
    {  
        printf("MYSQL is NULL !\n");  
        return -1;  
    }  
      
    if(mysql_init(mysql) == NULL)
	{
		printf("MYSQL init Error !\n");  
        return -1;  
	}
      
    return 0;  
}  
  
int ClientSQL::connectMySQL(MYSQL* mysql, const char* host, const char* userName, const char* password, const char* dbName)  
{  
    if(mysql_real_connect(mysql, host, userName, password, dbName, 0, 0, 0) == NULL)  
    {  
        printf("%s\n", mysql_error(mysql));  
        return EXIT_FAILURE;  
    }  
      
    return 0;  
}   
  
int ClientSQL::sendAndResponseMySQL(MYSQL* mysql, const char* sql)  
{  
	int ret = 0;
    if(mysql == NULL)  
    {  
        printf("MYSQL is NULL !\n");  
        return -1;  
    }  
      
    ret = mysql_query(mysql, sql);  
      
    if(ret != 0)  
    {  
        printf("%s\n", mysql_error(mysql));  //��ѯ������ 
        return -1;  
    }  
      
    MYSQL_RES *result = mysql_store_result(mysql);  
    if(result == NULL)//sql �����ȷ ���ǲ��ǻ�õ� �е���� �ͷ��� 0 
    {  
        printf("Query OK, %u rows affected\n", (unsigned int)mysql_affected_rows(mysql));  
        ret = 0;  
        
    }else{
    	
    	ret = 1;//�����н���ͷ���1 
	}  
      
    /*MYSQL_FIELD *field;  
    int cols = 0;  
    while((field = mysql_fetch_field(result)) != NULL)  //ȡ���ж����� 
    {  
            printf("%s\t", field->name);  
            cols++;  
    }  
    printf("\n");  
      
    MYSQL_ROW row;  
      
    while((row = mysql_fetch_row(result)) != NULL)  //ȡ����ÿһ�е����� 
    {  
        int i = 0;  
        for(; i < cols; i++)  
        {  
            printf("%s\t", row[i]);  
        }  
        printf("\n");  
    }  
      
    printf("Query OK, %u rows affected\n", (unsigned int)mysql_affected_rows(mysql));*/  
    mysql_free_result(result);  
    
    return ret;  
}  
  
int ClientSQL::closeMySQL(MYSQL* mysql)  
{  
    if(mysql == NULL)  
    {  
        printf("MYSQL is NULL !\n");  
        return -1;  
    }  
      
    mysql_close(mysql);  
    printf("Bye\n");  
    return 0;  
}  
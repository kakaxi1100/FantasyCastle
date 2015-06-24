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
    if(result == NULL)//sql �����ȷ ���ǲ��ǻ�õ� �е���� �ͷ��� -2 
    {  
        printf("Query OK, %u rows affected\n", (unsigned int)mysql_affected_rows(mysql));  
        ret = -2;  
        
    }else{	  
		//---------------��ӡ��ѯ���-------------------
	    MYSQL_FIELD *field;  
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
	     
		ret = (int)mysql_affected_rows(mysql);//�����н���ͷ���Ӱ������ 
		  
	    printf("Query OK, %d rows affected\n", ret); 
	    //----------------------------------------------
	   //------�ͷŽ��-------------------------------- 
   	    mysql_free_result(result);
   }
  
    return ret;  
}  
  
string ClientSQL::getMySQLResult(MYSQL* mysql, const char* sql)
{
	string ret = "";
    if(mysql == NULL)  
    {  
        printf("MYSQL is NULL !\n");  
        return ret;  
    }  
      
    int sqlRet = mysql_query(mysql, sql);  
      
    if(sqlRet != 0)  
    {  
        printf("%s\n", mysql_error(mysql));  //��ѯ������ 
        return ret;  
    }  
      
    MYSQL_RES *result = mysql_store_result(mysql);  
    if(result == NULL)//sql �����ȷ ���ǲ��ǻ�õ� �е���� �򷵻�һ���ս�� 
    {  
        printf("Query OK, %u rows affected\n", (unsigned int)mysql_affected_rows(mysql));  
       	return ret; 
        
    }else{	  
		//---------------��ӡ��ѯ���-------------------
	    MYSQL_FIELD *field;  
	    int cols = 0;  
	    vector<string> columns;
	    while((field = mysql_fetch_field(result)) != NULL)  //ȡ���ж����� 
	    {  
	            printf("%s\t", field->name);  
	            cols++;  
	            string s(field->name);
	            columns.push_back(s);
	    }    
	    
	    printf("\n");   
	    
	    MYSQL_ROW row;  
	    
	    char *rowcontent;
	    char NULLStr[10] = "NULL";
	    while((row = mysql_fetch_row(result)) != NULL)  //ȡ����ÿһ�е����� 
	    {  
	        int i = 0;
			ret += "{";  
	        for(; i < cols; i++)  
	        {  
	        	rowcontent = row[i];
	        	if(rowcontent == NULL)
	        	{
	        		rowcontent = NULLStr;
				}
	            printf("%s\t", rowcontent);
				if(i < cols -1)
				{  
	            	ret += columns[i]+":" + rowcontent + ",";
	        	}
				else
				{
	        		ret += columns[i]+":" + rowcontent;
				}
	        }  
	        printf("\n");  
	        ret += "}";  
	    }  
		
	    printf("Query OK, %d rows affected\n", (unsigned int)mysql_affected_rows(mysql)); 
	    //----------------------------------------------
	   //------�ͷŽ��-------------------------------- 
   	    mysql_free_result(result);
   }
  
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

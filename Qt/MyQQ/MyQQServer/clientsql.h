#ifndef CLIENTSQL_H
#define CLIENTSQL_H

#include <mysql/mysql.h>  
#include <unistd.h>  
#include <errno.h>  
#include <termios.h>  
#include <string.h>  

class ClientSQL
{

public:
	ClientSQL();
	~ClientSQL();	

	//初始化 mysql 对象   
	int initMySQL(MYSQL* mysql);  
  
	//链接 mysql server   
	int connectMySQL(MYSQL* mysql, const char* host, const char* userName, const char* password, const char* dbName);   
	  
	//生成sql语句  
	int sendAndResponseMySQL(MYSQL* mysql, const char* sql);  
  
	//关闭数据库链接  
	int closeMySQL(MYSQL* mysql); 
	
private:
};

#endif

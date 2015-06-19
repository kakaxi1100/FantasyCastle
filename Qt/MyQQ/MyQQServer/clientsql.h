#ifndef CLIENTSQL_H
#define CLIENTSQL_H

#include <mysql/mysql.h>  
#include <unistd.h>  
#include <errno.h>  
#include <termios.h>  
#include <string.h>  
#include <vector>
#include <iostream>
using namespace std;
class ClientSQL
{

public:
	ClientSQL();
	~ClientSQL();	

	//��ʼ�� mysql ����   
	int initMySQL(MYSQL* mysql);  
  
	//���� mysql server   
	int connectMySQL(MYSQL* mysql, const char* host, const char* userName, const char* password, const char* dbName);   
	  
	//����sql���  
	int sendAndResponseMySQL(MYSQL* mysql, const char* sql);  
  
	//�ر����ݿ�����  
	int closeMySQL(MYSQL* mysql); 
	
	//ȡ��sql����ֵ����jason��ʽ���� 
	string getMySQLResult(MYSQL* mysql, const char* sql); 
private:
};

#endif

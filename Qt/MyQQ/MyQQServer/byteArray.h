#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <cstdlib>
#include <string.h>
#include <iostream>

class ByteArray
{
public:
	
	ByteArray();
	~ByteArray();
	
	char buf[1024];	//�������� , ���Խ������óɿɱ�� ���Ǹ���������鵽�µ����飬���Ǻ��鷳�����á� 
	
	void setBufLen(unsigned int value);	
	unsigned int getBufLen();
		
	void setBytesAvailable(unsigned int value);
	unsigned int getBytesAvailable();
	
	unsigned int plusPosition(unsigned int value);
	unsigned int minusPosition(unsigned int value);
	unsigned int getPosition();
	
	void clear();//��������
	
	short readShort();//��ȡ�����ŵ�32λ����
	unsigned short readUnsignedShort();//��ȡ�޷���32λ���� 
	
	int readInt();//��ȡ�����ŵ�32λ����
	unsigned int readUnsignedInt();//��ȡ�޷���32λ���� 
	
	char* readUTF();//��ȡһ���ַ��� 
	char* readUTFBytes(int len); //��ȡһ��ָ�����ȵ��ַ��� 
	
private:
	unsigned int bytesAvailable;//��Ч���ݳ��� 
	unsigned int position;//�α�ĵ�ǰλ�� 
	unsigned int len;//�õ������ݳ��� 
};

#endif

#include "byteArray.h"
#include <cstdlib>
#include <string.h>
#include <iostream>

using namespace std;

ByteArray::ByteArray()
{
	clear();
}

ByteArray::~ByteArray()
{
	
}
	
void ByteArray::setBytesAvailable(unsigned int value)
{
	bytesAvailable = value;
}

unsigned int ByteArray::getBytesAvailable()
{
	return bytesAvailable - getPosition();
}

unsigned int ByteArray::plusPosition(unsigned int value)
{
	if((position + value) > getBytesAvailable())
	{
		cout<<"position out of range !!" << endl;
		return -1;
	}
	
	position +=  value;
	
	return getPosition();
}

unsigned int ByteArray::minusPosition(unsigned int value)
{
	if(position  < value)
	{
		cout<<"position out of range !!" << endl;
		return -1;
	}
	
	position -=  value;
	
	return getPosition();
}

unsigned int ByteArray::getPosition()
{
	return position;
}	
	
	
void ByteArray::clear()
{
	bytesAvailable = 0;
	position = 0;
	memset(buf, 0, sizeof(buf));
}

int ByteArray::readInt()
{
	int value = buf[plusPosition(1)]<<24 | buf[plusPosition(1)]<<16 | buf[plusPosition(1)]<<8 | buf[plusPosition(1)];
	
	return value;
}

unsigned int ByteArray::readUnsignedInt()
{
	int value = buf[plusPosition(1)]<<24 | buf[plusPosition(1)]<<16 | buf[plusPosition(1)]<<8 | buf[plusPosition(1)];
	return value;
}

char* ByteArray::readUTF()
{
	char* temp = &buf[getPosition()];
	size_t len = strlen(temp);
	char*p = (char*)malloc(len+sizeof(char) +1);
	if(p == NULL)
	{
		cout<<"malloc error!!"<<endl;
		return NULL;
	}
	plusPosition(len);
	memset(p, 0, sizeof(p));
	strcpy(p, temp);
	return p;
}

char* ByteArray::readUTFBytes(int len)
{
	char* temp = &buf[getPosition()];
	char*p = (char*)malloc(len+sizeof(char) +1);
	if(p == NULL)
	{
		cout<<"malloc error!!"<<endl;
		return NULL;
	}
	plusPosition(len);
	memset(p, 0, sizeof(p));
	strcpy(p, temp);
	return p;
}

#include "byteArray.h"


using namespace std;

ByteArray::ByteArray()
{
	clear();
}

ByteArray::~ByteArray()
{
	
}

void ByteArray::setBufLen(unsigned int value)
{
	len = value;
}
 
unsigned int ByteArray::getBufLen()
{
	return len;
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
	if(value > getBytesAvailable())
	{
		cout<<"position out of range !!"<< endl <<"position is: "<<getPosition() << " add value is: "<<value << " available is: "<<getBytesAvailable() << endl;
		return -1;
	}
	
	position +=  value;
	
	return getPosition();
}

unsigned int ByteArray::minusPosition(unsigned int value)
{
	if(position  < value)
	{
		cout<<"position out of range !!"<< endl <<"position is: "<<getPosition() << " minus value is: "<<value << " available is: "<<getBytesAvailable() << endl;
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

short ByteArray::readShort()
{
//	short value = buf[plusPosition(1)]<<8 | buf[getPosition()];
	short value = *((short*)&buf[getPosition()]);
	plusPosition(2);
	return value;
}

unsigned short ByteArray::readUnsignedShort()
{
//	unsigned short value = buf[plusPosition(1)]<<8 | buf[getPosition()];
	unsigned short value = *((unsigned short*)&buf[getPosition()]);
	plusPosition(2);
	return value;
}

int ByteArray::readInt()
{
	int value = buf[plusPosition(1)]<<24 | buf[plusPosition(1)]<<16 | buf[plusPosition(1)]<<8 | buf[getPosition()];
	
	return value;
}

unsigned int ByteArray::readUnsignedInt()
{
	unsigned int value = buf[plusPosition(1)]<<24 | buf[plusPosition(1)]<<16 | buf[plusPosition(1)]<<8 | buf[getPosition()];
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

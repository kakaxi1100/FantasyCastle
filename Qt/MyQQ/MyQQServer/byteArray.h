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
	
	char buf[1024];	//缓存数组 , 可以将其设置成可变的 就是复制这个数组到新的数组，但是好麻烦啊你妹。 
	
	void setBufLen(unsigned int value);	
	unsigned int getBufLen();
		
	void setBytesAvailable(unsigned int value);
	unsigned int getBytesAvailable();
	
	unsigned int plusPosition(unsigned int value);
	unsigned int minusPosition(unsigned int value);
	unsigned int getPosition();
	
	void clear();//数组重置
	
	short readShort();//读取带符号的32位整数
	unsigned short readUnsignedShort();//读取无符号32位整数 
	
	int readInt();//读取带符号的32位整数
	unsigned int readUnsignedInt();//读取无符号32位整数 
	
	char* readUTF();//读取一个字符串 
	char* readUTFBytes(int len); //读取一个指定长度的字符串 
	
private:
	unsigned int bytesAvailable;//有效数据长度 
	unsigned int position;//游标的当前位置 
	unsigned int len;//得到的数据长度 
};

#endif

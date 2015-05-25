#ifndef BYTEARRAY_H
#define BYTEARRAY_H

class ByteArray
{
public:
	
	ByteArray();
	~ByteArray();
	
	void setBytesAvailable(unsigned int value);
	unsigned int getBytesAvailable();
	
	unsigned int plusPosition(unsigned int value);
	unsigned int minusPosition(unsigned int value);
	unsigned int getPosition();
	
	void clear();//数组重置
	int readInt();//读取带符号的32位整数
	unsigned int readUnsignedInt();//读取无符号32位整数 
	char* readUTF();//读取一个字符串 
	char* readUTFBytes(int len); //读取一个指定长度的字符串 
private:
	unsigned int bytesAvailable;//有效数据长度 
	unsigned int position;//游标的当前位置 
	char buf[1024];	//缓存数组 , 可以将其设置成可变的 就是复制这个数组到新的数组，但是好麻烦啊你妹。 
};

#endif

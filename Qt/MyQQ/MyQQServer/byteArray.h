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
	
	void clear();//��������
	int readInt();//��ȡ�����ŵ�32λ����
	unsigned int readUnsignedInt();//��ȡ�޷���32λ���� 
	char* readUTF();//��ȡһ���ַ��� 
	char* readUTFBytes(int len); //��ȡһ��ָ�����ȵ��ַ��� 
private:
	unsigned int bytesAvailable;//��Ч���ݳ��� 
	unsigned int position;//�α�ĵ�ǰλ�� 
	char buf[1024];	//�������� , ���Խ������óɿɱ�� ���Ǹ���������鵽�µ����飬���Ǻ��鷳�����á� 
};

#endif

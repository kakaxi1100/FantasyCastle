#include <cstdlib>
#include <iostream>
#include "pub.h"
#include "work.h"
#include <signal.h>

using namespace std;

int main(int argc, char* argv[])
{
	/*if(argc < 2)
	{
		cout << "please input server port !" <<endl;
		
		return EXIT_FAILURE;
	}
	
	int port = atoi(argv[1]);
	if(port == 0)
	{
		cout<<"port "<< port << " is invaild!" <<endl;
		
		return EXIT_FAILURE;
	}*/
	
	int port = 8080;
	
	cout<<"server start::::"<<endl;
	//1�����óɷ�����ػ����� 
//	setDeamon();
	
	//2������socket 
	Work w(port);
	
	//3����׽����ɳ���������ź�
	signalTemplet(SIGINT, catchSignal); 
	signalTemplet(SIGPIPE, catchSignal); 
	
	//4������work
	w.run();
	 
	cout<<"server end::::"<<endl;
	
	return EXIT_SUCCESS;
}

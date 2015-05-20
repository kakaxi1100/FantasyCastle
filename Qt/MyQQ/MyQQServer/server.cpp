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
	//1、设置成服务端守护进程 
//	setDeamon();
	
	//2、设置socket 
	Work w(port);
	
	//3、捕捉会造成程序结束的信号
	signalTemplet(SIGINT, catchSignal); 
	signalTemplet(SIGPIPE, catchSignal); 
	
	//4、运行work
	w.run();
	 
	cout<<"server end::::"<<endl;
	
	return EXIT_SUCCESS;
}

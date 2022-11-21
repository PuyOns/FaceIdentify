#include "mythread.h"


MyThread::MyThread (QObject *parent, VideoWriter *VideoWrite)
	: QThread(parent),myVideoWrite(VideoWrite)
{

}

//自定义线程函数
void MyThread::run()
{
Label: 
	myVideoWrite->~VideoWriter();	 
	myVideoWrite->release();
	if (!myVideoWrite->isOpened())
	{
		emit sendReast(true);
		return;
	}
	else
	{
		goto Label;
	}
	
}


MyThread::~MyThread()
{

}

#pragma once
#include <QThread>
#include <opencv2/opencv.hpp>

#ifndef MYTHREAD_H
#define MYTHREAD_H

using namespace cv;
using namespace std;

//�߳�5�������ر�myVideoWrite
class MyThread : public QThread
{
	Q_OBJECT

public:
	MyThread(QObject *parent, VideoWriter *VideoWrite);
	~MyThread();
	void run();  
signals:
	void sendReast(bool val);
private:
	VideoWriter *myVideoWrite; //������Ƶ
};

#endif // MYTHREAD_H

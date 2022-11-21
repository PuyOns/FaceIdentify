#pragma once
#include <QThread>
#include <opencv2/opencv.hpp>

#ifndef MYTHREAD_H
#define MYTHREAD_H

using namespace cv;
using namespace std;

//线程5：用来关闭myVideoWrite
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
	VideoWriter *myVideoWrite; //制作视频
};

#endif // MYTHREAD_H

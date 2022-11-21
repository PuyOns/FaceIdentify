#pragma once
#include <QThread>
#include "mySeetAFace.h"
#include <QMessageBox>

#ifndef FEATURE1THREAD_H
#define FEATURE1THREAD_H

class Feature1Thread : public QThread
{
	Q_OBJECT

public:
	Feature1Thread(QObject *parent, QString mySiveImagePath);
	~Feature1Thread();
	SeetaFace iiSeetaFace;   //人脸对比
	void run();  //自定义线程函数
signals:
	void sendReast( float *feat1,bool val);
private:
	QString mySiveImagePath;  //拍照时保存的图片路径
	float *feat1;
};

#endif // FEATURE1THREAD_H

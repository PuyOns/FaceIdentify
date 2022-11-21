#pragma once
#include <QThread>
#include "mySeetAFace.h"
#include <QMessageBox>

#ifndef FEATURE2THREAD_H
#define FEATURE2THREAD_H

class Feature2Thread : public QThread
{
	Q_OBJECT

public:
	Feature2Thread(QObject *parent, QString mySiveImagePath);
	~Feature2Thread();
	SeetaFace iiSeetaFace;   //人脸对比
	void run();  //自定义线程函数
signals:
	void sendReast(float *feat2, bool val);
private:
	QString mySiveImagePath;  //拍照时保存的图片路径
	
	float *feat2;
};

#endif // FEATURE2THREAD_H

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
	SeetaFace iiSeetaFace;   //�����Ա�
	void run();  //�Զ����̺߳���
signals:
	void sendReast(float *feat2, bool val);
private:
	QString mySiveImagePath;  //����ʱ�����ͼƬ·��
	
	float *feat2;
};

#endif // FEATURE2THREAD_H

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
	SeetaFace iiSeetaFace;   //�����Ա�
	void run();  //�Զ����̺߳���
signals:
	void sendReast( float *feat1,bool val);
private:
	QString mySiveImagePath;  //����ʱ�����ͼƬ·��
	float *feat1;
};

#endif // FEATURE1THREAD_H

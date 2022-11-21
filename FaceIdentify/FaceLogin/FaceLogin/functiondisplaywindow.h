#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

#ifndef FUNCTIONDISPLAYWINDOW_H
#define FUNCTIONDISPLAYWINDOW_H

class FunctionDisplayWindow : public QWidget
{
	Q_OBJECT

public:
	FunctionDisplayWindow(QWidget *parent=0);
	~FunctionDisplayWindow();
	QPushButton *myButtonStartRecording;   //��ʼ¼��
	QPushButton *myButtonStopRecording;  //ֹͣ¼��
	//������ʾ���ڰ�ť�Ƿ����
	void isUsefulFunctionWindowButton(bool val);
signals:
	void sendStartRecording();   //��ʼ¼���ź�
	void sendStopRecording();   //ֹͣ¼���ź�
	void sendEdgeDetection(); //�Ҷȼ���ź�
	void sendPhotograph();  //�����ź�

public slots:

    void myChangeFunctionDisplayWindow(bool val); //��ʾ�����л�����

	void ReceiveCompareResult(const double&, const int&);   //��ȡ�ȶԽ��

protected:
	void paintEvent(QPaintEvent *event);
private:

	QPushButton *myButtonEdgeDetection;  //��Ե���
	QPushButton *myButtonPhotograph;  //����
    bool isComparisionFcaeCamera; //�Ƿ�ԱȽ��

	int comparetime= NULL;   //�ȶ���ʱ
	double compareresult= NULL; //�ȶԽ��
};

#endif // FUNCTIONDISPLAYWINDOW_H

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
	QPushButton *myButtonStartRecording;   //开始录制
	QPushButton *myButtonStopRecording;  //停止录制
	//功能显示窗口按钮是否可用
	void isUsefulFunctionWindowButton(bool val);
signals:
	void sendStartRecording();   //开始录制信号
	void sendStopRecording();   //停止录制信号
	void sendEdgeDetection(); //灰度检测信号
	void sendPhotograph();  //拍照信号

public slots:

    void myChangeFunctionDisplayWindow(bool val); //显示窗口切换内容

	void ReceiveCompareResult(const double&, const int&);   //获取比对结果

protected:
	void paintEvent(QPaintEvent *event);
private:

	QPushButton *myButtonEdgeDetection;  //边缘检测
	QPushButton *myButtonPhotograph;  //拍照
    bool isComparisionFcaeCamera; //是否对比结果

	int comparetime= NULL;   //比对用时
	double compareresult= NULL; //比对结果
};

#endif // FUNCTIONDISPLAYWINDOW_H

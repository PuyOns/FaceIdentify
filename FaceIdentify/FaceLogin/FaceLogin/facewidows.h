#pragma once
#include <QWidget>
#include<QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QIcon>
#include <QMessageBox>
#include <QFileDialog>
#include <QSystemTrayIcon>
#include "title.h"   //窗口标题栏设计
#include "toolbaroffacewindow.h" //窗口工具栏
#include "staticbar.h"  //主窗口状态栏
#include "displayimage.h"   //显示类
#include "functiondisplaywindow.h" //功能显示窗口
#include <opencv2/opencv.hpp>
#include"feat1compfeat2.h"
#include"feature1thread.h"
#include"feature2thread.h"
#include"videorecord.h"
//#include"mythread.h" 

#ifndef FACEWIDOWS_H
#define FACEWIDOWS_H

class FaceWidows : public QWidget
{
	Q_OBJECT

public:

	FaceWidows(QWidget *parent=0);
	~FaceWidows();

	void myCreateWindow();
	void connectSignalAndSlot();

	//视频播放（或图片连续播放）
	void nextmyImageSet();

signals:

	void myDealChangeFunctionDisplayWindow(bool val); //功能窗口切换画面

	void sendResult(const double& , const int& );  //发送比对结果和比对时间到功能显示类

	void stopVideoWrite(bool val);   //给视频编码保存的线程发送停止编码保存，结束视频编码循环

protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

public slots:

     //处理托盘事件
    void myActivatedSystemTrayIcon(QSystemTrayIcon::ActivationReason myReason);

	//槽函数处理工具栏按钮的发出的信号
	void myDealOpenCamera();     //点击打开摄像按钮发出的信号处理
	void myDealOpenFile();       //点击打开文件按钮发出的信号处理
	void myDealOpenVideo();      //点击打开视频按钮发出的信号处理
	void myDealOpenFaceDiscern(); //点击打开人脸识别按钮发出的信号处理
	void myDealOpenCompare();     //对比两张图片

	//槽函数处理功能显示窗口的按钮按下去发出的信号
	void dealStartRecording();  //开始录制
	void dealStopRecording();  //停止录制
	void dealEdgeDetection();  //边缘检测
	void dealPhotograph();  //拍照 

	//连接线程的槽函数，实现获取结果
	void getReast( double *reast);  
	void getFeat1( float *feat1,bool val);
	void getFeat2( float *feat2,bool val);
//	void closemyThread(bool val);

private:

	QPoint tempPoint;

	//分别是窗口的标题栏、工具栏、图片显示栏、功能显示栏
	Title *myWindowTitle;
	ToolBarOfFaceWindow *myWindowToolBar;
	DisplayImage *myDisplayImage;
	QImage mycvMatToQImage(cv::Mat);        //将opencv的cv::mat类型转为QImage

    //cv::Mat myQImageToCvMat(QImage &image,int format); //将QImage转为opencv的cv::Mat类型  format：0~3 

	FunctionDisplayWindow *myFunctionDisplay;
	StaticBar *myWindowStaticBar;
	QSystemTrayIcon *mySystemTrayIcon;   //托盘

	//帧数：播放图片速率每秒十张以上，人眼看作视频播放
	cv::Mat myImageSet;  //opencv的数据集或者图像集
	cv::VideoCapture myVideoCapture; //opencv的视频集
	cv::VideoWriter *myVideoWrite; //制作视频
	QTimer *myTimer; //用于一定时间内图片的获取 并以每秒大于10张播放	
	double myRate; //FPS动画或者视频播放帧数
	QImage myImage;//用于图片显示
	QImage mySiveImage;    //（FaceWidows::dealPhotograph）拍照保存的图片（用作是否进行灰度检测）

	//标志位：控制控件是否可用
	bool isOpenCamera;
	bool isOpenCompareButton;
	bool isOpenFaceDiscernButton;
	bool useThread1 = true;

	float *f1,*f2; //保存两张图片的各自第一个人脸的特征点数据
	bool isFindFace1 = false;
	bool isFindFace2 = false;

   //四条线程
	Feature1Thread *Feat1thread;
	Feature2Thread *Feat2thread;
	feat1Compfeat2 *FeatCompare;
	videoRecord *myVideoRecord;


	//用作对比时间的计算
	QTime CompareStartTime;  //开始比对时间
	QTime CompareOverTime;  //比对结束时间
	
};

#endif // FACEWIDOWS_H

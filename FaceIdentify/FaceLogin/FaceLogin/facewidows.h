#pragma once
#include <QWidget>
#include<QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QIcon>
#include <QMessageBox>
#include <QFileDialog>
#include <QSystemTrayIcon>
#include "title.h"   //���ڱ��������
#include "toolbaroffacewindow.h" //���ڹ�����
#include "staticbar.h"  //������״̬��
#include "displayimage.h"   //��ʾ��
#include "functiondisplaywindow.h" //������ʾ����
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

	//��Ƶ���ţ���ͼƬ�������ţ�
	void nextmyImageSet();

signals:

	void myDealChangeFunctionDisplayWindow(bool val); //���ܴ����л�����

	void sendResult(const double& , const int& );  //���ͱȶԽ���ͱȶ�ʱ�䵽������ʾ��

	void stopVideoWrite(bool val);   //����Ƶ���뱣����̷߳���ֹͣ���뱣�棬������Ƶ����ѭ��

protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

public slots:

     //���������¼�
    void myActivatedSystemTrayIcon(QSystemTrayIcon::ActivationReason myReason);

	//�ۺ�������������ť�ķ������ź�
	void myDealOpenCamera();     //���������ť�������źŴ���
	void myDealOpenFile();       //������ļ���ť�������źŴ���
	void myDealOpenVideo();      //�������Ƶ��ť�������źŴ���
	void myDealOpenFaceDiscern(); //���������ʶ��ť�������źŴ���
	void myDealOpenCompare();     //�Ա�����ͼƬ

	//�ۺ�����������ʾ���ڵİ�ť����ȥ�������ź�
	void dealStartRecording();  //��ʼ¼��
	void dealStopRecording();  //ֹͣ¼��
	void dealEdgeDetection();  //��Ե���
	void dealPhotograph();  //���� 

	//�����̵߳Ĳۺ�����ʵ�ֻ�ȡ���
	void getReast( double *reast);  
	void getFeat1( float *feat1,bool val);
	void getFeat2( float *feat2,bool val);
//	void closemyThread(bool val);

private:

	QPoint tempPoint;

	//�ֱ��Ǵ��ڵı���������������ͼƬ��ʾ����������ʾ��
	Title *myWindowTitle;
	ToolBarOfFaceWindow *myWindowToolBar;
	DisplayImage *myDisplayImage;
	QImage mycvMatToQImage(cv::Mat);        //��opencv��cv::mat����תΪQImage

    //cv::Mat myQImageToCvMat(QImage &image,int format); //��QImageתΪopencv��cv::Mat����  format��0~3 

	FunctionDisplayWindow *myFunctionDisplay;
	StaticBar *myWindowStaticBar;
	QSystemTrayIcon *mySystemTrayIcon;   //����

	//֡��������ͼƬ����ÿ��ʮ�����ϣ����ۿ�����Ƶ����
	cv::Mat myImageSet;  //opencv�����ݼ�����ͼ��
	cv::VideoCapture myVideoCapture; //opencv����Ƶ��
	cv::VideoWriter *myVideoWrite; //������Ƶ
	QTimer *myTimer; //����һ��ʱ����ͼƬ�Ļ�ȡ ����ÿ�����10�Ų���	
	double myRate; //FPS����������Ƶ����֡��
	QImage myImage;//����ͼƬ��ʾ
	QImage mySiveImage;    //��FaceWidows::dealPhotograph�����ձ����ͼƬ�������Ƿ���лҶȼ�⣩

	//��־λ�����ƿؼ��Ƿ����
	bool isOpenCamera;
	bool isOpenCompareButton;
	bool isOpenFaceDiscernButton;
	bool useThread1 = true;

	float *f1,*f2; //��������ͼƬ�ĸ��Ե�һ������������������
	bool isFindFace1 = false;
	bool isFindFace2 = false;

   //�����߳�
	Feature1Thread *Feat1thread;
	Feature2Thread *Feat2thread;
	feat1Compfeat2 *FeatCompare;
	videoRecord *myVideoRecord;


	//�����Ա�ʱ��ļ���
	QTime CompareStartTime;  //��ʼ�ȶ�ʱ��
	QTime CompareOverTime;  //�ȶԽ���ʱ��
	
};

#endif // FACEWIDOWS_H

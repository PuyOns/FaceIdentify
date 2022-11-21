#pragma once
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QTimer>
#include <QHBoxLayout>
#include <QPixmap>
 /*
    这个类实现视频和图片显示，有两种方法实现：
	1、直接调用公有函数来实现
	2、信号和槽的方式，在主窗口槽函数实现显示
 */
#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

class DisplayImage : public QWidget
{
	Q_OBJECT

public:
	DisplayImage(QWidget *parent=0);
	~DisplayImage();

	void myVideoDisplay(QImage myImage);   //显示视频
	void myPictureShow(QImage myImage);    //显示图片

private:

	QLabel *myLabelVideoDisplay;
	QLabel *myLabelPictureShow;
	
};

#endif // DISPLAYIMAGE_H

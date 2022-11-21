#pragma once
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QTimer>
#include <QHBoxLayout>
#include <QPixmap>
 /*
    �����ʵ����Ƶ��ͼƬ��ʾ�������ַ���ʵ�֣�
	1��ֱ�ӵ��ù��к�����ʵ��
	2���źźͲ۵ķ�ʽ���������ڲۺ���ʵ����ʾ
 */
#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

class DisplayImage : public QWidget
{
	Q_OBJECT

public:
	DisplayImage(QWidget *parent=0);
	~DisplayImage();

	void myVideoDisplay(QImage myImage);   //��ʾ��Ƶ
	void myPictureShow(QImage myImage);    //��ʾͼƬ

private:

	QLabel *myLabelVideoDisplay;
	QLabel *myLabelPictureShow;
	
};

#endif // DISPLAYIMAGE_H

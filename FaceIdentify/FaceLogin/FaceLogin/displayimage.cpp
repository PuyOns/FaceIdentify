#include "displayimage.h"

DisplayImage::DisplayImage(QWidget *parent)
	: QWidget(parent)
{
	QHBoxLayout *myRowLayout = new QHBoxLayout(this);

	QPixmap myPixmap(":/image/CameraWindow640x360.jpg");
	myLabelVideoDisplay =new QLabel(this);
	myLabelVideoDisplay->setFixedSize(631, 360);
	myLabelVideoDisplay->setPixmap(myPixmap);
	myLabelVideoDisplay->setScaledContents(true);  //������ʾ����ǩ��
	myLabelVideoDisplay->setFrameStyle(QFrame::Panel | QFrame::Sunken);  //�������
	myLabelVideoDisplay->setVisible(true);    //�ɼ�

	
	myPixmap.load(":/image/faceDescern640x360Winddow.jpg");
	myLabelPictureShow = new QLabel(this);
	myLabelPictureShow->setFixedSize(632, 360);
	myLabelPictureShow->setPixmap(myPixmap);
	myLabelPictureShow->setScaledContents(true);  //������ʾ����ǩ��
	myLabelPictureShow->setFrameStyle(QFrame::Panel | QFrame::Sunken);  //�������
	myLabelPictureShow->setVisible(true);  //�ɼ�

	myRowLayout->addWidget(myLabelVideoDisplay);
	myRowLayout->addWidget(myLabelPictureShow);
	this->setLayout(myRowLayout);

}

void DisplayImage::myVideoDisplay(QImage myImage)   //��ʾ��Ƶ
{
	myLabelVideoDisplay->setPixmap(QPixmap::fromImage(myImage));
}
void DisplayImage::myPictureShow(QImage myImage)    //��ʾͼƬ
{
	myLabelPictureShow->setPixmap(QPixmap::fromImage(myImage));
}

DisplayImage::~DisplayImage()
{

}

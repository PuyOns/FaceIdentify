#include "displayimage.h"

DisplayImage::DisplayImage(QWidget *parent)
	: QWidget(parent)
{
	QHBoxLayout *myRowLayout = new QHBoxLayout(this);

	QPixmap myPixmap(":/image/CameraWindow640x360.jpg");
	myLabelVideoDisplay =new QLabel(this);
	myLabelVideoDisplay->setFixedSize(631, 360);
	myLabelVideoDisplay->setPixmap(myPixmap);
	myLabelVideoDisplay->setScaledContents(true);  //设置显示到标签内
	myLabelVideoDisplay->setFrameStyle(QFrame::Panel | QFrame::Sunken);  //设置外观
	myLabelVideoDisplay->setVisible(true);    //可见

	
	myPixmap.load(":/image/faceDescern640x360Winddow.jpg");
	myLabelPictureShow = new QLabel(this);
	myLabelPictureShow->setFixedSize(632, 360);
	myLabelPictureShow->setPixmap(myPixmap);
	myLabelPictureShow->setScaledContents(true);  //设置显示到标签内
	myLabelPictureShow->setFrameStyle(QFrame::Panel | QFrame::Sunken);  //设置外观
	myLabelPictureShow->setVisible(true);  //可见

	myRowLayout->addWidget(myLabelVideoDisplay);
	myRowLayout->addWidget(myLabelPictureShow);
	this->setLayout(myRowLayout);

}

void DisplayImage::myVideoDisplay(QImage myImage)   //显示视频
{
	myLabelVideoDisplay->setPixmap(QPixmap::fromImage(myImage));
}
void DisplayImage::myPictureShow(QImage myImage)    //显示图片
{
	myLabelPictureShow->setPixmap(QPixmap::fromImage(myImage));
}

DisplayImage::~DisplayImage()
{

}

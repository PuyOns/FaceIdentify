#include "title.h"
#include <Qicon>
#include <QMessageBox>

Title::Title(QWidget *parent)
	: QWidget(parent)
{
//	setWindowIcon(QIcon(":/image/fxx.jpg"));
//	setWindowTitle(QString::fromLocal8Bit("主窗口"));

	QPixmap myPixmap(":/image/title1280x40.png");
	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);

	myLabelIcon = new QLabel(this);
	myPixmap.load(":/image/title.png");
	myLabelIcon->setPixmap(myPixmap);
	myLabelIcon->setFixedWidth(38);
	myLabelIcon->setAutoFillBackground(true);
	myLabelIcon->move(0, 0);

	myLabel=new QLabel(this);
	QPalette myTitlePalette;
	myTitlePalette.setColor(QPalette::WindowText,Qt::white);
	myLabel->setPalette(myTitlePalette);
	myLabel->setFixedWidth(200);
	myLabel->setText(QString::fromLocal8Bit("人脸识别系统"));
	myLabel->move(50, 12);

	myButtonClose=new QPushButton(this);
	myButtonClose->setFixedSize(40, 40);
	myButtonClose->setIcon(QIcon(":/image/close.png"));
	myButtonClose->move(1240, 0);

	connect(myButtonClose, &QPushButton::pressed, this, &Title::mySendWindowClose);

	//{
	//	if (QMessageBox::Ok == QMessageBox::information(this, QString::fromLocal8Bit("关闭登录"),
	//		QString::fromLocal8Bit("是否关闭窗口"), QMessageBox::Ok | QMessageBox::No))
	//	{
	//		this->close();
	//		emit myWindowClose();
	//	}

	//}
	//);
	
	myButtonMax = new QPushButton(this);
	myButtonMax->setFixedSize(40, 40);
	myButtonMax->setIcon(QIcon(":/image/max.png"));
	myButtonMax->move(1203, 0);

	connect(myButtonMax, &QPushButton::pressed, this, &Title::mySendWindowShowMax);

	//{
	//	/*if (this->isMaximized())
	//	{
	//		this->showNormal();
	//		emit myWindowShowNormal();
	//	}
	//	else
	//	{
	//		this->showMaximized();
	//		emit myWindowShowMax();
	//	}*/

	//}
	//);

	myButtonMix=new QPushButton(this);
	myButtonMix->setFixedSize(40, 40);
	myButtonMix->setIcon(QIcon(":/image/min.png"));
	myButtonMix->move(1166, 0);

	connect(myButtonMix, &QPushButton::pressed, this, &Title::mySendWindowShowMin);

	//{
	//	this->showMinimized();
	//	emit myWindowShowMin();
	//}
	//);

	
}

Title::~Title()
{

}

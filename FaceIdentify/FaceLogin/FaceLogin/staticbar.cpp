#include "staticbar.h"
#include <QHBoxLayout>
#include<QTime>
#include <QTimer>
#include <QSizePolicy>
#include <QToolBar>

StaticBar::StaticBar(QWidget *parent)
	: QWidget(parent)
{
	QPixmap myPixmap(":/image/staticBar1280x40.png");
	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);

	//����������ɫΪ��ɫ
	QHBoxLayout *myRowLayout = new QHBoxLayout(this);
	
	QPalette myStaticBarPalette;
	myStaticBarPalette.setColor(QPalette::WindowText, Qt::black);

	myVersionLabel=new QLabel;
	myVersionLabel->setFixedSize(150, 20);	
	myVersionLabel->setPalette(myStaticBarPalette);
	myVersionLabel->setText(QString::fromLocal8Bit("�汾�ţ�1.0.1"));

	myDeveloperLabel = new QLabel;
	myDeveloperLabel->setFixedSize(200,20);
	myDeveloperLabel->setPalette(myStaticBarPalette);
	myDeveloperLabel->setText(QString::fromLocal8Bit("�����ˣ�CUTE KITTY"));

	myExpendingLabel = new QLabel;
	myExpendingLabel->setFixedHeight(40);


	myTimeLabel = new QLabel;
	myTimeLabel->setFixedSize(100, 20);
	myTimeLabel->setPalette(myStaticBarPalette);
	myTimeLabel->setContentsMargins(0, 0, 0, 0);

	//��ʱ��һ��Ҫ��ָ�� Ҫ��Ȼʱ�䲻��
	QTimer *myTimer=new QTimer(this);
	myTimer->start(1000);

	QTime myTime = QTime::currentTime();
	QString myCurrentTime = myTime.toString("hh:mm:ss");
	myTimeLabel->setText(myCurrentTime);

	connect(myTimer, &QTimer::timeout, this,[=]() 
			{
				QTime myTime = QTime::currentTime();
				QString myCurrentTime = myTime.toString("hh:mm:ss");
				myTimeLabel->setText(myCurrentTime);   
			}
		   );
	myRowLayout->addWidget(myVersionLabel);
	myRowLayout->addWidget(myDeveloperLabel);
	myRowLayout->addWidget(myExpendingLabel);
	myRowLayout->addWidget(myTimeLabel);

//	this->setLayout(myRowLayout);

}

StaticBar::~StaticBar()
{

}

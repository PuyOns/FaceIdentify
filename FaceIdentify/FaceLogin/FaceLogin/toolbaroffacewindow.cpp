#include "toolbaroffacewindow.h"
#include <QHBoxLayout>

ToolBarOfFaceWindow::ToolBarOfFaceWindow(QWidget *parent)
	: QWidget(parent)
{
	QPixmap myPixmap(":/image/winToolBar1280x140.jpg");
	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);

	QHBoxLayout *myRowLayout=new QHBoxLayout;


	myCameraButton=new QPushButton;
	myCameraButton->setFixedSize(140, 140);
	myCameraButton->setStyleSheet("QPushButton{background-image:url(:/image/openCameraButton.jpg);}");
	connect(myCameraButton, &QPushButton::clicked, this, &ToolBarOfFaceWindow::mySendOpenCamera);

	myFileButton = new QPushButton;
	myFileButton->setFixedSize(140, 140);
	myFileButton->setStyleSheet("QPushButton{background-image:url(:/image/File.jpg);}");
	connect(myFileButton, &QPushButton::clicked, this, &ToolBarOfFaceWindow::mySendOpenFile);

	myVideoButton = new QPushButton;
	myVideoButton->setFixedSize(140, 140);
	myVideoButton->setStyleSheet("QPushButton{background-image:url(:/image/playButton140x140b.jpg);}");
	connect(myVideoButton, &QPushButton::clicked, this, &ToolBarOfFaceWindow::mySendOpenVideo);

	myFaceDiscernButton = new QPushButton;
	myFaceDiscernButton->setFixedSize(140, 140);
	myFaceDiscernButton->setStyleSheet("QPushButton{background-image:url(:/image/siveImage.jpg);}");
	connect(myFaceDiscernButton, &QPushButton::clicked, this, &ToolBarOfFaceWindow::mySendOpenFaceDiscern);

	myCompareButton = new QPushButton;
	myCompareButton->setFixedSize(220,140);
	myCompareButton->setStyleSheet("QPushButton{background-image:url(:/image/faceDiscernButton.jpg);}");
	connect(myCompareButton, &QPushButton::clicked, this, &ToolBarOfFaceWindow::mySendOpenCompare);

	myRowLayout->addWidget(myCameraButton);
	myRowLayout->addWidget(myFaceDiscernButton);
	myRowLayout->addWidget(myCompareButton);
	myRowLayout->addWidget(myFileButton);
	myRowLayout->addWidget(myVideoButton);	
	
	
	setLayout(myRowLayout);


}






















ToolBarOfFaceWindow::~ToolBarOfFaceWindow()
{

}

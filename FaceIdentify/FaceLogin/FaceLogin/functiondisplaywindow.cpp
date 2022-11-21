#include "functiondisplaywindow.h"


FunctionDisplayWindow::FunctionDisplayWindow(QWidget *parent)
	: QWidget(parent)
{
	 comparetime=0;   //�ȶ���ʱ
	 compareresult=0; //�ȶԽ��
	isComparisionFcaeCamera = false;

	QPixmap myPixmap(":/image/1280x140Window.jpg");
	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);

	myButtonStartRecording=new QPushButton(this);
	myButtonStartRecording->setFixedSize(55, 55);
	myButtonStartRecording->move(20, 8);
	myButtonStartRecording->setStyleSheet("QPushButton{background-image:url(:/image/beginButtonOnFunctionalWindow55X55.jpg);}");
	connect(myButtonStartRecording, &QPushButton::clicked, this, &FunctionDisplayWindow::sendStartRecording);

	myButtonStopRecording = new QPushButton(this);
	myButtonStopRecording->setFixedSize(55, 55);
	myButtonStopRecording->move(20, 78);
	myButtonStopRecording->setStyleSheet("QPushButton{background-image:url(:/image/stopButtonOnFunctionalWindow55X55.jpg);}");
	connect(myButtonStopRecording, &QPushButton::clicked, this, &FunctionDisplayWindow::sendStopRecording);

	myButtonEdgeDetection = new QPushButton(this);
	myButtonEdgeDetection->setFixedSize(140, 140);
	myButtonEdgeDetection->move(75, 0);
	myButtonEdgeDetection->setStyleSheet("QPushButton{background-image:url(:/image/borderCheckOnFunctionalWindow140X140.jpg);}");
	connect(myButtonEdgeDetection, &QPushButton::clicked, this, &FunctionDisplayWindow::sendEdgeDetection);

	myButtonPhotograph = new QPushButton(this);
	myButtonPhotograph->setFixedSize(140, 140);
	myButtonPhotograph->move(230, 0);
	myButtonPhotograph->setStyleSheet("QPushButton{background-image:url(:/image/PhotographOnFunctionalWindow140X140.jpg);}");
	connect(myButtonPhotograph, &QPushButton::clicked, this, &FunctionDisplayWindow::sendPhotograph);

	//��ť��ʼ�����ã����п�ʼ��ֹͣ�ź�ʱ�ڶ�Ӧ�ۺ���������ť ��ʹ���书��
	myButtonStartRecording->setDisabled(true);
	myButtonStopRecording->setDisabled(true);
	myButtonEdgeDetection->setDisabled(true);
	myButtonPhotograph->setDisabled(true);


}

void FunctionDisplayWindow::isUsefulFunctionWindowButton(bool val)
{
	if (val)
	{
		myButtonStartRecording->setDisabled(false);
		myButtonStopRecording->setDisabled(false);
		myButtonEdgeDetection->setDisabled(false);
		myButtonPhotograph->setDisabled(false);
	}
	else
	{
		myButtonStartRecording->setDisabled(true);
		myButtonStopRecording->setDisabled(true);
		myButtonEdgeDetection->setDisabled(true);
		myButtonPhotograph->setDisabled(true);
	}
}


void FunctionDisplayWindow::myChangeFunctionDisplayWindow(bool val)    //��ʾ�����л�����
{
	isComparisionFcaeCamera = val;
	QPixmap myPixmap;
	if (val)
	{
		myPixmap.load(":/image/winToolBar1280x140.jpg");
		myButtonStartRecording->hide();
		myButtonStopRecording->hide();
		myButtonEdgeDetection->hide();
		myButtonPhotograph->hide();
		
	}
	else
	{
		myPixmap.load(":/image/1280x140Window.jpg");
		myButtonStartRecording->show();
		myButtonStopRecording->show();
		myButtonEdgeDetection->show();
		myButtonPhotograph->show();
	}

	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	this->setAutoFillBackground(true);
	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);

	/***************************************************************************/

	//����д�ֻ�ͼӦ�÷��ڻ�ͼ�¼�������ﲻ��ʵ��

	//if (isComparisionFcaeCamera)
	//{
	//	QPainter myPainter(this);
	//	QFont myFont;
	//	myFont.setPixelSize(40);
	//	QPen myPen;
	//	myPen.setColor(Qt::blue);
	//	myPainter.setPen(myPen);
	//	myPainter.setFont(myFont);
	//	myPainter.drawText(QPoint(200, 70), QString::fromLocal8Bit("�ԱȽ���ǣ�%1"));
	//	myPainter.drawText(QPoint(400, 70), QString::fromLocal8Bit("�Ա�ʱ���ǣ�%1"));
	//}

}

void FunctionDisplayWindow::paintEvent(QPaintEvent *event)
{
	if (isComparisionFcaeCamera)
	{
		QPainter myPainter(this);
		QFont myFont;
		myFont.setPixelSize(40);
		QPen myPen;
		myPen.setColor(Qt::red);
		myPainter.setPen(myPen);
		myPainter.setFont(myFont);
		myPainter.drawText(QPoint(200, 70), QString::fromLocal8Bit("�ԱȽ���ǣ�%1").arg(compareresult));
		myPainter.drawText(QPoint(800, 70), QString::fromLocal8Bit("�Ա�ʱ���ǣ�%1").arg(comparetime));
	}

}

void FunctionDisplayWindow::ReceiveCompareResult(const double& result, const int& time)   //��ȡ�ȶԽ��
{
	compareresult = result;
	comparetime = time;
}

FunctionDisplayWindow::~FunctionDisplayWindow()
{
	
	

}

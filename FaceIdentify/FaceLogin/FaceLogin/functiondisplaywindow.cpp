#include "functiondisplaywindow.h"


FunctionDisplayWindow::FunctionDisplayWindow(QWidget *parent)
	: QWidget(parent)
{
	 comparetime=0;   //比对用时
	 compareresult=0; //比对结果
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

	//按钮开始不能用，当有开始或停止信号时在对应槽函数开启按钮 并使用其功能
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


void FunctionDisplayWindow::myChangeFunctionDisplayWindow(bool val)    //显示窗口切换内容
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

	//窗口写字绘图应该放在绘图事件里，在这里不能实现

	//if (isComparisionFcaeCamera)
	//{
	//	QPainter myPainter(this);
	//	QFont myFont;
	//	myFont.setPixelSize(40);
	//	QPen myPen;
	//	myPen.setColor(Qt::blue);
	//	myPainter.setPen(myPen);
	//	myPainter.setFont(myFont);
	//	myPainter.drawText(QPoint(200, 70), QString::fromLocal8Bit("对比结果是：%1"));
	//	myPainter.drawText(QPoint(400, 70), QString::fromLocal8Bit("对比时间是：%1"));
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
		myPainter.drawText(QPoint(200, 70), QString::fromLocal8Bit("对比结果是：%1").arg(compareresult));
		myPainter.drawText(QPoint(800, 70), QString::fromLocal8Bit("对比时间是：%1").arg(comparetime));
	}

}

void FunctionDisplayWindow::ReceiveCompareResult(const double& result, const int& time)   //获取比对结果
{
	compareresult = result;
	comparetime = time;
}

FunctionDisplayWindow::~FunctionDisplayWindow()
{
	
	

}

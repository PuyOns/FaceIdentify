#include "lineeditwithicon.h"


LineEditWithIcon::LineEditWithIcon(const QString &myImagePath, QWidget *parent)
	: myMapPath(myImagePath),QWidget(parent)
{
	//设置窗体颜色
	QPalette myPalette;     
	myPalette.setColor(QPalette::Window, Qt::white);
	this->setPalette(myPalette);

	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	myLineEdit =new QLineEdit(this);
	myLineEdit->move(30,10);
	myLineEdit->setFrame(false);
	myLineEdit->setFixedWidth(180);
	myLineEdit->setFixedHeight(20);

	 connect(myLineEdit, &QLineEdit::textChanged, this, [=](const QString text)
	 {
		 myValue = text;
	 }
	 );
}

void LineEditWithIcon::setValue(const QString &text)
{
	myLineEdit->setText(text);
}
void LineEditWithIcon::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter myPainter(this);
	myPainter.drawPixmap(10,10, QPixmap(myMapPath));
	myPainter.setRenderHint(QPainter::Antialiasing);   //反锯齿
	myPainter.setPen(QPen(Qt::black));
	QRect myRect = this->rect();
	myRect.setWidth(myRect.width()-16);
	myRect.setHeight(myRect.height() - 5);
	myPainter.drawRoundedRect(myRect,20,20);


}

void LineEditWithIcon::setEchoMode(QLineEdit::EchoMode falg)
{
	myLineEdit->setEchoMode(falg);
}

LineEditWithIcon::~LineEditWithIcon()
{
	
}

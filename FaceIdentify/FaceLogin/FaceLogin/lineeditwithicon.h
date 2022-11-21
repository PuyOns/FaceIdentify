#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPaintEvent>
#include <QPainter>

#ifndef LINEEDITWITHICON_H
#define LINEEDITWITHICON_H

class LineEditWithIcon : public QWidget
{
	Q_OBJECT

public:
	LineEditWithIcon(const QString &myImagePath,QWidget *parent=0);
	~LineEditWithIcon();
	void val(const QString& temp) { myValue = temp; }
	QString myText(){ return myValue; }
	void setValue(const QString &text);    //给输入框设置值

	void setEchoMode(QLineEdit::EchoMode falg);    //设置是否为密码显示属性

protected:
	void paintEvent(QPaintEvent *event);
	

private:
	QLineEdit *myLineEdit;
	QString myMapPath;
	QString myValue;
	
};

#endif // LINEEDITWITHICON_H

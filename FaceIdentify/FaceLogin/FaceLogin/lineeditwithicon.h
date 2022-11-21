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
	void setValue(const QString &text);    //�����������ֵ

	void setEchoMode(QLineEdit::EchoMode falg);    //�����Ƿ�Ϊ������ʾ����

protected:
	void paintEvent(QPaintEvent *event);
	

private:
	QLineEdit *myLineEdit;
	QString myMapPath;
	QString myValue;
	
};

#endif // LINEEDITWITHICON_H

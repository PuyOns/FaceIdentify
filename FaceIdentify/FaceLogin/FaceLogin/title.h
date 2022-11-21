#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#ifndef TITLE_H
#define TITLE_H

class Title : public QWidget
{
	Q_OBJECT

public:
	Title(QWidget *parent=NULL);
	~Title();
signals:
	void mySendWindowClose();
	void mySendWindowShowMax();
	void mySendWindowShowMin();
//	void mySendWindowShowNormal();

private:
	QLabel *myLabel;
	QLabel *myLabelIcon;
	QPushButton *myButtonClose;
	QPushButton *myButtonMix;
	QPushButton *myButtonMax;
	
};

#endif // TITLE_H

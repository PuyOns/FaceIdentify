#pragma once
#include <QLabel>
#include <QWidget>

#ifndef STATICBAR_H
#define STATICBAR_H

class StaticBar : public QWidget
{
	Q_OBJECT

public:
	StaticBar(QWidget *parent=0);
	~StaticBar();

private:
	QLabel *myTimeLabel;
	QLabel *myVersionLabel;
	QLabel *myDeveloperLabel;
	QLabel *myExpendingLabel;
};

#endif // STATICBAR_H

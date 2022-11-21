#pragma once
#include <QWidget>
#include <QPushButton>

#ifndef TOOLBAROFFACEWINDOW_H
#define TOOLBAROFFACEWINDOW_H

class ToolBarOfFaceWindow : public QWidget
{
	Q_OBJECT

public:
	ToolBarOfFaceWindow(QWidget *parent=NULL);
	~ToolBarOfFaceWindow();
signals:
	void mySendOpenCamera();
	void mySendOpenFile();
	void mySendOpenVideo();
	void mySendOpenFaceDiscern();
	void mySendOpenCompare();

private:
	QPushButton *myCameraButton;
	QPushButton *myFileButton;
	QPushButton *myVideoButton;
	QPushButton *myFaceDiscernButton;
	QPushButton *myCompareButton;
};

#endif // TOOLBAROFFACEWINDOW_H

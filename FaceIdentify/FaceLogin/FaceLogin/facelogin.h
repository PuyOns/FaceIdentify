#pragma once
#include <QWidget>
#include <QDialog>
#include<QPushButton>
#include<QMouseEvent>
#include<QPaintEvent>
#include <QEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include<QPainter>
#include<QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QCheckBox>
#include <QTextStream>
#include "interfacefunction.h"
#include "rememberUserIdAndPassword.h"   
#include "lineeditwithicon.h"

#ifndef FACELOGIN_H
#define FACELOGIN_H

class FaceLogin : public QDialog
{
	Q_OBJECT

public:
	FaceLogin(QWidget *parent = 0);
	~FaceLogin();

	//void AssignmentIdValue(const QString &text);   //设置id和Password的上次记住密码的值
	//void AssignmentPasswordValue(const QString &text);

public slots:

	void Login();

protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:

	bool CheckIsExist(const QString&,const QString&); //查找list表里面账号密码是否存在和重复

private:

	QPushButton *myButtonLogin;
	QPushButton *myMinWindowsButton;
	QPushButton *myMaxWindowsButton;
	QPushButton *myCloseWindowsButton;

	QLabel *myLabelShowCurrentTime;
	QPoint tempPoint;  
	QTimer *myTimer;

	LineEditWithIcon  *myIdLineEdit;
	LineEditWithIcon *myPasswordLineEdit;

	QCheckBox *myCheckBox;
	QList <IDANDPASSWORD> list;

};

#endif // FACELOGIN_H

#pragma once
#include <QObject>
#include "InterfacePort.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QMessageBox>
#include "mytcpclient.h"

#ifndef INTERFACEFUNCTION_H
#define INTERFACEFUNCTION_H

/*  1.心跳接口(heartPort)
     (1)检查是否在线
	 (2)检查版本是否需要更新
*/
void heartPort(QString version);



/*  2.登录接口(clientLogin)
(1)
(2)
*/
void clientLogin(USERANDPASS userandpassword);


/*  3.修改密码接口(modifyPassWord)
(1)
(2)
*/
void modifyPassWord(MODIFYPASSWORD  data);



QString getDatetime();

#endif // !INTERFACEFUNCTION_H
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

/*  1.�����ӿ�(heartPort)
     (1)����Ƿ�����
	 (2)���汾�Ƿ���Ҫ����
*/
void heartPort(QString version);



/*  2.��¼�ӿ�(clientLogin)
(1)
(2)
*/
void clientLogin(USERANDPASS userandpassword);


/*  3.�޸�����ӿ�(modifyPassWord)
(1)
(2)
*/
void modifyPassWord(MODIFYPASSWORD  data);



QString getDatetime();

#endif // !INTERFACEFUNCTION_H
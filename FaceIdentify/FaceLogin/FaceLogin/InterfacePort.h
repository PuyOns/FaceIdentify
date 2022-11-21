#pragma once
#include <qstring>

#ifndef INTERFACEPORT_H
#define INTERFACEPORT_H

typedef struct UserAndPassWord
{
	QString userName;
	QString passWord;
}USERANDPASS,*PTUSERANDPASS;

typedef struct ModifyPasswordWord
{
	QString userName;
	QString oldPassWord;
	QString newPassWord;
	QString phoneNUM;
}MODIFYPASSWORD, *PTMODIFYPASSWORD;


#endif // !INTERFACEPORT_H
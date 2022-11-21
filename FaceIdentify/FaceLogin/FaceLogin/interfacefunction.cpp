#include"interfacefunction.h"

QString getDatetime()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	return current_date_time.toString("yyyy-MM-dd hh:mm:ss");
}

/*  1.心跳接口(heartPort)
(1)检查是否在线
(2)检查版本是否需要更新
*/

void heartPort(QString version)
{
	myTcpClient client;
	//if (!client.connectToSever())
	//{
	//	QMessageBox::information(NULL, QString::fromLocal8Bit("提示消息"), QString::fromLocal8Bit("连接服务器失败！"));
	//	return;
	//}

	QJsonObject json;
	json.insert("InterfaceName", "heartPort");

	/*******************************************调试地方***************************
	*******************************************************************************
	******************************************************************************/
	json.insert("version", version);
	json.insert("currentDatetime",getDatetime());

	QJsonDocument jsonDOC;
	jsonDOC.setObject(json);
	QByteArray bytearray = jsonDOC.toJson(QJsonDocument::Compact);
	client.sendMessage(bytearray);

}


/*  2.登录接口(clientLogin)
(1)
(2)
*/
void clientLogin(USERANDPASS userandpassword)
{
	//if (!client.connectToSever())
	//{
	//	QMessageBox::information(NULL, QString::fromLocal8Bit("提示消息"), QString::fromLocal8Bit("连接服务器失败！"));
	//	return;
	//}


}


/*  3.修改密码接口(modifyPassWord)
(1)
(2)
*/
void modifyPassWord(MODIFYPASSWORD  data)
{
	//if (!client.connectToSever())
	//{
	//	QMessageBox::information(NULL, QString::fromLocal8Bit("提示消息"), QString::fromLocal8Bit("连接服务器失败！"));
	//	return;
	//}
}


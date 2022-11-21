#include"interfacefunction.h"

QString getDatetime()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	return current_date_time.toString("yyyy-MM-dd hh:mm:ss");
}

/*  1.�����ӿ�(heartPort)
(1)����Ƿ�����
(2)���汾�Ƿ���Ҫ����
*/

void heartPort(QString version)
{
	myTcpClient client;
	//if (!client.connectToSever())
	//{
	//	QMessageBox::information(NULL, QString::fromLocal8Bit("��ʾ��Ϣ"), QString::fromLocal8Bit("���ӷ�����ʧ�ܣ�"));
	//	return;
	//}

	QJsonObject json;
	json.insert("InterfaceName", "heartPort");

	/*******************************************���Եط�***************************
	*******************************************************************************
	******************************************************************************/
	json.insert("version", version);
	json.insert("currentDatetime",getDatetime());

	QJsonDocument jsonDOC;
	jsonDOC.setObject(json);
	QByteArray bytearray = jsonDOC.toJson(QJsonDocument::Compact);
	client.sendMessage(bytearray);

}


/*  2.��¼�ӿ�(clientLogin)
(1)
(2)
*/
void clientLogin(USERANDPASS userandpassword)
{
	//if (!client.connectToSever())
	//{
	//	QMessageBox::information(NULL, QString::fromLocal8Bit("��ʾ��Ϣ"), QString::fromLocal8Bit("���ӷ�����ʧ�ܣ�"));
	//	return;
	//}


}


/*  3.�޸�����ӿ�(modifyPassWord)
(1)
(2)
*/
void modifyPassWord(MODIFYPASSWORD  data)
{
	//if (!client.connectToSever())
	//{
	//	QMessageBox::information(NULL, QString::fromLocal8Bit("��ʾ��Ϣ"), QString::fromLocal8Bit("���ӷ�����ʧ�ܣ�"));
	//	return;
	//}
}


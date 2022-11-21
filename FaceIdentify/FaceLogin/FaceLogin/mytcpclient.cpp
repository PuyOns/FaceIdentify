#include "mytcpclient.h"
#include <QTcpSocket>
#include <QMessageBox>

myTcpClient::myTcpClient()
	: QObject()
{
	myTcpSocket = new QTcpSocket(this);

	//和服务器连接
	this->connectToSever();


	//读消息
	connect(myTcpSocket, &QTcpSocket::readyRead, this, &myTcpClient::readMessage);
}

bool myTcpClient::connectToSever()
{

	myTcpSocket->abort();  //取消已有的连接
	//连接服务器
	myTcpSocket->connectToHost("127.0.0.1", 888);

	connect(myTcpSocket, &QTcpSocket::connected, this, [=]() 
			{
				QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("连接服务器成功！！"));
			
	        }
	       );
	return true;
	if (myTcpSocket->waitForConnected(10000))
	{
		if (QMessageBox::Yes == QMessageBox::information
		(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("连接服务器失败,是否关闭客户端?"), QMessageBox::Yes | QMessageBox::No))
		{
			emit connectFailToSever();
			return false;
		}
	}
}

//发送客户端的版本等数据到服务器 (直接调用对象发送） 
void myTcpClient::sendMessage(QByteArray byte)
{
	QString str(byte);
	QByteArray message;   //定义一个buff缓冲区,把数据读到缓冲区
	QDataStream out(&message, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_13);    //要与服务器版本一致   QDataStream::Qt_5_13
	out << str;                //把str的数据写到缓冲区message
	myTcpSocket->write(message);
	//把缓冲区的数据强行输出
//	myTcpSocket->flush();
}

void myTcpClient::readMessage()
{
	QByteArray buffer;
	buffer = myTcpSocket->readAll();

}

myTcpClient::~myTcpClient()
{

}

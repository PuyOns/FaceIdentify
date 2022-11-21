#include "faceloginserver.h"
#include <QDataStream>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QMessageBox>

FaceLoginServer::FaceLoginServer(QWidget *parent)
	: QWidget(parent)
{
	myTcpSever = new QTcpServer(this);
	myTcpSocket = new QTcpSocket(this);
	myTcpSever->listen(QHostAddress::Any, 888);
	connect(myTcpSever,&QTcpServer::newConnection,this,&FaceLoginServer::newConnect);
	connect(myTcpSocket, &QTcpSocket::readyRead, this, &FaceLoginServer::readMessage);

}

void FaceLoginServer::newConnect()
{
	myTcpSocket = myTcpSever->nextPendingConnection();
	connect(myTcpSocket, &QTcpSocket::readyRead, this, &FaceLoginServer::readMessage);
//	QMessageBox::information(this, QString::fromLocal8Bit("提示消息"), QString::fromLocal8Bit("成功获取客户端发送的信息"));
	
}

//发送版本信息等到客户端 
void FaceLoginServer::sendMessage(QString information)
{
	 
	QString str = information;
	QByteArray message;   //定义一个buff缓冲区
	QDataStream out(&message, QIODevice::WriteOnly);  
	out.setVersion(QDataStream::Qt_5_13);
	//message<<out<<str
	out << str;  //数据读到缓冲区message
	myTcpSocket->write(message);
}

//读取客户端发送的版本等信息
void FaceLoginServer::readMessage()
{
	QMessageBox::information(this, QString::fromLocal8Bit("提示消息"), QString::fromLocal8Bit("成功获取客户端发送的信息"));
	QDataStream in(myTcpSocket);
	in.setVersion(QDataStream::Qt_5_13);
	in >> message;
	if (!message.isEmpty())
	{
		isOk =analyse_jsondata(message.toLatin1());
	}
	if (isOk)
	{
		sendMessage("ok!");
	}

}

bool FaceLoginServer::analyse_jsondata(const QByteArray& bytes)    //json解析
{
	QJsonParseError iserror;
	QJsonDocument jsonDOC = QJsonDocument::fromJson(bytes, &iserror);
	if (iserror.error==QJsonParseError::NoError)
	{
		if (jsonDOC.isObject())
		{
			QVariantMap myMap = jsonDOC.toVariant().toMap();
			if (myMap["InterfaceName"]== "heartPort")
			{
				if (myMap["version"] == "version 1.0.1")
				{
					return true;
				}
			}
		}
	}
	return false;
}
FaceLoginServer::~FaceLoginServer()
{

}

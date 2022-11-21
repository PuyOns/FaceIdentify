#include "mytcpclient.h"
#include <QTcpSocket>
#include <QMessageBox>

myTcpClient::myTcpClient()
	: QObject()
{
	myTcpSocket = new QTcpSocket(this);

	//�ͷ���������
	this->connectToSever();


	//����Ϣ
	connect(myTcpSocket, &QTcpSocket::readyRead, this, &myTcpClient::readMessage);
}

bool myTcpClient::connectToSever()
{

	myTcpSocket->abort();  //ȡ�����е�����
	//���ӷ�����
	myTcpSocket->connectToHost("127.0.0.1", 888);

	connect(myTcpSocket, &QTcpSocket::connected, this, [=]() 
			{
				QMessageBox::information(NULL, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ӷ������ɹ�����"));
			
	        }
	       );
	return true;
	if (myTcpSocket->waitForConnected(10000))
	{
		if (QMessageBox::Yes == QMessageBox::information
		(NULL, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ӷ�����ʧ��,�Ƿ�رտͻ���?"), QMessageBox::Yes | QMessageBox::No))
		{
			emit connectFailToSever();
			return false;
		}
	}
}

//���Ϳͻ��˵İ汾�����ݵ������� (ֱ�ӵ��ö����ͣ� 
void myTcpClient::sendMessage(QByteArray byte)
{
	QString str(byte);
	QByteArray message;   //����һ��buff������,�����ݶ���������
	QDataStream out(&message, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_13);    //Ҫ��������汾һ��   QDataStream::Qt_5_13
	out << str;                //��str������д��������message
	myTcpSocket->write(message);
	//�ѻ�����������ǿ�����
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

#pragma once
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>

#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

class myTcpClient : public QObject
{
	Q_OBJECT

public:
	myTcpClient();
	~myTcpClient();
	bool connectToSever();
	void sendMessage(QByteArray byte);
signals:
	void connectFailToSever();

protected slots:
    void readMessage();


private:
	QTcpSocket *myTcpSocket;
	
};

#endif // MYTCPCLIENT_H

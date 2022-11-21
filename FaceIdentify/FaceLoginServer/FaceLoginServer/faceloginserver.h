#ifndef FACELOGINSERVER_H
#define FACELOGINSERVER_H

#include <QtWidgets/QWidget>
#include <QTcpServer>
#include <QTcpSocket>

class FaceLoginServer : public QWidget
{
	Q_OBJECT

public:
	FaceLoginServer(QWidget *parent = 0);
	~FaceLoginServer();

protected slots:
	void newConnect();
	void sendMessage(QString information);
	void readMessage();

	bool analyse_jsondata(const QByteArray& bytes);     //Json½âÎö
private:
	QString message;
	QTcpServer *myTcpSever;
	QTcpSocket *myTcpSocket;

	bool isOk;

};

#endif // FACELOGINSERVER_H

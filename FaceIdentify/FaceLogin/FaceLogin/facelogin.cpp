#include "facelogin.h"



FaceLogin::FaceLogin(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon(QIcon(":/image/logining.png"));
	setWindowTitle(QString::fromLocal8Bit("��¼����"));
	
	QPixmap myPixmap(":/image/Pixmap.png");
	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	
	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);


	myButtonLogin = new QPushButton(this);
	myButtonLogin->setText(QString::fromLocal8Bit("��¼"));
	myButtonLogin->move(155, 520);
	myButtonLogin->setFixedSize(100, 40);
	myButtonLogin->autoFillBackground();
	myButtonLogin->setIcon(QIcon(":/image/logining.png"));

	
	myCloseWindowsButton = new QPushButton(this);
	myCloseWindowsButton->setFixedSize(30, 30);
	myCloseWindowsButton->move(360, 0);
	myCloseWindowsButton->autoFillBackground();
	myCloseWindowsButton->setIcon(QIcon(":/image/close.png"));

	myMaxWindowsButton = new QPushButton(this);
	myMaxWindowsButton->setFixedSize(30, 30);
	myMaxWindowsButton->move(320, 0);
	myMaxWindowsButton->autoFillBackground();
	myMaxWindowsButton->setIcon(QIcon(":/image/max.png"));

	myMinWindowsButton = new QPushButton(this);
	myMinWindowsButton->setFixedSize(30, 30);
	myMinWindowsButton->move(280, 0);
	myMinWindowsButton->autoFillBackground();
	myMinWindowsButton->setIcon(QIcon(":/image/min.png"));

	//�����˺����������
	myIdLineEdit = new LineEditWithIcon(":/image/person.png", this);
	myIdLineEdit->move(100, 400);

	myPasswordLineEdit = new LineEditWithIcon(":/image/passwd.png", this);
	myPasswordLineEdit->move(100, 450);
	myPasswordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);  //����������ʾ��ʽ
	
	myCheckBox = new QCheckBox(this);    //�Ƿ��ס�˺�������
	myCheckBox->setText(QString::fromLocal8Bit("��ס����"));
	myCheckBox->move(100, 498);

								//state������ʱ��ʾ�Ѿ��Ѽ�ס�������
	connect(myCheckBox, &QCheckBox::stateChanged, this, [=](int state)   
			{
				if (state)
				{ 		
					if (!myIdLineEdit->myText().isEmpty()&&!myPasswordLineEdit->myText().isEmpty())
					{
						QFile myFile("./IdAndPassword.ini");
						//�鿴�������Ƿ���������˺ź�������ͬ
						if ( list.isEmpty()|| !CheckIsExist(myIdLineEdit->myText(), myPasswordLineEdit->myText()) )
						{
							myFile.open(QIODevice::ReadWrite | QIODevice::Append);  // (append)׷�ӻ��ߴ���
							QTextStream out(&myFile);
							out << myIdLineEdit->myText() << ":" << myPasswordLineEdit->myText() << "\n";
							IdAndPassword strData;
							strData.userId = myIdLineEdit->myText();
							strData.Password = myPasswordLineEdit->myText();
							list.append(strData);
						
						}
						myFile.close();
						
					}
				}
			}
		   );

	//�������ļ����ж�ȡ
	QFile myFile("./IdAndPassword.ini");
	if (!myFile.open(QIODevice::ReadOnly))
	{
		
		return;
	}
	QTextStream in(&myFile);

	list.clear();   //����list�Ա�ʹ��list

	while (!in.atEnd())
	{
		QString oneLine = in.readLine();
		IDANDPASSWORD strData;
		QStringList myList = oneLine.split(":");
		strData.userId = myList.at(0);
		strData.Password = myList.at(1);
		list.append(strData);

	}

	if (!list.isEmpty())
	{
		//���˺������������ʷ���һ�μ�ס����ʱ��ֵ
		myIdLineEdit->setValue(list[list.count() - 1].userId);
		myPasswordLineEdit->setValue(list[list.count() - 1].Password);

	}
	
	myFile.close();

	//myLabelId = new QLabel(this);
	//myLabelId->move(100, 400);
	//myLabelId->setText(QString::fromLocal8Bit("�˺ţ�"));

	//myLabelPassword = new QLabel(this);
	//myLabelPassword->move(100, 440);
	//myLabelPassword->setText(QString::fromLocal8Bit("���룺"));

	//myTextLineId = new QLineEdit(this);
	//myTextLineId->move(140, 400);

	//myTextLinePassword = new QLineEdit(this);
	//myTextLinePassword->move(140, 440);
	//myTextLinePassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);

	/* Ҫʵ�ּ�ס������һ�̣�������Զ�����.ini�ļ� ���˺������뱣�����ļ���
	1���ٴα���Ӧ��ʵ��ȥ��
	2���ٴν�����򣬶�ȡ�����ļ�������������˺�������д������ 
	3�����������һ��д����˺�������ʾ�������
	4���ſ�������ȥ��*/
	//myCheckBox = new QCheckBox(this);    //�Ƿ��ס�˺�������
	//myCheckBox->setText(QString::fromLocal8Bit("��ס����"));
	//myCheckBox->move(100, 470);
	//connect(myCheckBox, &QCheckBox::stateChanged, this, [=](int stage) 
	//		{
	//			if (!myTextLineId->text().isEmpty()&&!myTextLinePassword->text().isEmpty())
	//			{
	//				QFile myFile("./IdAndPassword.ini");
	//				if ( list.isEmpty()|| !CheckIsExist( myTextLineId->text(), myTextLinePassword->text() ) )
	//				{
	//					myFile.open(QIODevice::ReadWrite | QIODevice::Append);  // (append)׷�ӻ��ߴ���
	//					QTextStream out(&myFile);
	//					out << myTextLineId->text() << ":" << myTextLinePassword->text() << "\n";
	//					IdAndPassword strData;
	//					strData.userId = myTextLineId->text();
	//					strData.Password = myTextLinePassword->text();
	//					list.append(strData);
	//				}
	//				myFile.close();
	//			}
	//		}
	//	   );

	////�������ļ����ж�ȡ
	//QFile myFile("./IdAndPassword.ini");
	//if (!myFile.open(QIODevice::ReadOnly))
	//{
	//	return;
	//}
	//QTextStream in(&myFile);

	//list.clear();   //����list�Ա�ʹ��list

	//while (!in.atEnd())
	//{
	//	QString oneLine = in.readLine();
	//	IDANDPASSWORD strData;
	//	QStringList myList = oneLine.split(":");
	//	strData.userId = myList.at(0);
	//	strData.Password = myList.at(1);
	//	list.append(strData);

	//}

	//if (!list.isEmpty())
	//{
	//	//myTextLineId->setText(list[list.count() - 1].userId);
	//	//myTextLineId->setText(list[list.count() - 1].Password);

	//	AssignmentIdValue( list[list.count() - 1].userId );
	//	AssignmentPasswordValue(list[list.count() - 1].Password);
	//}

	myLabelShowCurrentTime = new QLabel(this);
	myLabelShowCurrentTime->move(300, 560);

	QTime myTime = QTime::currentTime();
	QString myCurrentTime = myTime.toString("hh:mm::ss");
	myLabelShowCurrentTime->setText(myCurrentTime);

	myTimer = new QTimer(this);
	myTimer->start(1000);
	connect(myTimer, &QTimer::timeout,this,[=]()
	{
		QTime myTime = QTime::currentTime();
		QString myCurrentTime = myTime.toString("hh:mm::ss");
		myLabelShowCurrentTime->setText(myCurrentTime);
	}
	);
	
	connect(myButtonLogin, &QPushButton::pressed,this,&FaceLogin::Login);

	connect(myCloseWindowsButton, &QPushButton::pressed,this,[=]()
			{
				if (QMessageBox::Ok == QMessageBox::information(this, QString::fromLocal8Bit("�رյ�¼"),
					QString::fromLocal8Bit("�Ƿ�رմ���"), QMessageBox::Ok | QMessageBox::No))
				{
					this->close();
				}

			}
	       );

	connect(myMaxWindowsButton, &QPushButton::pressed,this,[=]() 
			{
				if (this->isMaximized())
				{
					this->showNormal();
				}
				else
					this->showMaximized();
			}
		   );

	connect(myMinWindowsButton, &QPushButton::pressed,this,[=]() 
			{
				this->showMinimized();
			}
		   );

}

//�����¼��ť�ۺ���
void FaceLogin::Login()
{  

	/****************************************************���� *******************/
	/****************************************************************************/
	heartPort("version 1.0.1");

	//����idLineEdit��passwordLineEdit���Ƿ񱻷�����ʷ���һ�μ�ס����ʱ�����ֵ

	//QMessageBox::information
	//(this, QString::fromLocal8Bit("�û�����������ʾ"),
	//	QString::fromLocal8Bit("�û�����%1�����룺%2").arg(myTextLineId->text().arg(myTextLinePassword->text())),
	//	QMessageBox::Ok | QMessageBox::No);
	QMessageBox::information
	    (
			this, QString::fromLocal8Bit("�û�����������ʾ"),
			QString::fromLocal8Bit("�û�����%1�����룺%2").arg(myIdLineEdit->myText()).arg(myPasswordLineEdit->myText()),
		    QMessageBox::Ok | QMessageBox::No
		);
	accept();  //����ǰ��������
}


void FaceLogin::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);                   //������¼�������Qwidget�в������ʱ���е�����
	QPoint myMousePositonBeforeMove = event->globalPos();
	QPoint myWidgetFramePositionTopLeftBeforeMove = this->geometry().topLeft();
	tempPoint = myMousePositonBeforeMove - myWidgetFramePositionTopLeftBeforeMove;

}

void FaceLogin::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
	QPoint NowmyMousePositon = event->globalPos();
	QPoint NowWidgetPosition = NowmyMousePositon - tempPoint;
	//    QPoint myWidgetmove=NowWidgetPosition-myWidgetFramePositionTopLeftBeforeMove;
	this->move(NowWidgetPosition);         
}


void FaceLogin::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
	tempPoint = QPoint();      //����tempQPoint
}

//��������
bool FaceLogin::CheckIsExist(const QString& key1, const QString& key2)
{
	foreach(IDANDPASSWORD value, list)
	{
		if ((value.userId == key1) && (value.Password == key1))
		{
			return true;
		}
	}
	return false;
}





//���˺����������ֵ

//void FaceLogin::AssignmentIdValue(const QString &text)
//{
//	myTextLineId->setText(text);
//}
//
//void FaceLogin::AssignmentPasswordValue(const QString &text)
//{
//	myTextLinePassword->setText(text);
//}



FaceLogin::~FaceLogin()
{

}

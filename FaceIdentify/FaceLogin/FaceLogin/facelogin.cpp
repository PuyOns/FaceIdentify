#include "facelogin.h"



FaceLogin::FaceLogin(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon(QIcon(":/image/logining.png"));
	setWindowTitle(QString::fromLocal8Bit("登录窗口"));
	
	QPixmap myPixmap(":/image/Pixmap.png");
	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	
	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);


	myButtonLogin = new QPushButton(this);
	myButtonLogin->setText(QString::fromLocal8Bit("登录"));
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

	//设置账号密码输入框
	myIdLineEdit = new LineEditWithIcon(":/image/person.png", this);
	myIdLineEdit->move(100, 400);

	myPasswordLineEdit = new LineEditWithIcon(":/image/passwd.png", this);
	myPasswordLineEdit->move(100, 450);
	myPasswordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);  //设置密码显示格式
	
	myCheckBox = new QCheckBox(this);    //是否记住账号与密码
	myCheckBox->setText(QString::fromLocal8Bit("记住密码"));
	myCheckBox->move(100, 498);

								//state是正数时表示已经把记住密码打钩了
	connect(myCheckBox, &QCheckBox::stateChanged, this, [=](int state)   
			{
				if (state)
				{ 		
					if (!myIdLineEdit->myText().isEmpty()&&!myPasswordLineEdit->myText().isEmpty())
					{
						QFile myFile("./IdAndPassword.ini");
						//查看链表里是否与输入的账号和密码相同
						if ( list.isEmpty()|| !CheckIsExist(myIdLineEdit->myText(), myPasswordLineEdit->myText()) )
						{
							myFile.open(QIODevice::ReadWrite | QIODevice::Append);  // (append)追加或者创建
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

	//对配置文件进行读取
	QFile myFile("./IdAndPassword.ini");
	if (!myFile.open(QIODevice::ReadOnly))
	{
		
		return;
	}
	QTextStream in(&myFile);

	list.clear();   //清零list以便使用list

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
		//给账号密码框设置历史最后一次记住密码时的值
		myIdLineEdit->setValue(list[list.count() - 1].userId);
		myPasswordLineEdit->setValue(list[list.count() - 1].Password);

	}
	
	myFile.close();

	//myLabelId = new QLabel(this);
	//myLabelId->move(100, 400);
	//myLabelId->setText(QString::fromLocal8Bit("账号："));

	//myLabelPassword = new QLabel(this);
	//myLabelPassword->move(100, 440);
	//myLabelPassword->setText(QString::fromLocal8Bit("密码："));

	//myTextLineId = new QLineEdit(this);
	//myTextLineId->move(140, 400);

	//myTextLinePassword = new QLineEdit(this);
	//myTextLinePassword->move(140, 440);
	//myTextLinePassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);

	/* 要实现记住密码那一刻，程序会自动生成.ini文件 将账号与密码保存在文件中
	1、再次保存应该实现去重
	2、再次进入程序，读取配置文件，并将里面的账号与密码写入链表 
	3、把链表最后一次写入的账号密码显示到输入框
	4、才可以做到去重*/
	//myCheckBox = new QCheckBox(this);    //是否记住账号与密码
	//myCheckBox->setText(QString::fromLocal8Bit("记住密码"));
	//myCheckBox->move(100, 470);
	//connect(myCheckBox, &QCheckBox::stateChanged, this, [=](int stage) 
	//		{
	//			if (!myTextLineId->text().isEmpty()&&!myTextLinePassword->text().isEmpty())
	//			{
	//				QFile myFile("./IdAndPassword.ini");
	//				if ( list.isEmpty()|| !CheckIsExist( myTextLineId->text(), myTextLinePassword->text() ) )
	//				{
	//					myFile.open(QIODevice::ReadWrite | QIODevice::Append);  // (append)追加或者创建
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

	////对配置文件进行读取
	//QFile myFile("./IdAndPassword.ini");
	//if (!myFile.open(QIODevice::ReadOnly))
	//{
	//	return;
	//}
	//QTextStream in(&myFile);

	//list.clear();   //清零list以便使用list

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
				if (QMessageBox::Ok == QMessageBox::information(this, QString::fromLocal8Bit("关闭登录"),
					QString::fromLocal8Bit("是否关闭窗口"), QMessageBox::Ok | QMessageBox::No))
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

//点击登录按钮槽函数
void FaceLogin::Login()
{  

	/****************************************************调试 *******************/
	/****************************************************************************/
	heartPort("version 1.0.1");

	//测试idLineEdit和passwordLineEdit中是否被放入历史最后一次记住密码时保存的值

	//QMessageBox::information
	//(this, QString::fromLocal8Bit("用户名和密码显示"),
	//	QString::fromLocal8Bit("用户名：%1，密码：%2").arg(myTextLineId->text().arg(myTextLinePassword->text())),
	//	QMessageBox::Ok | QMessageBox::No);
	QMessageBox::information
	    (
			this, QString::fromLocal8Bit("用户名和密码显示"),
			QString::fromLocal8Bit("用户名：%1，密码：%2").arg(myIdLineEdit->myText()).arg(myPasswordLineEdit->myText()),
		    QMessageBox::Ok | QMessageBox::No
		);
	accept();  //将当前窗口隐藏
}


void FaceLogin::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);                   //让鼠标事件具有在Qwidget中操作鼠标时具有的属性
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
	tempPoint = QPoint();      //清零tempQPoint
}

//遍历链表
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





//给账号密码框设置值

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

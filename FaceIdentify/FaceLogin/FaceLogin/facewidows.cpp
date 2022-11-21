#include "facewidows.h"

FaceWidows::FaceWidows(QWidget *parent)
	: QWidget(parent)
{

	isOpenCamera = false;
	isOpenCompareButton= false;
	isOpenFaceDiscernButton= false;

	setWindowIcon(QIcon(":/image/fxx.jpg"));
	setWindowTitle(QString::fromLocal8Bit("������"));
	QPixmap myPixmap(":/image/1280x720kkk.jpg");
	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);

	myCreateWindow();  //������ʾ

	connectSignalAndSlot();  //���Ӵ����źźͲ�
}

void FaceWidows::mousePressEvent(QMouseEvent *event)
{

	QWidget::mousePressEvent(event);                   //������¼�������Qwidget�в������ʱ���е�����
	QPoint myMousePositonBeforeMove = event->globalPos();
	QPoint myWidgetFramePositionTopLeftBeforeMove = this->geometry().topLeft();
	tempPoint = myMousePositonBeforeMove - myWidgetFramePositionTopLeftBeforeMove;

}

void FaceWidows::mouseMoveEvent(QMouseEvent *event)
{

	QWidget::mouseMoveEvent(event);
	QPoint NowmyMousePositon = event->globalPos();
	QPoint NowWidgetPosition = NowmyMousePositon - tempPoint;
	//    QPoint myWidgetmove=NowWidgetPosition-myWidgetFramePositionTopLeftBeforeMove;
	this->move(NowWidgetPosition);

}

void FaceWidows::mouseReleaseEvent(QMouseEvent *event)
{

	QWidget::mouseReleaseEvent(event);
	tempPoint = QPoint();      //����tempQPoint

}

void FaceWidows::myCreateWindow()
{

	//�����ڱ�����
	myWindowTitle = new Title(this);
	myWindowTitle->move(0, 0);

	//�����ڹ�����
	myWindowToolBar = new ToolBarOfFaceWindow(this);
	myWindowToolBar->move(0, 40);
	

	//��ʾͼƬ����
	myDisplayImage = new DisplayImage(this);
	myDisplayImage->move(0, 180);

	//������ʾ����
	myFunctionDisplay = new FunctionDisplayWindow(this);
	myFunctionDisplay->move(0, 540);

	//������״̬��
	myWindowStaticBar = new StaticBar(this);
	myWindowStaticBar->move(0, 680);

}

void FaceWidows::connectSignalAndSlot()
{

	//���ڱ������رա���С������󻯵��źŴ���
	connect(myWindowTitle,&Title::mySendWindowClose,this,[=]()
			{

				if (QMessageBox::Yes == QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),
					QString::fromLocal8Bit("�Ƿ��˳�ϵͳ"), QMessageBox::Yes| QMessageBox::No))
				{
					
					this->close();

				}

				else return;
		        
			}
		   );

	connect(myWindowTitle, &Title::mySendWindowShowMax, this, [=]()
			{

				if (this->isMaximized())
				{

					this->showNormal();
				}

				else
				{

					this->showMaximized();

				}
			}
		   );

	connect(myWindowTitle, &Title::mySendWindowShowMin, this, [=]()
			{

                //this->showMinimized();
				this->hide();

				//�����¼�����
				mySystemTrayIcon = new QSystemTrayIcon(this);
				QIcon myIcon = QIcon(":/image/fxx.jpg");
				mySystemTrayIcon->setIcon(myIcon);
				mySystemTrayIcon->setToolTip(QString::fromLocal8Bit("����ʶ��ϵͳ"));
				connect(mySystemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
					    this, SLOT(myActivatedSystemTrayIcon(QSystemTrayIcon::ActivationReason)));
				mySystemTrayIcon->show();

			}
		  );

	                          /*�����������ĸ���ť�źŴ���*/
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenCamera, this, &FaceWidows::myDealOpenCamera);
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenFaceDiscern, this, &FaceWidows::myDealOpenFaceDiscern);
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenFile, this, &FaceWidows::myDealOpenFile);
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenVideo, this, &FaceWidows::myDealOpenVideo);
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenCompare, this, &FaceWidows::myDealOpenCompare);

	                          /*������ʾ���źźͲ�*/
	connect(myFunctionDisplay, &FunctionDisplayWindow::sendStartRecording, this, &FaceWidows::dealStartRecording);
	connect(myFunctionDisplay, &FunctionDisplayWindow::sendStopRecording,this, &FaceWidows::dealStopRecording);
	connect(myFunctionDisplay, &FunctionDisplayWindow::sendEdgeDetection, this, &FaceWidows::dealEdgeDetection);
	connect(myFunctionDisplay, &FunctionDisplayWindow::sendPhotograph, this, &FaceWidows::dealPhotograph);

	/*���ܴ���ʵ���л�  ע�⣺��������ʱ���������ź����ӹ��ܴ��ڵĲۺ���ʱ���ۺ������빫�еأ�Ҫ��Ȼ���ܷ���*/
	/**���������ڰ�ť��������źţ�������ʵ�ֶ�Ӧ�Ĳۺ�������void FaceWidows::myDealOpenFile()����
	 **���ܴ����л�����ͨ�������������Ӧ�Ĳۺ��������ź�emit myDealChangeFunctionDisplayWindow(bool);
	 **���ܴ��ڲۺ���ʵ���л�����**/

	connect( this, &FaceWidows::myDealChangeFunctionDisplayWindow, myFunctionDisplay,
		     &FunctionDisplayWindow::myChangeFunctionDisplayWindow);

	           /*���ͱȶԽ���ͱȶ���ʱ��������ʾ��*/
	connect(this, SIGNAL(sendResult(const double&, const int&)), myFunctionDisplay, 
		    SLOT(ReceiveCompareResult(const double&, const int&)) );
	
}

void FaceWidows::myActivatedSystemTrayIcon(QSystemTrayIcon::ActivationReason myReason)
{

	switch (myReason)
	{

	case QSystemTrayIcon::Context :  //����Ҽ����
		break;

	case QSystemTrayIcon::DoubleClick : //���˫������

		//��������Ҫ��ʾ������������Ҫ���ء���֪��Ϊʲô��һ��дthis->show()���룬���������ã�
		//��������this->showNormal()˫�����̿�����ʾ Ȼ����show������
		this->show();
		mySystemTrayIcon->hide();
		break;

	}
}

//���������ť�������źŶ�Ӧ�ۺ������� 
//ʵ����Ƶ¼�Ƶ���ʾ���ܣ�¼���Ϊ��ʾ�ͱ�����Ƶ�����ҿ������ܴ��ڵĿ�ʼ¼�ơ�ֹͣ¼�ƵȰ�ť
void FaceWidows::myDealOpenCamera()
{

	if (!isOpenCamera)
	{

		isOpenCamera = true;
		isOpenFaceDiscernButton = true;
		emit myDealChangeFunctionDisplayWindow(false);  // �ù�����ʾ���ڿ����л���¼����Ƶҳ��
	    //QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("penCamera()�ź��Ѵ���"));

		if (myVideoCapture.isOpened())
		{

			myVideoCapture.release();  //�ر���Ƶ��

		}

		//��¼���ܣ�����ͷ��ʱ��Ĳ���Ϊ��myRate=1  cout<<myRate;��
		myRate = myVideoCapture.open(0);   

		if (myVideoCapture.isOpened())
		{

			//����������ͷ¼����Ƶ��������Ƶ��ʾ����������Ƶת����ͼƬ���ţ�֡���ﵽ10��������Ƶ

			//֡����һ���Ӵ���ͼƬ��֡��(һ֡��һ����ֹ�Ļ��棩
			//��ȡ֡������ȡ��Ƶÿ�벥�ż���ͼƬ������Ƶ�е�����ͼƬ��  
			//��ȡ֡����myRate = myVideoCapture.get(CV_CAP_PROP_FPS);

			//ֻҪ��֡�����õ�10���ϣ��Ϳ��Գ�Ϊ�����Ƶ
			myRate*= 25;    // ��Ƶ֡��:����������Ƶ���ŵ�֡���ͻ�ȡ������ͷ֡������
			//(cv::Size)������Ƶ�Ĵ��ڵĴ�С��[640x480],Ҳ������ͼ�����ͼƬ��С
			myVideoCapture >> myImageSet;     //����Ƶ��ת����ͼƬ��

			///******����Ƶ���ϲ���********/
			if (!myImageSet.empty())
			{

				myImage = mycvMatToQImage(myImageSet);
				myDisplayImage->myVideoDisplay(myImage);
				myTimer = new QTimer(this);
				//��ʱ��ÿ�δ�һ�δ���ͼƬ��Ϊ��1000/maRate���δ�һ��Ϊһ����
				myTimer->setInterval(1000/myRate);
				myTimer->start();
				connect(myTimer, &QTimer::timeout, this, &FaceWidows::nextmyImageSet);

			}

			myFunctionDisplay->isUsefulFunctionWindowButton(true);

		}
	}

	else
	{

		isOpenCamera = false;
		isOpenFaceDiscernButton = false;
		emit myDealChangeFunctionDisplayWindow(false);
		myVideoCapture.open(1);
		myFunctionDisplay->isUsefulFunctionWindowButton(false);
		QImage image(":/image/CameraWindow640x360.jpg");
		myDisplayImage->myVideoDisplay(image);

	}	
}

//�������Ƶ��ť�������źŶ�Ӧ�ۺ�������
void FaceWidows::myDealOpenVideo()
{

	isOpenCamera = false;
	isOpenFaceDiscernButton = true;
	emit myDealChangeFunctionDisplayWindow(false);
    //QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("OpenVideo()�ź��Ѵ���"));

	if (myVideoCapture.isOpened())
	{

		myVideoCapture.release();  //�ر���Ƶ��

	}

	QString myFilePath = QFileDialog::getOpenFileName(this, "Open video file",".", "video file(*.mp4;*.avi;*.flv )");
	//��QString����ͨ��ת��Ϊlocal8Bit��תΪdata���ݣ�dataΪcv��ʶ������
	myVideoCapture.open(myFilePath.toLocal8Bit().data());
	

	if (myVideoCapture.isOpened())
	{

		/****��ȡ֡������ȡ��Ƶÿ�벥�ż���ͼƬ������Ƶ�е�����ͼƬ�� 
		     ֡����һ���Ӵ���ͼƬ������(һ֡��һ����ֹ�Ļ��棩      ****/
		myRate = myVideoCapture.get(CV_CAP_PROP_FPS);
		//cout << myRate;
		myVideoCapture >> myImageSet;

		if (!myImageSet.empty())
		{
			
			//qt�ؼ�������ƵҪ��cv::Mat myImageSet;opencv�����ݼ�����ͼ��תΪQt��QImage����ſ��Բ��ų���Ƶ
			myImage = mycvMatToQImage(myImageSet);
			myDisplayImage->myVideoDisplay(myImage);
			//��ʱ��ÿһ����δ�һ�Σ�һ�봫25֡�� ����ÿ�δ�һ�δ���ͼƬ��Ϊ��1000/25
			myTimer = new QTimer(this);
			myTimer->setInterval(1000/myRate);
			myTimer->start();
			connect(myTimer, &QTimer::timeout, this, &FaceWidows::nextmyImageSet);

		}

		myFunctionDisplay->isUsefulFunctionWindowButton(true);

	}
}

//��Ƶ��תͼƬ���������ݼ�
void FaceWidows::nextmyImageSet()
{
	myVideoCapture >> myImageSet;

	if (!myImageSet.empty())
	{

		myDisplayImage->myVideoDisplay(myImage);

	}
	
}

//��myImageSet����ͼƬ��ΪQImage������ͼƬ
QImage FaceWidows::mycvMatToQImage(cv::Mat)
{

	QImage myMatToImage;

	if (myImageSet.channels()==3)  //��ɫͨ��
	{

		cv::cvtColor(myImageSet, myImageSet, CV_BGR2RGB);
		myMatToImage = QImage((const unsigned char*)(myImageSet.data), 
								myImageSet.cols, myImageSet.rows,
								myImageSet.cols*myImageSet.channels(),
								QImage::Format_RGB888);

	}

	else if (myImageSet.channels()==1)//��ɫͨ�� 

	{

		myMatToImage = QImage((const unsigned char*)(myImageSet.data), myImageSet.cols, myImageSet.rows,
			                   myImageSet.cols*myImageSet.channels(), QImage::Format_Indexed8);

	}

	else

	{
		myMatToImage = QImage((const unsigned char*)(myImageSet.data), myImageSet.cols, myImageSet.rows,
			                   myImageSet.cols*myImageSet.channels(), QImage::Format_RGB888); 
	}

	return myMatToImage;

}

//������ļ���ť�������źŶ�Ӧ�ۺ�������  ���ܴ�����ʾ�ԱȽ������ʱ
void FaceWidows::myDealOpenFile()
{

	emit myDealChangeFunctionDisplayWindow(false);
	/*QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("OpenFile()�ź��Ѵ���"));*/

	QString myFilePath = QFileDialog::getOpenFileName(this, "Open File",
		".", " file( *.gif;*.png; *.jpg; ALLFILE(*.*)");

	if (myFilePath.isEmpty())
	{

		return;

	}

	else
	{

		QImage image;
		image.load(myFilePath);
		myDisplayImage->myPictureShow(image);

		if (!image.load(myFilePath))
		{

			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�ļ�ѡ�����������ѡ��"));
			image.load(":/image/faceDescern640x360Winddow.jpg");
			myDisplayImage->myPictureShow(image);
			return;

		}

		else
		{	

			if(useThread1)
			{

				Feat1thread = new Feature1Thread(this, myFilePath);

				if (!Feat1thread->isRunning())
				{

					//�߳�1����ȡ��һ��ͼƬ������			
					Feat1thread->start();
					//getFeat1���߳�һ����
					connect(Feat1thread, &Feature1Thread::sendReast, this, &FaceWidows::getFeat1);
					useThread1 = false;
					return;

				}
			}

//			else if(Feat2thread = new Feature2Thread(this, myFilePath))
			else
			{

				Feat2thread = new Feature2Thread(this, myFilePath);
				Feat2thread->start();
				connect(Feat2thread, &Feature2Thread::sendReast, this, &FaceWidows::getFeat2);
				useThread1 = true;

			}

			isOpenCompareButton = true;
			CompareStartTime = QTime::currentTime();

		}
	}
}

//�������ͼƬ��ť����ʵʱ�����е�ͼƬ,ͼƬ�����������������ݳ�ȡ
//
void FaceWidows::myDealOpenFaceDiscern()
{

	emit myDealChangeFunctionDisplayWindow(false);
	/*QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("FaceDiscern()�ź��Ѵ���")); */

	myVideoCapture >> myImageSet;

	if (!myImageSet.empty())
	{
		mySiveImage = FaceWidows::mycvMatToQImage(myImageSet);
		cv::Mat myGrayImage;
		//ʵ�ֱ���ͼƬ����
		mySiveImage.save("cuttedImage.jpg");

	}

	if (isOpenFaceDiscernButton)
	{

		//�߳�2����ȡ�ڶ���ͼƬ������
		Feat2thread = new Feature2Thread(this, "cuttedImage.jpg");

		if (!Feat2thread->isRunning())
		{

			Feat2thread->start();
			useThread1 = true;

		}

		connect(Feat2thread, &Feature2Thread::sendReast, this, &FaceWidows::getFeat2);
		CompareStartTime = QTime::currentTime();
		isOpenCompareButton = true;

	}
}

void FaceWidows::myDealOpenCompare()
{
	
	if (isOpenCompareButton&&isFindFace1&&isFindFace2)
	{

			emit myDealChangeFunctionDisplayWindow(true);
			myFunctionDisplay->isUsefulFunctionWindowButton(false);
			//�߳�3���Ƚ�ͼƬ
			FeatCompare = new feat1Compfeat2(this, f1, f2);

			if (!FeatCompare->isRunning())
			{

				FeatCompare->start();

			}

			connect(FeatCompare, &feat1Compfeat2::sendReast, this, &FaceWidows::getReast);
			isFindFace1 = false;
			isFindFace2 = false;
	
	}

	else
	{
		if (QMessageBox::Yes == QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����ͼƬ��������������������һ���������³�ȡ��"),
			QMessageBox::Yes | QMessageBox::No))
			emit myDealChangeFunctionDisplayWindow(false);
		else
			return;
	}
}

void FaceWidows::getFeat1(float *feat1,bool val)
{

	f1 = feat1;
	isFindFace1 = val;
	Feat1thread->iiSeetaFace.~SeetaFace();
	Feat1thread->wait();
	Feat1thread->quit();
	
}

void FaceWidows::getFeat2(float *feat2,bool val)
{
	
	f2 = feat2;
	isFindFace2 = val;
	Feat2thread->iiSeetaFace.~SeetaFace();
	Feat2thread->wait();
	Feat2thread->quit();
	
}

void FaceWidows::getReast(double *reast)
{

	if (*reast == -1)
	{

		myDealOpenFaceDiscern();

	}

	else
	{

		const double result = *reast;
		CompareOverTime = QTime::currentTime();
		//���㿪ʼ������ʱ��/s
		int interval = CompareStartTime.msecsTo(CompareOverTime) / 1000;
		//���ͱȶԽ���ͱȶ���ʱ��������ʾ��
		connect(this, SIGNAL(sendResult(const double&, const int&)), myFunctionDisplay, SLOT(ReceiveCompareResult(const double&, const int&)));
		emit sendResult(result, interval);  //���ͱȶԽ���ͱȶ�ʱ�� 

	}

	FeatCompare->iiSeetaFace.~SeetaFace();
	FeatCompare->wait();
	FeatCompare->quit(); 

	delete f1;
	delete f2;
	delete Feat1thread;   
	delete Feat2thread;
	delete FeatCompare;

	isOpenCompareButton = false;

}


void FaceWidows::dealStartRecording()  //��ʼ¼��
{

    /*QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʼ¼��"));*/
	
	myVideoWrite = new VideoWriter();
	myVideoRecord=new videoRecord(this, myImageSet, myVideoCapture, myVideoWrite);

	if (!myVideoRecord->isRunning())
	{

		myVideoRecord->start();
		myFunctionDisplay->myButtonStopRecording->setDisabled(false);
		myFunctionDisplay->myButtonStartRecording->setDisabled(true);

	}
}

void FaceWidows::dealStopRecording()  //ֹͣ¼��
{

	/*QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("ֹͣ¼��"));*/

	if (myVideoRecord->isRunning())
	{

		connect(this, &FaceWidows::stopVideoWrite, myVideoRecord, &videoRecord::stopVideowrite);
		emit stopVideoWrite(true);
		myVideoRecord->wait();
		myVideoRecord->quit();
		delete myVideoRecord;
		//delete myVideoWrite;
		//@brief(ժҪ�����ͣ����ر���Ƶ�����������Զ���������������destructor
		myVideoWrite->release();
		myFunctionDisplay->myButtonStopRecording->setDisabled(true);
		myFunctionDisplay->myButtonStartRecording->setDisabled(false);

	}
}

void FaceWidows::dealEdgeDetection()  //��Ե���  ������ͼƬת���ɺڰ�ɫ��ͼƬ ����ͼƬ����ɫ�Ŀɼ�����
{

    //QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��Ե���"));
	
	cv::Mat myGrayImage;
	//���Ŵ��ڵ�ͼƬ�Ҷȼ�⣬�����Ǳ����ͼƬ�Ҷȼ�� ��Ϊinputarray Image��myImageSet(��ǰͼƬ����ͼƬ��
	//Ҫ��Ᵽ���ͼƬ����dealPhotograph(����)����ʵ��
    //	cv::Canny(myImageSet, myGrayImage, 0, 30, 3);  //ͼƬ�Ҷȼ�⴦���� ��5�������̶�����Ĭ��ֵ
	cv::Canny(myImageSet, myGrayImage, 0, 30);
    //	cv::namedWindow("grayScaleWindow");  
	cv::imshow("grayScaleWindow", myGrayImage);    //�ԻҶ�ͼƬ������ʾ

	//����Ҷ�ͼƬ
	if (QMessageBox::Yes == QMessageBox::information(this, QString::fromLocal8Bit("�Ҷ�ͼƬ"),
		QString::fromLocal8Bit("�Ƿ񱣴�Ҷ�ͼƬ"), QMessageBox::Yes | QMessageBox::No))
	{

		static int i = 1;
		string fileName = "grayImage" + to_string(i++);
		imwrite("./sived grayImage/" + fileName + ".jpg", myGrayImage);

	}
}

    //��QImageתΪopencv��cv::mat���� ��ʵʱ���ջ򱣴��ͼƬ��ת����ʽ���ٻҶȼ��
/***cv::Mat FaceWidows::myQImageToCvMat(QImage &image, int format)
	{

		  cv::Mat cvImage;
		  cvImage=cv::Mat(image.height(), image.width(), format, image.bits(), image.bytesPerLine());
		  return cvImage;

		  myMatToImage = QImage((const unsigned char*)(myImageSet.data), myImageSet.cols, myImageSet.rows,
		  myImageSet.cols*myImageSet.channels(), QImage::Format_RGB888);

	}***/

void FaceWidows::dealPhotograph()  //���� û��ʵ�����ջҶȼ��********************************
{

    //QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("����"));

	myVideoCapture >> myImageSet;
	if (!myImageSet.empty())
	{
        //QImage mySiveImage = FaceWidows::mycvMatToQImage(myImageSet);
		mySiveImage = FaceWidows::mycvMatToQImage(myImageSet);
		cv::Mat myGrayImage;
		myDisplayImage->myPictureShow(mySiveImage);
		//ʵ�ֱ���ͼƬ����
		mySiveImage.save("sived picture/sivedImage.jpg");

	}	
}

FaceWidows::~FaceWidows()
{

}

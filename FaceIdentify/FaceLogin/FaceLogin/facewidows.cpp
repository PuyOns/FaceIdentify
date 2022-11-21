#include "facewidows.h"

FaceWidows::FaceWidows(QWidget *parent)
	: QWidget(parent)
{

	isOpenCamera = false;
	isOpenCompareButton= false;
	isOpenFaceDiscernButton= false;

	setWindowIcon(QIcon(":/image/fxx.jpg"));
	setWindowTitle(QString::fromLocal8Bit("主窗口"));
	QPixmap myPixmap(":/image/1280x720kkk.jpg");
	this->setMaximumSize(QSize(myPixmap.size()));
	this->setMinimumSize(QSize(myPixmap.size()));
	setWindowFlag(Qt::FramelessWindowHint);
	setAutoFillBackground(true);

	QPalette myPalette;
	myPalette.setBrush(QPalette::Window, QBrush(myPixmap));
	this->setPalette(myPalette);

	myCreateWindow();  //窗口显示

	connectSignalAndSlot();  //连接窗口信号和槽
}

void FaceWidows::mousePressEvent(QMouseEvent *event)
{

	QWidget::mousePressEvent(event);                   //让鼠标事件具有在Qwidget中操作鼠标时具有的属性
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
	tempPoint = QPoint();      //清零tempQPoint

}

void FaceWidows::myCreateWindow()
{

	//主窗口标题栏
	myWindowTitle = new Title(this);
	myWindowTitle->move(0, 0);

	//主窗口工具栏
	myWindowToolBar = new ToolBarOfFaceWindow(this);
	myWindowToolBar->move(0, 40);
	

	//显示图片窗口
	myDisplayImage = new DisplayImage(this);
	myDisplayImage->move(0, 180);

	//功能显示窗口
	myFunctionDisplay = new FunctionDisplayWindow(this);
	myFunctionDisplay->move(0, 540);

	//主窗口状态栏
	myWindowStaticBar = new StaticBar(this);
	myWindowStaticBar->move(0, 680);

}

void FaceWidows::connectSignalAndSlot()
{

	//窗口标题栏关闭、最小化、最大化的信号处理
	connect(myWindowTitle,&Title::mySendWindowClose,this,[=]()
			{

				if (QMessageBox::Yes == QMessageBox::information(this, QString::fromLocal8Bit("提示"),
					QString::fromLocal8Bit("是否退出系统"), QMessageBox::Yes| QMessageBox::No))
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

				//托盘事件处理
				mySystemTrayIcon = new QSystemTrayIcon(this);
				QIcon myIcon = QIcon(":/image/fxx.jpg");
				mySystemTrayIcon->setIcon(myIcon);
				mySystemTrayIcon->setToolTip(QString::fromLocal8Bit("人脸识别系统"));
				connect(mySystemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
					    this, SLOT(myActivatedSystemTrayIcon(QSystemTrayIcon::ActivationReason)));
				mySystemTrayIcon->show();

			}
		  );

	                          /*工具栏窗口四个按钮信号处理*/
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenCamera, this, &FaceWidows::myDealOpenCamera);
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenFaceDiscern, this, &FaceWidows::myDealOpenFaceDiscern);
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenFile, this, &FaceWidows::myDealOpenFile);
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenVideo, this, &FaceWidows::myDealOpenVideo);
	connect(myWindowToolBar, &ToolBarOfFaceWindow::mySendOpenCompare, this, &FaceWidows::myDealOpenCompare);

	                          /*功能显示类信号和槽*/
	connect(myFunctionDisplay, &FunctionDisplayWindow::sendStartRecording, this, &FaceWidows::dealStartRecording);
	connect(myFunctionDisplay, &FunctionDisplayWindow::sendStopRecording,this, &FaceWidows::dealStopRecording);
	connect(myFunctionDisplay, &FunctionDisplayWindow::sendEdgeDetection, this, &FaceWidows::dealEdgeDetection);
	connect(myFunctionDisplay, &FunctionDisplayWindow::sendPhotograph, this, &FaceWidows::dealPhotograph);

	/*功能窗口实现切换  注意：在主窗口时，主窗口信号连接功能窗口的槽函数时，槽函数必须公有地，要不然不能访问*/
	/**工具栏窗口按钮点击发出信号，主窗口实现对应的槽函数（例void FaceWidows::myDealOpenFile()），
	 **功能窗口切换功能通过主窗口这个对应的槽函数发送信号emit myDealChangeFunctionDisplayWindow(bool);
	 **功能窗口槽函数实现切换窗口**/

	connect( this, &FaceWidows::myDealChangeFunctionDisplayWindow, myFunctionDisplay,
		     &FunctionDisplayWindow::myChangeFunctionDisplayWindow);

	           /*发送比对结果和比对用时到功能显示类*/
	connect(this, SIGNAL(sendResult(const double&, const int&)), myFunctionDisplay, 
		    SLOT(ReceiveCompareResult(const double&, const int&)) );
	
}

void FaceWidows::myActivatedSystemTrayIcon(QSystemTrayIcon::ActivationReason myReason)
{

	switch (myReason)
	{

	case QSystemTrayIcon::Context :  //鼠标右键点击
		break;

	case QSystemTrayIcon::DoubleClick : //鼠标双击托盘

		//主界面需要显示出来，托盘需要隐藏。不知道为什么第一次写this->show()代码，点托盘无用；
		//试着用了this->showNormal()双击托盘可以显示 然后用show正常了
		this->show();
		mySystemTrayIcon->hide();
		break;

	}
}

//点击打开摄像按钮发出的信号对应槽函数处理 
//实现视频录制的显示功能（录像分为显示和保存视频）并且开启功能窗口的开始录制、停止录制等按钮
void FaceWidows::myDealOpenCamera()
{

	if (!isOpenCamera)
	{

		isOpenCamera = true;
		isOpenFaceDiscernButton = true;
		emit myDealChangeFunctionDisplayWindow(false);  // 让功能显示窗口可以切换到录制视频页面
	    //QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("penCamera()信号已处理"));

		if (myVideoCapture.isOpened())
		{

			myVideoCapture.release();  //关闭视频集

		}

		//打开录像功能（摄像头这时候的参数为：myRate=1  cout<<myRate;）
		myRate = myVideoCapture.open(0);   

		if (myVideoCapture.isOpened())
		{

			//无论是摄像头录制视频或者是视频显示，都是由视频转换到图片播放，帧数达到10以上是视频

			//帧数：一秒钟传输图片的帧数(一帧：一幅静止的画面）
			//获取帧数：获取视频每秒播放几张图片（或视频中的连续图片）  
			//获取帧数：myRate = myVideoCapture.get(CV_CAP_PROP_FPS);

			//只要把帧数设置到10以上，就可以成为真的视频
			myRate*= 25;    // 视频帧数:根据正常视频播放的帧数和获取的摄像头帧数设置
			//(cv::Size)播放视频的窗口的大小是[640x480],也是摄像图摄像的图片大小
			myVideoCapture >> myImageSet;     //把视频流转换成图片流

			///******让视频不断播放********/
			if (!myImageSet.empty())
			{

				myImage = mycvMatToQImage(myImageSet);
				myDisplayImage->myVideoDisplay(myImage);
				myTimer = new QTimer(this);
				//定时器每滴答一次传的图片数为：1000/maRate，滴答一次为一毫秒
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

//点击打开视频按钮发出的信号对应槽函数处理
void FaceWidows::myDealOpenVideo()
{

	isOpenCamera = false;
	isOpenFaceDiscernButton = true;
	emit myDealChangeFunctionDisplayWindow(false);
    //QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("OpenVideo()信号已处理"));

	if (myVideoCapture.isOpened())
	{

		myVideoCapture.release();  //关闭视频集

	}

	QString myFilePath = QFileDialog::getOpenFileName(this, "Open video file",".", "video file(*.mp4;*.avi;*.flv )");
	//将QString数据通过转换为local8Bit再转为data数据，data为cv可识别类型
	myVideoCapture.open(myFilePath.toLocal8Bit().data());
	

	if (myVideoCapture.isOpened())
	{

		/****获取帧数：获取视频每秒播放几张图片（或视频中的连续图片） 
		     帧数：一秒钟传输图片的数量(一帧：一幅静止的画面）      ****/
		myRate = myVideoCapture.get(CV_CAP_PROP_FPS);
		//cout << myRate;
		myVideoCapture >> myImageSet;

		if (!myImageSet.empty())
		{
			
			//qt控件播放视频要把cv::Mat myImageSet;opencv的数据集或者图像集转为Qt的QImage对象才可以播放成视频
			myImage = mycvMatToQImage(myImageSet);
			myDisplayImage->myVideoDisplay(myImage);
			//定时器每一毫秒滴答一次，一秒传25帧数 所以每滴答一次传的图片数为：1000/25
			myTimer = new QTimer(this);
			myTimer->setInterval(1000/myRate);
			myTimer->start();
			connect(myTimer, &QTimer::timeout, this, &FaceWidows::nextmyImageSet);

		}

		myFunctionDisplay->isUsefulFunctionWindowButton(true);

	}
}

//视频集转图片集或者数据集
void FaceWidows::nextmyImageSet()
{
	myVideoCapture >> myImageSet;

	if (!myImageSet.empty())
	{

		myDisplayImage->myVideoDisplay(myImage);

	}
	
}

//把myImageSet数据图片变为QImage的数据图片
QImage FaceWidows::mycvMatToQImage(cv::Mat)
{

	QImage myMatToImage;

	if (myImageSet.channels()==3)  //彩色通道
	{

		cv::cvtColor(myImageSet, myImageSet, CV_BGR2RGB);
		myMatToImage = QImage((const unsigned char*)(myImageSet.data), 
								myImageSet.cols, myImageSet.rows,
								myImageSet.cols*myImageSet.channels(),
								QImage::Format_RGB888);

	}

	else if (myImageSet.channels()==1)//灰色通道 

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

//点击打开文件按钮发出的信号对应槽函数处理  功能窗口显示对比结果和用时
void FaceWidows::myDealOpenFile()
{

	emit myDealChangeFunctionDisplayWindow(false);
	/*QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("OpenFile()信号已处理"));*/

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

			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件选择错误，请重新选择！"));
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

					//线程1：抽取第一张图片特征点			
					Feat1thread->start();
					//getFeat1后线程一结束
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

//点击保存图片按钮保存实时摄像中的图片,图片用来人脸特征点数据抽取
//
void FaceWidows::myDealOpenFaceDiscern()
{

	emit myDealChangeFunctionDisplayWindow(false);
	/*QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("FaceDiscern()信号已处理")); */

	myVideoCapture >> myImageSet;

	if (!myImageSet.empty())
	{
		mySiveImage = FaceWidows::mycvMatToQImage(myImageSet);
		cv::Mat myGrayImage;
		//实现保存图片功能
		mySiveImage.save("cuttedImage.jpg");

	}

	if (isOpenFaceDiscernButton)
	{

		//线程2：抽取第二张图片特征点
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
			//线程3：比较图片
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
		if (QMessageBox::Yes == QMessageBox::information(this, QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("两张图片的人物特征点其中至少一张有误，重新抽取？"),
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
		//计算开始到结束时间/s
		int interval = CompareStartTime.msecsTo(CompareOverTime) / 1000;
		//发送比对结果和比对用时到功能显示类
		connect(this, SIGNAL(sendResult(const double&, const int&)), myFunctionDisplay, SLOT(ReceiveCompareResult(const double&, const int&)));
		emit sendResult(result, interval);  //发送比对结果和比对时间 

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


void FaceWidows::dealStartRecording()  //开始录制
{

    /*QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("开始录制"));*/
	
	myVideoWrite = new VideoWriter();
	myVideoRecord=new videoRecord(this, myImageSet, myVideoCapture, myVideoWrite);

	if (!myVideoRecord->isRunning())
	{

		myVideoRecord->start();
		myFunctionDisplay->myButtonStopRecording->setDisabled(false);
		myFunctionDisplay->myButtonStartRecording->setDisabled(true);

	}
}

void FaceWidows::dealStopRecording()  //停止录制
{

	/*QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("停止录制"));*/

	if (myVideoRecord->isRunning())
	{

		connect(this, &FaceWidows::stopVideoWrite, myVideoRecord, &videoRecord::stopVideowrite);
		emit stopVideoWrite(true);
		myVideoRecord->wait();
		myVideoRecord->quit();
		delete myVideoRecord;
		//delete myVideoWrite;
		//@brief(摘要：解释）：关闭视频编码器，并自动调用其析构函数destructor
		myVideoWrite->release();
		myFunctionDisplay->myButtonStopRecording->setDisabled(true);
		myFunctionDisplay->myButtonStartRecording->setDisabled(false);

	}
}

void FaceWidows::dealEdgeDetection()  //边缘检测  将正常图片转换成黑白色的图片 保留图片除颜色的可见属性
{

    //QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("边缘检测"));
	
	cv::Mat myGrayImage;
	//播放窗口的图片灰度检测，而不是保存的图片灰度检测 因为inputarray Image是myImageSet(当前图片流的图片）
	//要检测保存的图片，在dealPhotograph(拍照)里面实现
    //	cv::Canny(myImageSet, myGrayImage, 0, 30, 3);  //图片灰度检测处理保存 第5个参数固定且是默认值
	cv::Canny(myImageSet, myGrayImage, 0, 30);
    //	cv::namedWindow("grayScaleWindow");  
	cv::imshow("grayScaleWindow", myGrayImage);    //对灰度图片进行显示

	//保存灰度图片
	if (QMessageBox::Yes == QMessageBox::information(this, QString::fromLocal8Bit("灰度图片"),
		QString::fromLocal8Bit("是否保存灰度图片"), QMessageBox::Yes | QMessageBox::No))
	{

		static int i = 1;
		string fileName = "grayImage" + to_string(i++);
		imwrite("./sived grayImage/" + fileName + ".jpg", myGrayImage);

	}
}

    //将QImage转为opencv的cv::mat类型 对实时拍照或保存的图片先转换格式，再灰度检测
/***cv::Mat FaceWidows::myQImageToCvMat(QImage &image, int format)
	{

		  cv::Mat cvImage;
		  cvImage=cv::Mat(image.height(), image.width(), format, image.bits(), image.bytesPerLine());
		  return cvImage;

		  myMatToImage = QImage((const unsigned char*)(myImageSet.data), myImageSet.cols, myImageSet.rows,
		  myImageSet.cols*myImageSet.channels(), QImage::Format_RGB888);

	}***/

void FaceWidows::dealPhotograph()  //拍照 没有实现拍照灰度检测********************************
{

    //QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("拍照"));

	myVideoCapture >> myImageSet;
	if (!myImageSet.empty())
	{
        //QImage mySiveImage = FaceWidows::mycvMatToQImage(myImageSet);
		mySiveImage = FaceWidows::mycvMatToQImage(myImageSet);
		cv::Mat myGrayImage;
		myDisplayImage->myPictureShow(mySiveImage);
		//实现保存图片功能
		mySiveImage.save("sived picture/sivedImage.jpg");

	}	
}

FaceWidows::~FaceWidows()
{

}

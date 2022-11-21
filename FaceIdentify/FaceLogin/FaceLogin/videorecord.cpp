#include "videorecord.h"

videoRecord::videoRecord(QObject *parent, Mat &ImageSet, VideoCapture &VideoCapture, VideoWriter *VideoWrite)
	: QThread(parent), myImageSet(ImageSet), myVideoCapture(VideoCapture), myVideoWrite(VideoWrite)
{

}

videoRecord::~videoRecord()
{

}

void videoRecord::run()
{
	//摄像头：图片：640*480 帧数设置为:24  录制的视频帧数测试：30 根据录制时间算
	//视频：1920*1080 帧数：25
	Size cameraSize(640, 480);
	//cout<< fps <<"\n";
	//每帧图像大小
	Size videoSize(myVideoCapture.get(CAP_PROP_FRAME_WIDTH),myVideoCapture.get(CAP_PROP_FRAME_HEIGHT));
	//cout << videoSize;
	if (videoSize == cameraSize)  //保存摄像头的视频：一定要根据摄像头的视频窗口大小来设置，要不然保存不了！！！
	{
		static int i = 1;

	/**总结：
		   能否录制视频成功:1、摄像头实时视频窗口大小;2、帧数。其中1是决定性因素（帧数只要不为0）
		   录制摄像头的视频播放是否卡顿：1、视频窗口大小;2、 视频的帧数;3、 视频的编码。

		先设置，录制摄像头视频，再播放，打印帧数，再调，不论怎么设置帧数，
		      但是发现录制的播放的时候视频还很卡，那就是视频编码格式有问题****/
		double fps = 25;  
		string fileName = "camera" + to_string(i++);
		//本电脑摄像图视频录制编码可用：('M', 'J', 'P', 'G') 
		//('P', 'L', 'M', '1') 打印窗口：audio video interleaved(音频视频交错),不可用
		//('D', 'I', 'V', '3') ('M', 'P', '4', '2')('D', 'I', 'V', 'X') ('F', 'L', 'V', '1') 视频卡顿
		//('U', '2', '6', '3')需要固定摄像窗口大小或者视频大小:128*96 176*44 352*288 704*576 1408*1156 Try H 263+
		//('I', '2', '6', '3') 打印窗口：encode not be found(没有发现此编码器） 

		myVideoWrite->open("./sived videos/" + fileName + ".avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, videoSize, true);
	}
	else  //保存播放的视频
	{
		double fps = myVideoCapture.get(CAP_PROP_FPS);  //帧数
		static int i = 1;
		string fileName = "video" + to_string(i++);
		myVideoWrite->open("./sived videos/" + fileName + ".avi", CV_FOURCC('M', 'P', '4', '2'), fps, videoSize, true);
		//编码器窗口选择编码器
		//	myVideoWrite.open("./sived videos/" + fileName + ".avi", -1, fps, videoSize, true);

		//myVideoWrite.open("./sived videos/" + fileName + ".avi", cv::VideoWriter::fourcc('P', 'I', 'M', '1'),
		//	myVideoCapture.get(CV_CAP_PROP_FPS/10), cv::Size(myImageSet.cols, myImageSet.rows), true);
	}

	    isStopWrite = false;

   //不断把图像集写入视频集  
	//导致错误：线程不能结束，因为线程是一个死循环
	
		while (!isStopWrite)
		{
			myVideoWrite->write(myImageSet);
		}
	
}

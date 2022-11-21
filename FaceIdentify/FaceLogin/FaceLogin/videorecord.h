#include <QThread>
#include <opencv2/opencv.hpp>

#ifndef VIDEORECORD_H
#define VIDEORECORD_H

using namespace cv;
using namespace std;
//线程4：用来录制视频
class videoRecord : public QThread
{
	Q_OBJECT

public:
	videoRecord(QObject *parent, Mat &ImageSet, VideoCapture &VideoCapture, VideoWriter *VideoWrite);
	cv::Mat myImageSet;  //opencv的数据集
	cv::VideoCapture myVideoCapture; //opencv的视频集
	cv::VideoWriter *myVideoWrite; //制作视频
	~videoRecord();
	void run();
public slots:
void stopVideowrite(bool value) { isStopWrite = value; };

private:
	bool isStopWrite;
};

#endif // VIDEORECORD_H

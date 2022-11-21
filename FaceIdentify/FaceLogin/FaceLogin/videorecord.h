#include <QThread>
#include <opencv2/opencv.hpp>

#ifndef VIDEORECORD_H
#define VIDEORECORD_H

using namespace cv;
using namespace std;
//�߳�4������¼����Ƶ
class videoRecord : public QThread
{
	Q_OBJECT

public:
	videoRecord(QObject *parent, Mat &ImageSet, VideoCapture &VideoCapture, VideoWriter *VideoWrite);
	cv::Mat myImageSet;  //opencv�����ݼ�
	cv::VideoCapture myVideoCapture; //opencv����Ƶ��
	cv::VideoWriter *myVideoWrite; //������Ƶ
	~videoRecord();
	void run();
public slots:
void stopVideowrite(bool value) { isStopWrite = value; };

private:
	bool isStopWrite;
};

#endif // VIDEORECORD_H

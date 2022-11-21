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
	//����ͷ��ͼƬ��640*480 ֡������Ϊ:24  ¼�Ƶ���Ƶ֡�����ԣ�30 ����¼��ʱ����
	//��Ƶ��1920*1080 ֡����25
	Size cameraSize(640, 480);
	//cout<< fps <<"\n";
	//ÿ֡ͼ���С
	Size videoSize(myVideoCapture.get(CAP_PROP_FRAME_WIDTH),myVideoCapture.get(CAP_PROP_FRAME_HEIGHT));
	//cout << videoSize;
	if (videoSize == cameraSize)  //��������ͷ����Ƶ��һ��Ҫ��������ͷ����Ƶ���ڴ�С�����ã�Ҫ��Ȼ���治�ˣ�����
	{
		static int i = 1;

	/**�ܽ᣺
		   �ܷ�¼����Ƶ�ɹ�:1������ͷʵʱ��Ƶ���ڴ�С;2��֡��������1�Ǿ��������أ�֡��ֻҪ��Ϊ0��
		   ¼������ͷ����Ƶ�����Ƿ񿨶٣�1����Ƶ���ڴ�С;2�� ��Ƶ��֡��;3�� ��Ƶ�ı��롣

		�����ã�¼������ͷ��Ƶ���ٲ��ţ���ӡ֡�����ٵ���������ô����֡����
		      ���Ƿ���¼�ƵĲ��ŵ�ʱ����Ƶ���ܿ����Ǿ�����Ƶ�����ʽ������****/
		double fps = 25;  
		string fileName = "camera" + to_string(i++);
		//����������ͼ��Ƶ¼�Ʊ�����ã�('M', 'J', 'P', 'G') 
		//('P', 'L', 'M', '1') ��ӡ���ڣ�audio video interleaved(��Ƶ��Ƶ����),������
		//('D', 'I', 'V', '3') ('M', 'P', '4', '2')('D', 'I', 'V', 'X') ('F', 'L', 'V', '1') ��Ƶ����
		//('U', '2', '6', '3')��Ҫ�̶����񴰿ڴ�С������Ƶ��С:128*96 176*44 352*288 704*576 1408*1156 Try H 263+
		//('I', '2', '6', '3') ��ӡ���ڣ�encode not be found(û�з��ִ˱������� 

		myVideoWrite->open("./sived videos/" + fileName + ".avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, videoSize, true);
	}
	else  //���沥�ŵ���Ƶ
	{
		double fps = myVideoCapture.get(CAP_PROP_FPS);  //֡��
		static int i = 1;
		string fileName = "video" + to_string(i++);
		myVideoWrite->open("./sived videos/" + fileName + ".avi", CV_FOURCC('M', 'P', '4', '2'), fps, videoSize, true);
		//����������ѡ�������
		//	myVideoWrite.open("./sived videos/" + fileName + ".avi", -1, fps, videoSize, true);

		//myVideoWrite.open("./sived videos/" + fileName + ".avi", cv::VideoWriter::fourcc('P', 'I', 'M', '1'),
		//	myVideoCapture.get(CV_CAP_PROP_FPS/10), cv::Size(myImageSet.cols, myImageSet.rows), true);
	}

	    isStopWrite = false;

   //���ϰ�ͼ��д����Ƶ��  
	//���´����̲߳��ܽ�������Ϊ�߳���һ����ѭ��
	
		while (!isStopWrite)
		{
			myVideoWrite->write(myImageSet);
		}
	
}

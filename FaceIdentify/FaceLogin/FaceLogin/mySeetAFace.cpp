#include"mySeetAFace.h"


mySeetAFace::mySeetAFace(const char *model_name)  //��һ��ģ������
	:seeta::FaceDetection(model_name)
{
	this->SetMinFaceSize(40);
	this->SetScoreThresh(2.f);   //��С����
	this->SetImagePyramidScaleFactor(0.8f);  //�տ�ʼ�����ƶȣ�Ԥ��ֵ
	this->SetWindowStep(4, 4);
}

SeetaFace::SeetaFace():
	             myseetaface(new mySeetAFace("model/seeta_fd_frontal_v1.0.bin")),
                 point_detector(new FaceAlignment("model/seeta_fa_v1.1.bin")),
                 face_recognizer_1(new FaceIdentification("model/seeta_fr_v1.0.bin"))
                // ,face_recognizer_2(new FaceIdentification("model/seeta_fr_v1.0.bin"))
{

}

//����ж��������������һ�ţ����������뻺����feature������true
//���û������������false
bool SeetaFace::myGetFeature_1(string fileName, float* feature) //��ȡ����������feat��
{

	const char *imagePath = fileName.c_str();
	IplImage *img_grayscale = cvLoadImage(imagePath, 0);

	IplImage *img_color = cvLoadImage(imagePath, 2);  /* ?, color */
	if ((img_color == NULL) || (img_grayscale == NULL))
	{
		return false;
	}

	int pts_num = 5;
	int im_width = img_grayscale->width;
	int im_height = img_grayscale->height;
	unsigned char* data = new unsigned char[im_width * im_height];
	unsigned char* data_ptr = data;
	unsigned char* image_data_ptr = (unsigned char*)img_grayscale->imageData;
	int h = 0;
	for (h = 0; h < im_height; h++) {
		memcpy(data_ptr, image_data_ptr, im_width);
		data_ptr += im_width;
		image_data_ptr += img_grayscale->widthStep;
	}

	seeta::ImageData image_data(img_grayscale->width, img_grayscale->height, 1);
	image_data.data = data;

	// Detect faces
	vector<seeta::FaceInfo> faces = this->myseetaface->Detect(image_data);
	int32_t face_num = static_cast<int32_t>(faces.size());

	if (face_num == 0)
	{
		delete[]data;
		cvReleaseImage(&img_grayscale);
		cvReleaseImage(&img_color);
		return false;
	}

	// Detect 5 facial landmarks
	seeta::FacialLandmark points[5];
	bool isMark = point_detector->PointDetectLandmarks(image_data, faces[0], points);
	if (!isMark)
		return false;

	//// Visualize the results
	//cvRectangle(img_color, cvPoint(faces[0].bbox.x, faces[0].bbox.y), cvPoint(faces[0].bbox.x + faces[0].bbox.width - 1, faces[0].bbox.y + faces[0].bbox.height - 1), CV_RGB(255, 0, 0));
	//for (int i = 0; i<pts_num; i++)
	//{
	//	cvCircle(img_color, cvPoint(points[i].x, points[i].y), 2, CV_RGB(0, 255, 0), CV_FILLED);
	//}

	//��ȡ����5�������㱣����feature��
	unsigned char isgetFeat = this->face_recognizer_1->ExtractFeatureWithCrop(image_data, points, feature);
	if (!isgetFeat)
		return false;

	//IplImage *img_color
	//  (grandchild)cvarr->cvmat(son)->ipllmage(parent)
	//���ܱ���
	//  cvSaveImage("result.bmp", img_color);

	cvReleaseImage(&img_color);
	cvReleaseImage(&img_grayscale);

	delete[]data;
	return true;

}

bool SeetaFace::myGetFeature_2(string fileName, float* feature) //��ȡ����������feat��
{

	const char *imagePath = fileName.c_str();
	IplImage *img_grayscale = cvLoadImage(imagePath, 0);

	IplImage *img_color = cvLoadImage(imagePath, 2);  /* ?, color */
	if ((img_color == NULL) || (img_grayscale == NULL))
	{
		return 0;
	}

	int pts_num = 5;
	int im_width = img_grayscale->width;
	int im_height = img_grayscale->height;
	unsigned char* data = new unsigned char[im_width * im_height];
	unsigned char* data_ptr = data;
	unsigned char* image_data_ptr = (unsigned char*)img_grayscale->imageData;
	int h = 0;
	for (h = 0; h < im_height; h++) {
		memcpy(data_ptr, image_data_ptr, im_width);
		data_ptr += im_width;
		image_data_ptr += img_grayscale->widthStep;
	}

	seeta::ImageData image_data(img_grayscale->width, img_grayscale->height, 1);
	image_data.data = data;

	// Detect faces
	vector<seeta::FaceInfo> faces = this->myseetaface->Detect(image_data);
	int32_t face_num = static_cast<int32_t>(faces.size());

	if (face_num == 0)
	{
		delete[]data;
		cvReleaseImage(&img_grayscale);
		cvReleaseImage(&img_color);
		return 0;
	}

	// Detect 5 facial landmarks
	seeta::FacialLandmark points[5];
	bool isMark = point_detector->PointDetectLandmarks(image_data, faces[0], points);
	if (!isMark)
		return false;

	//// Visualize the results
	//cvRectangle(img_color, cvPoint(faces[0].bbox.x, faces[0].bbox.y), cvPoint(faces[0].bbox.x + faces[0].bbox.width - 1, faces[0].bbox.y + faces[0].bbox.height - 1), CV_RGB(255, 0, 0));
	//for (int i = 0; i<pts_num; i++)
	//{
	//	cvCircle(img_color, cvPoint(points[i].x, points[i].y), 2, CV_RGB(0, 255, 0), CV_FILLED);
	//}

	//��ȡ����5�������㱣����feature��
	unsigned char isgetFeat = this->face_recognizer_2->ExtractFeatureWithCrop(image_data, points, feature);
	if (!isgetFeat)
		return false;


	//IplImage *img_color
	//  (grandchild)cvarr->cvmat(son)->ipllmage(parent)
	//���ܱ���
	//  cvSaveImage("result.bmp", img_color);

	cvReleaseImage(&img_color);
	cvReleaseImage(&img_grayscale);

	delete[]data;
	return true;

}

float* SeetaFace::newFeatureBuffer()
{
	//һ�������������С  2048���ֽ�
	const float sizeFace = this->face_recognizer_1->feature_size();
	float *faceDress = new float[sizeFace];
	return faceDress;
}

float SeetaFace::FeatureCompare(float *feature1, float *feature2) //�����Ƚ�
{
	//API�ӿ�:SEETA_API float CalcSimilarity(FaceFeatures const fc1,FaceFeatures const fc2,long dim = -1);		
	return this->face_recognizer_1->CalcSimilarity(feature1, feature2);
}

SeetaFace::~SeetaFace()
{
}

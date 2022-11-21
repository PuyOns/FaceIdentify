#pragma once
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <face_alignment.h>
#include <face_identification.h>
#include <face_detection.h>

using namespace std;
using namespace seeta;
#ifndef _SEETAFACE_
#define _SEETAFACE_

class mySeetAFace :public FaceDetection
{
public:
	mySeetAFace(const char *model_name);

	~mySeetAFace() = default;
};

//���������������ʶ�������ģ���ʼ��
class SeetaFace
{
public:
	SeetaFace();
	~SeetaFace();

	mySeetAFace *myseetaface;   //FaceDectionģ�飬ʶ������
	FaceAlignment *point_detector;  //FaceAlignmentģ�飬��ȡ������������㣬������
	FaceIdentification *face_recognizer_1; //FaceIdentificationģ�飬�����Ա�ģ��
	FaceIdentification *face_recognizer_2; //FaceIdentificationģ�飬�����Ա�ģ��

	bool myGetFeature_1(string fileName, float* feature);     //��ȡ����������feat��
	bool myGetFeature_2(string fileName, float* feature);     //��ȡ����������feat��
	float *newFeatureBuffer();      //float feat=new float[2048]
	float FeatureCompare(float *feature1, float *feature2); //�����Ƚ�


};
#endif // !_SEETAFACE_


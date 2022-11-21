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

//这个类用来把人脸识别的三个模块初始化
class SeetaFace
{
public:
	SeetaFace();
	~SeetaFace();

	mySeetAFace *myseetaface;   //FaceDection模块，识别人脸
	FaceAlignment *point_detector;  //FaceAlignment模块，抽取人脸五个特征点，并保存
	FaceIdentification *face_recognizer_1; //FaceIdentification模块，人脸对比模块
	FaceIdentification *face_recognizer_2; //FaceIdentification模块，人脸对比模块

	bool myGetFeature_1(string fileName, float* feature);     //抽取特征保存在feat中
	bool myGetFeature_2(string fileName, float* feature);     //抽取特征保存在feat中
	float *newFeatureBuffer();      //float feat=new float[2048]
	float FeatureCompare(float *feature1, float *feature2); //特征比较


};
#endif // !_SEETAFACE_


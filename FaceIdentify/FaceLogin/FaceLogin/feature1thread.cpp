#include "feature1thread.h"


Feature1Thread::Feature1Thread(QObject *parent, QString mySiveImagePath)
	:QThread(parent), mySiveImagePath(mySiveImagePath)
{

}

void Feature1Thread::run()
{
	feat1 = iiSeetaFace.newFeatureBuffer();
	bool isFindFace=iiSeetaFace.myGetFeature_1(mySiveImagePath.toStdString(), feat1);
	emit sendReast(feat1, isFindFace);
	cout << "feat1=" << feat1<<endl;

}

Feature1Thread::~Feature1Thread()
{

}



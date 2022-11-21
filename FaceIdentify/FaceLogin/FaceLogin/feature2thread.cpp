#include "feature2thread.h"

Feature2Thread::Feature2Thread(QObject *parent, QString mySiveImagePath)
	: QThread(parent), mySiveImagePath(mySiveImagePath)
{

}

void Feature2Thread::run()
{
	feat2 = iiSeetaFace.newFeatureBuffer();
	bool isFindFace = iiSeetaFace.myGetFeature_1(mySiveImagePath.toStdString(), feat2);
	emit sendReast(feat2, isFindFace);
	cout <<"feat2="<< feat2<<endl;
}

Feature2Thread::~Feature2Thread()
{

}

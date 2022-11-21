#include "feat1compfeat2.h"

feat1Compfeat2::feat1Compfeat2(QObject *parent,  float *feat1,  float *feat2)
	: QThread(parent),fea1(feat1),fea2(feat2)
{
	cout << fea1 << " " << fea2<<endl;
}

void feat1Compfeat2::run()
{ 
	result=new double;
	*result=iiSeetaFace.FeatureCompare(fea1, fea2);
	emit sendReast(result);
    cout <<"对比结果是："<< *result << endl;
}

feat1Compfeat2::~feat1Compfeat2()
{

}

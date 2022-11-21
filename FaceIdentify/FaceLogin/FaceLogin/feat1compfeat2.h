#pragma once
#include <QThread>
#include "mySeetAFace.h"

#ifndef FEAT1COMPFEAT2_H
#define FEAT1COMPFEAT2_H

class feat1Compfeat2 : public QThread
{
	Q_OBJECT

public:
	feat1Compfeat2(QObject *parent, float *feat1,  float *feat2);
	~feat1Compfeat2();
	SeetaFace iiSeetaFace;
	void run();
signals:
	void sendReast(double *result);
private:
	 float *fea1;
	 float *fea2;
	 double *result;
	
};

#endif // FEAT1COMPFEAT2_H

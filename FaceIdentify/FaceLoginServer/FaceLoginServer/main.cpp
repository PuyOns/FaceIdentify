 #include "faceloginserver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FaceLoginServer w;
	w.show();
	return a.exec();
}

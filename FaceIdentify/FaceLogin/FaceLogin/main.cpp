
//#include "lineeditwithicon.h"  //��¼�����û������
//#include "title.h"     //�����ڱ�����
//#include "toolbaroffacewindow.h" //�����ڹ�����
//#include "staticbar.h"   //������״̬��
//#include "displayimage.h"  //��ʾͼƬ����
//#include "functiondisplaywindow.h" //������ʾ����
//#include "interfacefunction.h"

#include <QtWidgets/QApplication>
#include "facelogin.h"  //��¼����
#include "facewidows.h"  //������ 
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//FaceLoginServer fs;
	//fs.show();

	//***********///////
	FaceLogin w;
	FaceWidows f;
	if (w.exec() == QDialog::Accepted)
	{
		f.show();
		return a.exec();
	}
	else
		return 0;




	//FaceWidows f;
	//f.show();
	//return a.exec();

	/*LineEditWithIcon m(":/image/person.png");
	m.show();
	return a.exec();*/

	/*Title t;
	t.show();
	return a.exec();*/

	//ToolBarOfFaceWindow tb;
	//tb.show();
	//return a.exec();

	/*StaticBar s;
	s.show();
	return a.exec();*/

	/*DisplayImage im;
	im.show();
	return a.exec();*/

	/*FunctionDisplayWindow fw;
	fw.show();
	return a.exec();*/

}

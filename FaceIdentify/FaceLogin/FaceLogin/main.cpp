
//#include "lineeditwithicon.h"  //登录窗口用户密码框
//#include "title.h"     //主窗口标题栏
//#include "toolbaroffacewindow.h" //主窗口工具栏
//#include "staticbar.h"   //主窗口状态栏
//#include "displayimage.h"  //显示图片窗口
//#include "functiondisplaywindow.h" //功能显示窗口
//#include "interfacefunction.h"

#include <QtWidgets/QApplication>
#include "facelogin.h"  //登录窗口
#include "facewidows.h"  //主窗口 
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

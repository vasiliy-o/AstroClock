#include "astroclock.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);		
	AstroProc w;
	w.show();
	return a.exec();
}

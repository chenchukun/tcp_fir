#include "server.h"
#include <QApplication>

int main(int argc, char **argv)
{
	QApplication *app = new QApplication(argc, argv);
	Server s;
	s.show();
	app->exec();
}

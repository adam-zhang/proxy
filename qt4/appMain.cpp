#include <QCoreApplication>
#include <iostream>
#include "LocalServer.h"

int main(int argc, char** argv)
{
	QCoreApplication a(argc, argv);
	LocalServer server;
	server.listen(1080);
	return a.exec();
}

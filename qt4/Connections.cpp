#include "Connections.h"
#include "Utilities.h"
#include <QTcpSocket>

using namespace std;

Connections::Connections(QObject* parent)
	: QObject(parent)
{
}

Connections::~Connections() {}

void Connections::addSocket(QTcpSocket* socket)
{
	//map_.insert(make_pair(socket, data));
	connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Connections::onReadyRead()
{
	QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
	if (!socket->bytesAvailable())
		return;
	QByteArray data = socket->readAll();
	output(data);
	outputData(data);
	map_.insert(make_pair(socket, data));
}

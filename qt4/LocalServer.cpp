#include "LocalServer.h"
#include "Utilities.h"
#include "Connections.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

LocalServer::LocalServer(QObject* parent)
	: QObject(parent)
	  , server_(new QTcpServer(this))
	  , connects_(new Connections(this))
{
	initialize();	
}

LocalServer::~LocalServer()
{
}

bool LocalServer::listen(int port)
{
	Q_ASSERT(server_);
	QHostAddress address("127.0.0.1");
	return server_->listen(address, port);
}

void LocalServer::initialize()
{
	Q_ASSERT(server_);
	connect(server_, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void LocalServer::onNewConnection()
{
	//qDebug() << "onNewConnection called";
	QTcpSocket* socket = server_->nextPendingConnection();
	connects_->addSocket(socket);
}

//void LocalServer::onSocketDataReceived()
//{
//	qDebug() << "onSocketDataReceived called";
//	while(socket_->bytesAvailable())
//	{
//		QByteArray data = socket_->readAll();
//		outputData(data);
//		output(data);
//	}
//	//QByteArray data = {0x05, 0x00};
//	//socket_->write(data);
//}

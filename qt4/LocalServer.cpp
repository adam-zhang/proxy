#include "LocalServer.h"
#include "Utilities.h"
#include <QTcpServer>
#include <QTcpSocket>

LocalServer::LocalServer(QObject* parent)
	: QObject(parent)
	  , server_(new QTcpServer(this))
	  , socket_(0)
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
	socket_ = server_->nextPendingConnection();
	Q_ASSERT(socket_);
	connect(socket_, SIGNAL(disconnect()), socket_, SLOT(deleteLater()));
	connect(socket_, SIGNAL(readyRead()), this, SLOT(onSocketDataReceived()));
}

void LocalServer::onSocketDataReceived()
{
	while(socket_->bytesAvailable())
	{
		QByteArray data = socket_->readAll();

	}
}

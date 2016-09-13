#ifndef __LOCALSERVER__H
#define __LOCALSERVER__H

#include <QObject>

class QTcpServer;
class QTcpSocket;
class Connections;

class LocalServer : public QObject
{
	Q_OBJECT
public:
	LocalServer(QObject* parent = 0);
	~LocalServer();
public:
	bool listen(int port);
private:
	QTcpServer* server_;
	Connections* connects_;
private:
	void initialize();
private slots:
	void onNewConnection();
	//void onSocketDataReceived();
};
#endif//__LOCALSERVER__H

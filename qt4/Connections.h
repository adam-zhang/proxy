#ifndef __CONNECTIONS__H
#define __CONNECTIONS__H

#include <QObject>
#include <map>
//#include <vector>

class QTcpSocket;


class Connections : public QObject
{
	Q_OBJECT
public:
	Connections(QObject* parent);
	~Connections();
private:
	std::map<QTcpSocket*, QByteArray> map_;

public:
	void addSocket(QTcpSocket*);
private slots:
	void onReadyRead();

};
#endif//__CONNECTIONS__H

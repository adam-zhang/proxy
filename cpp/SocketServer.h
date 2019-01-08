#ifndef __SOCKETSERVER__H
#define __SOCKETSERVER__H
#include <memory>
#include <vector>
#include <thread>
#include <list>

class Socket;


class SocketServer
{
	public:
		explicit SocketServer(short port)
			: port_(port)
		{

		}
		void run();
	private:
		std::shared_ptr<Socket> socket_;	
		short port_;
	private:
		void threadProc(std::shared_ptr<Socket>& s);
		std::list<std::shared_ptr<std::thread>> threads_;
		void removeThread(std::thread::id);
};
#endif//__SOCKETSERVER__H

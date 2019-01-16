#ifndef __CONNNECTIONHANDLER__H
#define __CONNNECTIONHANDLER__H
#include <memory>

class Socket;

class ConnectionHandler
{
	public:
		explicit ConnectionHandler(const std::shared_ptr<Socket>&);
	private:
		std::shared_ptr<Socket> local_;
		std::shared_ptr<Socket> remote_;
	public:
		bool run();
};
#endif//__CONNNECTIONHANDLER__H

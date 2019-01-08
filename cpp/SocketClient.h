#ifndef __SOCKETCLIENT__H
#define __SOCKETCLIENT__H

#include <string>
#include <memory>
#include <vector>

class Socket;

class SocketClient
{
	public:
		SocketClient(const std::string& ip, short port);
	private:
		std::shared_ptr<Socket> socket_;
	public:
		bool Connect();
		size_t Receive(std::vector<char>&);
		size_t Send(const std::vector<char>&);
		size_t Send(const std::string& );
};
#endif//__SOCKETCLIENT__H

#ifndef __SOCKET__H
#define __SOCKET__H

#include <netinet/in.h>
#include <string>
#include <memory>
#include <vector>

class Socket
{
	public:
		explicit Socket(short port);
		Socket(const std::string&, short port);
		Socket(int s, const sockaddr_in& address);
		~Socket();
	public:
		static std::shared_ptr<Socket> fromHostName(const std::string&);
	private:
		int socket_;
		struct sockaddr_in address_;
	public:
		const int fileDescriptor()
		{ return socket_; }
		const sockaddr_in& address()const
		{ return address_; }
	public:
		bool Bind();
		bool Listen();
		bool Connect();
		std::shared_ptr<Socket> Accept();
		ssize_t Receive(std::vector<char>&);
		ssize_t Send(const std::vector<char>&);
		ssize_t Send(const std::vector<char>&, size_t size);
};
#endif//__SOCKET__H

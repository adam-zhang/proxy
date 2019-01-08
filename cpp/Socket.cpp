#include "Socket.h"
#include "Debugger.h"
#include <cassert>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

static int createSocket()
{
	int r = socket(AF_INET, SOCK_STREAM, 0);
	assert(r > 0);
	return r;
}

static struct sockaddr_in createAddress(short port)
{
	sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	return address;
}

static struct sockaddr_in createAddress(const string& ip, short port)
{
	sockaddr_in address = createAddress(port);
	inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
	return address;
}



Socket::Socket(short port)
	: socket_(createSocket())
	  , address_(createAddress(port))
{
	assert(socket_ > 0);
}

Socket::Socket(const string& ip, short port)
	: socket_(createSocket())
	  , address_(createAddress(ip, port))
{
	assert(socket_);
}

Socket::Socket(int s, const sockaddr_in& address)
	: socket_(s)
	  , address_(address)
{ 
	assert(socket_);
}

Socket::~Socket()
{
	close(socket_);
}

bool Socket::Bind()
{
	int ret = bind(socket_, (sockaddr*)&address(), sizeof(sockaddr_in));
	if (ret < 0)
	{
		Debugger::write("error in bind", errno);
		return false;
	}
	int value = 0;
	setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int));
	return true;
}

bool Socket::Listen()
{
	int ret = listen(socket_, 256);
	if (ret < 0)
	{
		Debugger::write("error in listen", errno);
		return false;
	}
	return true;
}

bool Socket::Connect()
{
	int ret = connect(socket_, (sockaddr*)&address_, sizeof(sockaddr_in));
	return ret > 0;
}

std::shared_ptr<Socket> Socket::Accept()
{
	sockaddr_in clientAddress = {0};
	socklen_t size = 0;
	int ret = accept(socket_, (sockaddr*)&clientAddress, &size);
	if (ret < 0)
		return NULL;
	auto p = make_shared<Socket>(ret, clientAddress);
	fcntl(ret, F_SETFD, fcntl(ret, F_GETFD, 0 )|O_NONBLOCK);
	return p;
}

size_t Socket::Receive(vector<char>& data)
{
	return read(socket_, &data[0], data.size());
}

size_t Socket::Send(const vector<char>& data)
{
	return write(socket_, &data[0], data.size());
}

size_t Socket::Send(const vector<char>& buffer, size_t size)
{
	return write(socket_, &buffer[0], size);
}


#include "SocketClient.h"
#include "Socket.h"

using namespace std;

SocketClient::SocketClient(const std::string& ip, short port)
	: socket_(std::make_shared<Socket>(ip, port))
{
}

bool SocketClient::Connect()
{
	return socket_->Connect();
}

size_t SocketClient::Receive(vector<char>& buffer)
{
	return socket_->Receive(buffer);
}

size_t SocketClient::Send(const vector<char>& buffer)
{
	return socket_->Send(buffer);
}

size_t SocketClient::Send(const string& data)
{
	vector<char> v(data.begin(), data.end());
	return Send(v);
}

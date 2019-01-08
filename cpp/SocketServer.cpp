#include "SocketServer.h"
#include "Socket.h"
#include <thread>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "Debugger.h"

using namespace std;

void SocketServer::run()
{
	socket_ = make_shared<Socket>(port_);
	if (!socket_->Bind())
		return;
	if (!socket_->Listen())
		return;
	while(auto client = socket_->Accept())
	{
		thread t(std::bind(&SocketServer::threadProc, this, client));
		t.detach();
	}
}

void SocketServer::threadProc(std::shared_ptr<Socket>& s)
{
	vector<char> buffer(512);
	auto count = s->Receive(buffer);	
	cout << count << " bytes received.\n";
	copy(buffer.begin(), buffer.begin() + count, ostream_iterator<char>(cout));
	cout << "\n";
}


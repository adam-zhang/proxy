#include "ConnectionHandler.h"
#include "Socket.h"
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

ConnectionHandler::ConnectionHandler(shared_ptr<Socket>& local)
	:local_(local)
{}

static string readHeader(const shared_ptr<Socket>& socket)
{
	vector<char> buffer(512);
	string ret;
	size_t count = 0;
	while((count = socket->Receive(buffer)) > 0)
	{
		copy(buffer.begin(), 
				buffer.begin() + count,
			       	back_inserter(ret));
	}
}


static void sendBack(shared_ptr<Socket>& remote,
	       	shared_ptr<Socket>& local)
{
	vector<char> buffer(1024);
	size_t count = 0;
	while((count = remote->Receive(buffer)) > 0)
	{
		local->Send(buffer, count);
	}
}

template<typename T>
bool begin_with(const basic_string<T>& left, const basic_string<T>& right )
{
	if (left.size() < right.size())
		return false;
	for(size_t i = 0; i != right.size(); ++i)
		if (right[i] != left[i])
			return false;
	return true;
}


static string getHost(const string& header)
{
	stringstream ss;
	ss << header;
	string line;
	while(getline(ss, line))
	{
		if (begin_with<char>(line, "host: "))
			return line.substr(6);
	}
	return string();
}

bool ConnectionHandler::run()
{
	string header = readHeader(local_);
	string host = getHost(header);
	if (!regex_match(host, regex("[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(/.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+/.?")))
		return false;
	remote_ = make_shared<Socket>(host, 80);
	sendBack(remote_, local_);
}

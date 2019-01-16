/* File Name: server.c */  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <cassert>
#include "trim.h"

#define DEFAULT_PORT 8000  
#define MAXLINE 4096  

using namespace std;

string readHeader(int fd)
{
	string s;
	vector<char> buffer(MAXLINE);
	int count = 0;
	while((count = read(fd, &buffer[0], MAXLINE)) > 0)
	{
		cout << "count:" << count << endl;
		copy(buffer.begin(), buffer.begin() + count, back_inserter(s));
	}
	//cout << "after read" << endl;
	return s;
}

bool begin_with(const string& s, const string& compareTo)
{
	if(s.size() < compareTo.size())
		return false;
	for(auto i = 0; i != compareTo.size(); ++i)
		if (compareTo[i] != s[i])
			return false;
	return true;
}

string getHost(const string& header)
{
	stringstream ss;
	ss << header;
	string host("Host: ");
	string line;
	while(getline(ss, line))
	{
		//cout << "line:" << line << endl;
		if (begin_with(line, host))
			return trim(line.substr(host.size()));
	}
	return "";
}

string sendToRemote(const string& header)
{
	cout << "header in sending remote:" << header << endl;
	auto host = getHost(header);	
	struct sockaddr_in address = {0};
	socklen_t size = 0;
	cout << "before gethostbyname\n" << host << 
		"\n" << host.size() << endl;
	hostent* target = gethostbyname(host.c_str());
	cout << "after gethostbyname.\n";
	assert(target);
	int i = 0;
	int remote = socket(AF_INET, SOCK_STREAM, 0);
	assert(remote != -1);
	sockaddr_in remoteAddress = {0};
	remoteAddress.sin_family = AF_INET;
	remoteAddress.sin_port = htons(80);
	remoteAddress.sin_addr.s_addr = *((int*)target->h_addr);
	connect(remote, (sockaddr*)&remoteAddress, sizeof(sockaddr_in));
	write(remote, header.c_str(), header.size());
	vector<char> buffer(4096);
	int count = 0;
	string s;
	while((count = read(remote, &buffer[0], 5096)) > 0)
	{
		if (count < 4096 )
			close(remote);
		copy(buffer.begin(), buffer.end(), back_inserter(s));
	}
	cout << "received:\n" << s << endl;
	if (s.size() == 0)
		++i;
	else
		return s;
	return string();
}


void processConnection(int fd)
{
	auto header = readHeader(fd);
	auto host = getHost(header);
	auto content = sendToRemote(header);
	write(fd, content.c_str(), content.size());
}

int main(int argc, char** argv)  
{  
	int    socket_fd, connect_fd;  
	struct sockaddr_in     servaddr;  
	char    buff[4096];  
	int     n;  
	//初始化Socket  
	if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
		printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
		exit(0);  
	}  
	int opt = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(int));
	//初始化  
	memset(&servaddr, 0, sizeof(servaddr));  
	servaddr.sin_family = AF_INET;  
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
	servaddr.sin_port = htons(DEFAULT_PORT);//设置的端口为DEFAULT_PORT  

	//将本地地址绑定到所创建的套接字上  
	if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
		printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
		exit(0);  
	}  
	//开始监听是否有客户端连接  
	if( listen(socket_fd, 10) == -1){  
		printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
		exit(0);  
	}  
	printf("======waiting for client's request======\n");  
	while(1)
	{  
		//阻塞直到有客户端连接，不然多浪费CPU资源。  
		if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){  
			printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
			continue;  
		}  
		//接受客户端传过来的数据  
		//n = recv(connect_fd, buff, MAXLINE, -1);  
		//向客户端发送回应数据  
		if(!fork())
		{ 
			fcntl(connect_fd, F_SETFL, fcntl(connect_fd, F_GETFL, 0)|O_NONBLOCK);
			processConnection(connect_fd);
			//if(send(connect_fd, "Hello,you are connected!\n", 26,0) == -1)  
			//	perror("send error");  
			//close(connect_fd);  
			//exit(0);  
		}  
		//buff[n] = '\0';  
		//printf("recv msg from client: %s\n", buff);  
		close(connect_fd);  
	}  
	close(socket_fd);  
}  

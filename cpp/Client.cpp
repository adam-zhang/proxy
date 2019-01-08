#include <iostream>
#include "SocketClient.h"
#include "Common.h"

using namespace std;

int main(int, char**)
{
	SocketClient client("127.0.0.1", PORT);
	auto ret = client.Connect();
	client.Send("Hello Server");
	return 0;
}

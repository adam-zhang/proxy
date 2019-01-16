#include <iostream>
#include "SocketServer.h"
#include "Common.h"
#include "Debugger.h"
#include "ConnectionHandler.h"

using namespace std;

int main(int, char**)
{
	SocketServer server(PORT);
	Debugger::write("before run");
	server.run();
	Debugger::write("after run");
	return 0;
}

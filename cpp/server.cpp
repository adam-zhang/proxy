#include <iostream>
#include "SocketServer.h"
#include "Common.h"
#include "Debugger.h"

int main(int, char**)
{
	SocketServer server(PORT);
	Debugger::write("after server");
	server.run();
	Debugger::write("after run");
	return 0;
}

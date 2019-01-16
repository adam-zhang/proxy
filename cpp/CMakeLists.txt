cmake_minimum_required(VERSION 2.8)
project(proxy)
set(CMAKE_BUILD_TYPE Debug)
set(server_sources server.cpp
	Socket.cpp
	SocketServer.cpp
	Debugger.cpp	
	ConnectionHandler.cpp
	)
set(client_sources Client.cpp
	Socket.cpp
	SocketClient
	Debugger.cpp)
add_executable(server ${server_sources})
target_link_libraries(server pthread)

add_executable(client ${client_sources})


#pragma once

#include "WSAInitializer.h"
#include <WS2tcpip.h>
#include <stdio.h>
#include <string.h>
#include "RequestsStructs.h"
#include "ResponsesStructs.h"
#include "Constants.h"
#include "RequestHandlerFactory.h"
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <string>
#include <iostream>
#include <thread>

class IRequestHandler;

class Communicator
{
public:
	Communicator(std::string SERVER_IP, int SERVER_PORT);
	~Communicator();
	void startHandleRequests();

private:
	std::string m_SERVER_IP;
	int activeThreads;
	int m_SERVER_PORT;
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;//<SOCKET <TCP, IPV4>, IRequestHandler - OBJECT>
	RequestHandlerFactory* m_handleFactory;

	void accept();
	void bindAndListen();
	void handleNewClient(SOCKET _clientSocket);

};


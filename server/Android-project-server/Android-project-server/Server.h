#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <thread>
#include <iostream>
#include "Communicator.h"


class Server
{
public:
	Server(std::string SERVER_IP, int SERVER_PORT);
	void run();
private:
	Communicator* m_communicator;
};



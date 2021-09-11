#pragma warning(disable : 4996)

#include "Server.h"


Server::Server(std::string SERVER_IP, int SERVER_PORT)
{
	m_communicator = new Communicator(SERVER_IP, SERVER_PORT);
}

void Server::run()
{
	std::string adminCommand = "";
	//Openes new Thread that detach from...
	std::thread t_connector(&Communicator::startHandleRequests, m_communicator);
	t_connector.detach();

	do
	{
		std::cout << "ADMIN #>";
		std::cin >> adminCommand;
	} while (adminCommand != "EXIT");

	return;
}

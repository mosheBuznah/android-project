#include "Communicator.h"
#pragma warning(disable : 4996)
#include <chrono>
#include <thread>

Communicator::Communicator(std::string SERVER_IP, int SERVER_PORT)
{
	this->m_SERVER_IP = SERVER_IP;
	this->m_SERVER_PORT = SERVER_PORT;
	this->activeThreads = 0;
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{

	std::cout << "[" << m_SERVER_IP << "] " << "Listening on port " << m_SERVER_PORT << std::endl;
	bindAndListen();
	while (true)
	{
		std::cout << "[" << m_SERVER_IP << ":" << m_SERVER_PORT << "] " << "Waiting for client connection request..." << std::endl;
		accept();
	}
}


void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(this->m_SERVER_PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = inet_addr(this->m_SERVER_IP.c_str());//Ip has given from config.txt
	sa.sin_addr.s_addr = INADDR_ANY;  // when there are few ip's for the machine. We will use always "INADDR_ANY"


	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

void Communicator::accept()
{
	SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "[" << m_SERVER_IP << ":" << m_SERVER_PORT << "] " << "New Connection...Openning new Thread" << std::endl;
	activeThreads++;
	std::cout << "Active threads - {" << activeThreads << "}" << std::endl;

	std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
	clientThread.detach();
}
void Communicator::handleNewClient(SOCKET _clientSocket)
{
	char buffer[256] = { 0 };
	while (true)
	{
		recv(_clientSocket, buffer, 1024, 0);
		printf("message from client: ");
		puts(buffer);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		send(_clientSocket, "recieve message\n", strlen("recieve message\n") + 1, 0);
	}
}

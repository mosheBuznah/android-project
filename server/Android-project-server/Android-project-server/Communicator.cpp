#include "Communicator.h"
#pragma warning(disable : 4996)
#include <chrono>
#include <thread>
#include "SocketHelper.h"
#include "LoginRequestHandler.h"

Communicator::Communicator(std::string SERVER_IP, int SERVER_PORT)
{
	this->m_SERVER_IP = SERVER_IP;
	this->m_SERVER_PORT = SERVER_PORT;
	this->activeThreads = 0;
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	this->m_handleFactory = new RequestHandlerFactory();

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

	LoginRequestHandler* clientLoginHandler = m_handleFactory->createLoginRequestHandler();
	m_clients.insert(std::make_pair(client_socket, clientLoginHandler));
	std::cout << "[" << m_SERVER_IP << ":" << m_SERVER_PORT << "] " << "New Connection...Openning new Thread" << std::endl;
	activeThreads++;
	std::cout << "Active threads - {" << activeThreads << "}" << std::endl;

	std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
	clientThread.detach();

}
void Communicator::handleNewClient(SOCKET _clientSocket)
{
	RequestInfo requestInfoFromClient = { 0 };

	int index = 0;
	//send(_clientSocket, "Hello User", 11, 0);
	while (true)
	{
		int code = 0;
		int jsonLen = 0;
		try
		{
			 code = SocketHelper::getCode(_clientSocket);
			std::cout << "code ===================== " << code << "\n\n\n";


			if (code == 0) {
				//WSAGetLastError();
				continue;
			}

			/*if (code != GET_ROOMS && code != GET_HIGH_SCORE_RESPONSE
				&& code != GET_PERSONAL_STATS_RESPONSE && code != LOGOUT && code != LEAVE_ROOM
				&& code != CLOSE_ROOM && code != START_GAME && code != GET_ROOM_STATE && code != GET_QUESTION_REQUEST
				&& code != GET_GAME_RESULT_REQUEST)
			{
				jsonLen = SocketHelper::getJsonLen(_clientSocket);
				if (index == 0)
					std::cout << jsonLen << "\n";
				requestInfoFromClient.buffer = (unsigned char*)SocketHelper::getJsonData(_clientSocket, jsonLen);

			}*/
		}
		catch (...) {
			std::cout << "error" << std::endl;
			m_clients.erase(_clientSocket);
			break; //socket was closed
		}

		try
		{
			index++;
			requestInfoFromClient.id = code;
			requestInfoFromClient.sizeJsonMessage = jsonLen;
			time(&requestInfoFromClient.curtime);

			std::cout << "requestInfoFromClient.buffer+5: " << requestInfoFromClient.buffer << "\n\n";
			RequestResult responseToClient = m_clients[_clientSocket]->handleRequest(requestInfoFromClient);
			m_clients[_clientSocket] = responseToClient.newHandler;

			std::cout << "code: " << code << std::endl;
			std::cout << "len message " << requestInfoFromClient.sizeJsonMessage << "\n";
			std::cout << "message from client: " << requestInfoFromClient.buffer << "\n";
			std::cout << "message to client: " << (char*)responseToClient.response + 5 << "\n";

			SocketHelper::sendMessageByProtocol(_clientSocket, code, (char*)responseToClient.response + 5);
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	activeThreads--;
	closesocket(_clientSocket);//100% close SOCKET connection

}

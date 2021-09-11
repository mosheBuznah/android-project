#include "Communicator.h"
#pragma warning(disable : 4996)


Communicator::Communicator(std::string SERVER_IP, int SERVER_PORT)
{
	this->m_SERVER_IP = SERVER_IP;
	this->m_SERVER_PORT = SERVER_PORT;
	this->activeThreads = 0;
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
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
		// the main thread is only accepting clients 
		// and add then to the list of handlers
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
	//sa.sin_addr.s_addr = INADDR_ANY;  // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

void Communicator::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	//struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&client_socket;
	// the function that handle the conversation with the client
	//Start new thread to handle request

	//LoginRequestHandler clientLoginHandler;
	//m_clients.insert(std::make_pair(client_socket, clientLoginHandler));
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
		//send(_clientSocket, "recieve!!!", 20, 0);
		



		int sock = 0, valread;
		struct sockaddr_in serv_addr;
		//char* hello = "Hello from client";
		char buffer[1024] = { 0 };
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			printf("\n Socket creation error \n");
			return;
		}

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(3001);

		// Convert IPv4 and IPv6 addresses from text to binary form
		//inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		if (inet_pton(AF_INET, "10.100.102.22", &serv_addr.sin_addr) <= 0)
		{
			printf("\nInvalid address/ Address not supported \n");
			return;
		}

		if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		{
			printf("\nConnection Failed \n");
			return;
		}
		send(sock, "message", strlen("message"), 0);
	}
}

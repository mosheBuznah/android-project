#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include "Server.h"


#define CONFIG_FILE_PATH "config.txt"

#pragma warning (disable: 4996)

std::pair<std::string, int>getFromConfigFile()
{
	std::string server_ip;
	int port = 0;


	std::cout << "Server is starting...\nOpening config file: " << CONFIG_FILE_PATH << std::endl;
	std::ifstream fin(CONFIG_FILE_PATH);
	std::string line;
	std::istringstream sin;
	try
	{
		/*
		CONFING FILE PROTOCOL

		server_ip=<STR_SERVER_IPV4>
		port=<INT_PORT>
		*/
		while (std::getline(fin, line)) {
			sin.str(line.substr(line.find("=") + 1));
			if (line.find("server_ip") != std::string::npos) {
				std::cout << "SERVER_IP: " << sin.str() << std::endl;
				std::cout << "_______________________________________________________________________________" << std::endl;
				sin >> server_ip;
			}
			else if (line.find("port") != std::string::npos) {
				sin >> port;
			}
			sin.clear();
		}
		fin.close();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}

	return std::make_pair(server_ip, port);
}

int main()
{

	WSAInitializer wsaInit;

	std::pair<std::string, int> infoPair = getFromConfigFile();
	try {
		Server myServer(infoPair.first, infoPair.second);
		myServer.run();

	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}

	system("PAUSE");
	return EXIT_SUCCESS;
}

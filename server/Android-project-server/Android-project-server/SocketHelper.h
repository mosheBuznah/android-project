#pragma once
#include "Communicator.h"
#include "JsonResponsePacketSerializer.h"
#include "jsonRequestPacketDeserializer.h"
#include "SocketHelper.h"
#include <string>


class SocketHelper
{
public:
	//send functions
	static void sendMessageByProtocol(SOCKET sock, int code, char* jsonData);
	static void send(SOCKET sock, unsigned char* buffer, int buffLen);

	//get from buffer
	static int getCode(SOCKET sock);
	static int getJsonLen(SOCKET sock);
	static char* getJsonData(SOCKET sock, int lenMessage);

	//recv all buffer by protocol

};

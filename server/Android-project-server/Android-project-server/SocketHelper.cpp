#include "SocketHelper.h"

void SocketHelper::sendMessageByProtocol(SOCKET sock, int code, char* jsonData)
{
    unsigned char* buffer = JsonResponsePacketSerializer::createBuffer(code, std::string(jsonData));
    send(sock, buffer, strlen(jsonData) + 1 + 4);
}

void SocketHelper::send(SOCKET sock, unsigned char* buffer, int buffLen)
{
    if (::send(sock, (char*)buffer, buffLen, 0) == -1)
        throw std::exception("couldn't send this message");
}

int SocketHelper::getCode(SOCKET sock)
{
    char code = 0;
    recv(sock, &code, 1, 0);

    return code;
}

int SocketHelper::getJsonLen(SOCKET sock)
{
    char lenBinary[4] = { 0 };
    recv(sock, lenBinary, 4, 0);

    return jsonRequestPacketDeserializer::charBitsToInt((unsigned char*)lenBinary);
}

char* SocketHelper::getJsonData(SOCKET sock, int lenMessage)
{
    int len = lenMessage + 1;
    char* jsonData = new char[len];
    recv(sock, jsonData, lenMessage, 0);
    jsonData[len - 1] = 0;
    return jsonData;
}

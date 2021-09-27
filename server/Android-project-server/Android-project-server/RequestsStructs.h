#pragma once

#include <string>
#include "IRequestHandler.h"

class IRequestHandler;

struct SignUpRequest
{
	std::string userName;
	std::string password;
	std::string fullName;
	std::string email_phone;
};

struct LoginRequest
{
	std::string userName;
	std::string password;
};

struct ErrorRequest
{
	std::string message;
};

struct RequestInfo
{
	int id;
	int sizeJsonMessage;
	time_t curtime;
	unsigned char* buffer; //json data only
};

//typedef struct RequestInfo RequestInfo;

struct RequestResult
{
	unsigned char* response;
	IRequestHandler* newHandler;
};

//typedef struct RequestResult RequestResult;



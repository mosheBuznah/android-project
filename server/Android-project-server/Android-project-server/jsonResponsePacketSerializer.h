#pragma once
#include "ResponsesStructs.h"
#include "json.hpp"
#include "Constants.h"
#include <iostream>
#include <bitset>
#include <cmath>

using json = nlohmann::json;


class JsonResponsePacketSerializer
{
public:
	//Get code and json message and create a buffer msg ready to send
	static unsigned char* createBuffer(int code, std::string jsonMessage);

	static unsigned char* serializeResponse(ErrorResponse errorResponse);
	static unsigned char* serializeResponse(LoginResponse loginResponse);
	static unsigned char* serializeResponse(SignUpResponse signUpResponse);
private:
	static unsigned char* num32Bits(int number);
};



#pragma once
#include "RequestsStructs.h"
#include "json.hpp"
#include <bitset>
#include <iostream>
#include <cmath>

using json = nlohmann::json;

class jsonRequestPacketDeserializer
{
public:
	/*Deserialize <ALL functions>*/
	//version 1
	static LoginRequest deserializerLoginRequest(unsigned char* buffer);
	static SignUpRequest deserializerSignupRequest(unsigned char* buffer);

	static int charBitsToInt(unsigned char* buff);

};


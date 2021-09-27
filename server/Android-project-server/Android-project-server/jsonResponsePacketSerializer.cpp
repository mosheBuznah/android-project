#include "jsonResponsePacketSerializer.h"

#pragma warning (disable: 4996)


unsigned char* JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse)
{
	json jsonErrorResponse;
	unsigned char* buffer; // all the buffer to send with the seocket
	std::string jsonErrorResponseStr = "";

	//create the json fields
	jsonErrorResponse["message"] = errorResponse.message;
	jsonErrorResponseStr = jsonErrorResponse.dump();

	//buffer = createBuffer(ERROR, jsonErrorResponseStr);
	buffer = createBuffer(ERROR_RESPONSE, jsonErrorResponseStr);
	return buffer;
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
	json jsonLoginResponse;
	unsigned char* buffer; // all the buffer to send with the seocket
	std::string jsonLoginResponseStr = "";

	//create the json fields
	jsonLoginResponse["status"] = loginResponse.status;
	jsonLoginResponseStr = jsonLoginResponse.dump();

	buffer = createBuffer(LOGIN_REQUEST, jsonLoginResponseStr);

	return buffer;
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(SignUpResponse signUpResponse)
{
	json jsonSignUpResponse;
	unsigned char* buffer; // all the buffer to send with the seocket
	std::string jsonSignUpResponseStr = "";

	//create the json fields
	jsonSignUpResponse["status"] = signUpResponse.status;
	jsonSignUpResponseStr = jsonSignUpResponse.dump();

	buffer = createBuffer(SIGN_UP_REQUEST, jsonSignUpResponseStr);

	return buffer;
}


unsigned char* JsonResponsePacketSerializer::num32Bits(int number)
{
	unsigned char* digs = new unsigned char[4];
	std::string bitsNumber = std::bitset<32>(number).to_string();

	unsigned char num8Bits = 0;
	int power = 7;
	int ind = 0;

	for (int j = 0; j < 32; j++) {
		num8Bits += (bitsNumber[j] - '0') * pow(2, power);
		power--;

		if (power == -1) {
			digs[ind] = num8Bits;
			num8Bits = 0;
			ind++;
			power = 7;
		}
	}

	return digs;
}



unsigned char* JsonResponsePacketSerializer::createBuffer(int code, std::string jsonMessage)
{
	unsigned char* buffer; // all the buffer to send with the seocket
	unsigned char* lenMessage = new unsigned char[5];

	// code, sizeMessage, the message and null at the end
	int sizeBuff = 1 + 4 + jsonMessage.size() + 1;
	buffer = new unsigned char[sizeBuff];
	lenMessage = num32Bits(jsonMessage.size());

	buffer[0] = code;
	//copy the len of the message to our buffer
	for (int i = 0; i < 4; i++)
		buffer[1 + i] = lenMessage[i];
	std::strcpy((char*)buffer + 5, jsonMessage.c_str()); //copy the message itself

	return buffer;
}

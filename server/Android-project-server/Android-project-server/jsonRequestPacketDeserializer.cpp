#include "jsonRequestPacketDeserializer.h"

#pragma warning (disable: 4996)

LoginRequest jsonRequestPacketDeserializer::deserializerLoginRequest(unsigned char* buffer)
{
    json loginRequestJson = json::parse(buffer + 5);
    LoginRequest loginRequest;

    loginRequest.userName = loginRequestJson["userName"];
    loginRequest.password = loginRequestJson["password"];

    return loginRequest;
}

SignUpRequest jsonRequestPacketDeserializer::deserializerSignupRequest(unsigned char* buffer)
{
    json signUpRequestJson = json::parse(buffer + 5);
    SignUpRequest signUpRequest;

    signUpRequest.userName = signUpRequestJson["username"];
    signUpRequest.password = signUpRequestJson["password"];
    signUpRequest.email_phone = signUpRequestJson["email_phone"];
    signUpRequest.fullName = signUpRequestJson["fullName"];

    return signUpRequest;
}

int jsonRequestPacketDeserializer::charBitsToInt(unsigned char* buff)
{
    int num = 0;
    std::string num32BitsStr = "";
    for (int i = 0; i < 4; i++) {
        num32BitsStr += std::bitset<8>(buff[i]).to_string();
    }

    for (int i = 0; i < num32BitsStr.size(); i++) {
        num += (num32BitsStr[i] - '0') * (int)pow(2, 31 - i);
    }

    return num;
}

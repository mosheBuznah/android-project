#pragma once

#include <string>
struct LoginResponse
{
	unsigned int status; 
	std::string errorMessage; //optional
};

struct SignUpResponse
{
	unsigned int status;
	std::string errorMessage; //optional
};


struct ErrorResponse
{
	std::string message;
};

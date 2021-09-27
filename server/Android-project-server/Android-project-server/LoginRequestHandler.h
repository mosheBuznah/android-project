#pragma once
#include "IRequestHandler.h"
#include "RequestsStructs.h"
#include "ResponsesStructs.h"
//#include "jsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Constants.h"
#include "LoginManager.h"
//#include "RequestHandlerFactory.h"

#include <ctime>

class RequestHandlerFactory;

class LoginRequestHandler :
    public IRequestHandler
{
private:
    LoginManager* m_loginManager;
    RequestHandlerFactory* m_handleFactory;

    /*All functions that in Login State*/
    RequestResult login(RequestInfo infoFromClient);
    RequestResult signup(RequestInfo infoFromClient);
public:
    bool isRequestRelevant(RequestInfo requestInfo);
    /*Login functions Router*/
    RequestResult handleRequest(RequestInfo requestInfo);
    LoginRequestHandler(LoginManager* loginManager, RequestHandlerFactory* requestHandleFactory);
};




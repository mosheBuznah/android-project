#include "LoginRequestHandler.h"

#pragma warning (disable: 4996)

RequestResult LoginRequestHandler::login(RequestInfo infoFromClient)
{
    json clientLoginData = json::parse(infoFromClient.buffer);
    LoginResponse loginResponse;

    RequestResult requestResultToClient;
    if (m_loginManager->login(clientLoginData["userName"], clientLoginData["password"])) {
        loginResponse.status = 1;
        //requestResultToClient.newHandler = m_handleFactory->createMenuRequestHandler(clientLoginData["username"]);
    }
    else {
        loginResponse.status = 0;
      //  requestResultToClient.newHandler = m_handleFactory->createLoginRequestHandler();
    }
    requestResultToClient.response =
        JsonResponsePacketSerializer::serializeResponse(loginResponse);

    return requestResultToClient;
}

RequestResult LoginRequestHandler::signup(RequestInfo infoFromClient)
{
    json clientSignUpData = json::parse(infoFromClient.buffer);
    SignUpResponse signUpResponse;

    RequestResult requestResultToClient;
    std::cout << "json : " << clientSignUpData["userName"] << " " << clientSignUpData["password"]
        << " " << clientSignUpData["email"] << std::endl;
    if (m_loginManager->signup(clientSignUpData["userName"],
        clientSignUpData["password"], clientSignUpData["email_phone"], "", "", "")) {
        signUpResponse.status = 1;
        //requestResultToClient.newHandler = m_handleFactory->createMenuRequestHandler(clientSignUpData["username"]);
    }
    else {
        signUpResponse.status = 0;
       // requestResultToClient.newHandler = m_handleFactory->createLoginRequestHandler();
    }
    requestResultToClient.response =
        JsonResponsePacketSerializer::serializeResponse(signUpResponse);
    requestResultToClient.newHandler = this;

    return requestResultToClient;
}


bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
    return requestInfo.id == LOGIN_REQUEST || requestInfo.id == SIGN_UP_REQUEST;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
    if (isRequestRelevant(requestInfo))
    {
        switch (requestInfo.id)
        {
            case LOGIN_REQUEST:
                return login(requestInfo);
                break;
            case SIGN_UP_REQUEST:
                return signup(requestInfo);
                break;
            default:
                break;
        }
    }

    ErrorResponse error;
    error.message = "Error: Not supported code...";
    RequestResult request = {NULL, NULL};
    strcpy((char*)request.response, (char*)JsonResponsePacketSerializer::serializeResponse(error));
    request.newHandler = this; //stay in the login state

    return request;
}

LoginRequestHandler::LoginRequestHandler(LoginManager* loginManager, 
    RequestHandlerFactory* requestHandleFactory)
{
}

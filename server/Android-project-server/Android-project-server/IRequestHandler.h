
#ifndef IREQUEST_HANDLER
#define IREQUEST_HANDLER

#include "RequestsStructs.h"


struct RequestResult;
struct RequestInfo;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo requestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
private:

};


#endif // !IREQUEST_HANDLER


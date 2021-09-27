#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory()
{
    m_database = new SqliteDataBase();
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(&m_loginManager, this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}

IDataBase* RequestHandlerFactory::getDB()
{
    return m_database;
}




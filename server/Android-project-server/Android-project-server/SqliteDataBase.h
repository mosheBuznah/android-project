#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#include <iostream>
class SqliteDataBase :
    public IDataBase
{
public:
	bool open();
	bool close();
	bool sqlExecution(std::string command);
	bool isThereThisUsername(std::string userName);
	bool isThePasswordCorrect(std::string userName, std::string password);
	bool createUser(std::string userName, std::string password, std::string mail);
private:
	sqlite3* db = nullptr;

	//private functions
	bool createUsersTable(sqlite3* db);
};


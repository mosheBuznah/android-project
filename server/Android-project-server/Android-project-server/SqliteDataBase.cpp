#include "SqliteDataBase.h"
#include <io.h>

int callbackCounter(void* data, int argc, char** argv, char** azColName)
{
	float counter = 0;
	for (int i = 0; i < argc; i++)
	{
		counter = std::stof(argv[i]);
	}
	float* pCounter = (float*)data;
	*pCounter = counter;
	data = pCounter;
	return 0;
}



bool SqliteDataBase::open()
{
	std::string dbFileName = "Trivia_DB.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);

	int res = sqlite3_open(dbFileName.c_str(), &this->db);
	if (res != SQLITE_OK) {
		db = nullptr;
		std::cout << "[SQLite3:ERROR_1] Failed to open DB" << std::endl;
		return false;
	}
	if (doesFileExist)
	{
		std::cout << "[SQLite3] Creating new DB..." << std::endl;
		int createFlagUsersName = createUsersTable(db);
		//int createFlagStatistics = createStatisticsTable(db);
		if (createFlagUsersName == 0)
		{
			std::cout << "[SQLite3:ERROR_2] Failed to Create a DB" << std::endl;
			return false;
		}
		else
		{
			std::cout << "[SQLite3] All DB colums created successfully..." << std::endl;
		}
	}
	else
	{
		std::cout << "[SQLite3] DB Opened" << std::endl;
	}
	return true;
}

bool SqliteDataBase::close()
{
	sqlite3_close(db);
	db = nullptr;
	std::cout << "[SQLite3] DB Closed" << std::endl;
	return true;

}

bool SqliteDataBase::sqlExecution(std::string command)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, command.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::string myString(errMessage);
		std::cout << "[SQLite3:ERROR] " << errMessage << std::endl;
		return false;
	}
	return true;

}

bool SqliteDataBase::isThereThisUsername(std::string userName)
{
	std::string command = "SELECT COUNT(1) FROM USERS WHERE USERNAME = \"" + userName + "\"";
	char* errMessage = nullptr;
	int exist = false;
	int result = sqlite3_exec(db, command.c_str(), callbackCounter, (void*)&exist, &errMessage);
	if (result != SQLITE_OK)
	{
		std::string myString(errMessage);
		std::cout << "[SQLite3:ERROR] " << errMessage << std::endl;
		std::cout << "Command" << command << std::endl;
	}
	return exist;

}

bool SqliteDataBase::isThePasswordCorrect(std::string userName, std::string password)
{
	if (!isThereThisUsername(userName))
		return false;
	std::string command = "SELECT COUNT(1) FROM USERS WHERE USERNAME = \"" + userName + "\" AND PASSWORD = \"" + password + "\"";
	char* errMessage = nullptr;
	int exist = false;
	int result = sqlite3_exec(db, command.c_str(), callbackCounter, (void*)&exist, &errMessage);
	if (result != SQLITE_OK)
	{
		std::string myString(errMessage);
		std::cout << "[SQLite3:ERROR] " << errMessage << std::endl;
		std::cout << "Command" << command << std::endl;
	}
	return exist;

}

bool SqliteDataBase::createUser(std::string userName, std::string password, std::string mail)
{
	std::string command = "INSERT INTO USERS (USERNAME, PASSWORD, MAIL) VALUES (\"" + userName + "\", \"" + password + "\", \"" + mail + "\");";

	bool result = sqlExecution(command);
	if (result) {
		std::cout << "[SQLite3] User: " << userName << " Added successfully..." << std::endl;
	}
	else {
		std::cout << "[SQLite3:ERROR] Failed to add a User... COMMAND: " << command << std::endl;
	}

	return result;

}


bool SqliteDataBase::createUsersTable(sqlite3* db)
{
	std::string sqlStatement = R"(
CREATE TABLE USERS (
USERNAME TEXT PRIMARY KEY NOT NULL,
PASSWORD TEXT NOT NULL,
EMAIL_NUMBER TEXT NOT NULL,
FULL_NAME TEXT NOT NULL
);
)";


	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::string myString(errMessage);
		std::cout << "[SQLite3:ERROR] " << errMessage << std::endl;
		return false;
	}
	return true;
}


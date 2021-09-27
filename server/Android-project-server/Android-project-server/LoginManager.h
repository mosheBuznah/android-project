#pragma once
#include <string>
#include <vector>
#include "IDataBase.h"
#include "SqliteDataBase.h"

class LoginManager
{
public:
	LoginManager();
	//before we work with db we need to open it 
	bool openDatabase();
	//when we finish the work with the db we need to close it (point db pointer to null)
	bool closeDatabase();
	//Get all user data and create in db USER table a user 
	bool signup(std::string userName, std::string password,
		std::string mail, std::string address,
		std::string phone_number, std::string brith_date);
	//get user name and password and check if the pass and username match if yes we will add to vector Logged User
	bool login(std::string userName, std::string password);
	//Remove from LoggedUser vector 
	bool logout(std::string userName);

	//Test Function print all connected users
	void printAllLoggedUsers();

	//version 3 - change password Bonus
	int changePassword(std::string userName, std::string password);
	std::vector<std::string> getUserDetails(std::string userName);
private:
	IDataBase* m_database = new SqliteDataBase();
	//std::vector<LoggedUser> m_loggedUsers;

	bool isUserConnected(std::string username);

};


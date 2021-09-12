#include "LoginManager.h"

LoginManager::LoginManager()
{
	m_database = new SqliteDataBase();
	openDatabase();
}

bool LoginManager::openDatabase()
{
	return this->m_database->open();
}

bool LoginManager::closeDatabase()
{
	this->m_database->close();
	delete m_database;
	return true;
}

bool LoginManager::signup(std::string userName, std::string password,
	std::string mail, std::string address,
	std::string phone_number, std::string brith_date)
{
	try
	{
		bool res = m_database->createUser(userName, password, mail);
		if (res) {
			std::cout << "[SQLite3] User: " << userName << " signed up successfully..." << std::endl;
			//now the user is logged in to the system
			//LoggedUser newLoggedUser(userName);
			//this->m_loggedUsers.push_back(newLoggedUser);
			std::cout << "[SQLite3] User: " << userName << " login successfully..." << std::endl;
		}
		else
			std::cout << "[SQLite3:Error] User: " << userName << " can't sign up..." << std::endl;
		return res;
	}
	catch (std::exception& e)
	{
		std::cout << "[SQLite3:Error] User: " << userName << " can't sign up..." << e.what() << std::endl;
		return false;
	}
}

bool LoginManager::login(std::string userName, std::string password)
{
	try
	{
		bool loginPass = m_database->isThePasswordCorrect(userName, password);
		bool connectedUser = isUserConnected(userName);
		if (loginPass && connectedUser == false)
		{
			//LoggedUser newLoggedUser(userName);
			//this->m_loggedUsers.push_back(newLoggedUser);
			std::cout << "[SQLite3] User: " << userName << " login successfully..." << std::endl;
			return true;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "[SQLite3:Error] Login failed..." << e.what() << std::endl;
	}

	return false;
}

/*
bool LoginManager::logout(std::string userName)
{
	try
	{
		for (std::vector <LoggedUser>::iterator it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it) {
			if (it->getUsername() == userName)
			{
				m_loggedUsers.erase(it);
				std::cout << "[SQLite3] User: " << userName << " logout successfully..." << std::endl;
				return true;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << "[SQLite3:Error] Logout failed..." << e.what() << std::endl;
		return false;
	}
}

void LoginManager::printAllLoggedUsers()
{
	if (m_loggedUsers.size() == 1)
		std::cout << "[SQLite3] User: " << m_loggedUsers[0].getUsername() << " status: login" << std::endl;
	else
		for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it)
		{
			std::cout << "[SQLite3] User: " << it->getUsername() << " status: login" << std::endl;
		}

}

int LoginManager::changePassword(std::string userName, std::string password)
{
	int code = m_database->changePassword(userName, password);
	if (code == USER_DOESNT_EXIST) {
		std::cout << "[SQLite3:Error] Change password faild... User doesn't exist" << std::endl;
		return USER_DOESNT_EXIST;
	}
	else if (code == PASSWORD_EQALE_TO_OLD_PASS) {
		std::cout << "[SQLite3:Error] Change password faild... password equal to old password" << std::endl;
		return PASSWORD_EQALE_TO_OLD_PASS;
	}
	else if (code == CHANGE_PASSWORD_SQLITE_ERROR) {
		std::cout << "[SQLite3:Error] Change password faild... sqlite error" << std::endl;
		return CHANGE_PASSWORD_SQLITE_ERROR;
	}
	else {
		std::cout << "[SQLite3:Error] Change password success" << std::endl;
		return CHANGE_PASSWORD_SCUCCESS;
	}

}

std::vector<std::string> LoginManager::getUserDetails(std::string userName)
{
	std::vector<std::string> user = m_database->getUserDetails(userName);

	if (user.size() == 0) {
		std::cout << "[SQLite3:Error] Change password faild... user doesn't exist" << std::endl;
		return user;
	}
	else {
		std::cout << "[SQLite3:Error] Change password success" << std::endl;
		return user;
	}

}

bool LoginManager::isUserConnected(std::string username)
{
	for (int i = 0; i < m_loggedUsers.size(); i++) {
		if (username == m_loggedUsers[i].getUsername())
			return true;
	}
	return false;
}*/

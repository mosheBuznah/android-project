#pragma once
#include<string>

class IDataBase
{
	/*
	Open a Database
	If there is no db we will create a new db one
	*/
	virtual bool open() = 0;
	/*
	* Close a db and set db pointer to null
	*/
	virtual bool close() = 0;
	//Get a string (sql command) and execute it to sql
	virtual bool sqlExecution(std::string command) = 0;

	//Function get string type username and check in db through sql command if there is this username in db
	virtual bool isThereThisUsername(std::string userName) = 0;

	//Checking if the passwords from the db is match and also the usernames is matches too
	virtual bool isThePasswordCorrect(std::string userName, std::string password) = 0;

	/*
	Creating a User and put it to the db
	@params:
	String -> UserName,
	String -> Sha256 -> Password,
	String -> Mail
	*/
	virtual bool createUser(std::string userName, std::string password, std::string mail) = 0;

};


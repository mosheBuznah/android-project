#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
//#include "MenuRequestHandler.h"
#include "IDataBase.h"
#include "SqliteDataBase.h"
//#include "RoomAdminRequestHandler.h"
//#include "RoomMemberRequestHandler.h"
//#include "GameManager.h"
//#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	//version 1
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	IDataBase* getDB();


	//version 2
	//MenuRequestHandler* createMenuRequestHandler(std::string username);
	

	//version 3
	//RoomAdminRequestHandler* createRoomAdminRequestHandler(Room* room, LoggedUser loggedUser);
	//RoomMemberRequestHandler* createRoomMemberRequestHandler(Room* room, LoggedUser loggedUser);

	//version 4
	//GameRequestHandler* createGameRequestHandler(Game* game, std::string userName,
	//	GameManager* gameManager, int roomID);
	//GameManager* getGameManager();
	//StatisticsManager* getStatisticsManager();
private:
	LoginManager m_loginManager;
	//RoomManager m_roomManager;
	IDataBase* m_database;
	//GameManager* m_gameManager;
	//StatisticsManager* m_statisticsManager;
};

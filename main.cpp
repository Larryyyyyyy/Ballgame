#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <vector>
#include <sqlite3.h>
#include "BacisFunction.h"
#include "gzjmain.h"
#include "func.h"
#include "player.h"
#include "task.h"
#include "registerlogin.h"
#include "button.h"
using namespace std; 
extern int go = 0;//菜单状态
extern int Type = -1, Mode = -1, Track = -1; //*****
extern string ip = "";
extern int port = 0;
extern bool sente = 0;
player account;
int callback1(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		if (argv[0] == account.getName()) {
			account = player(argv[0], argv[1], argv[2], stoi(argv[3]), stoi(argv[4]));
			return 0;
		}
	}
	return 0;
}
int main() {
	account = registermain();
	sqlite3* db;
	char* errMsg = 0;
	int rc = sqlite3_open("player.db", &db);  // 将 "your_database.db" 替换为实际的数据库文件名
	if (rc) {
		std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
		return 0;
	}
	std::string sql = "SELECT username, userpassword, usermibao, coins, points FROM player";
	rc = sqlite3_exec(db, sql.c_str(), callback1, 0, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL错误: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	sqlite3_close(db);
	if (account.getName() != "")gzjmain(account);
	else gzjmain(account);
	return 0;
}
/*
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "game.h"
extern int go = 0;//菜单状态
extern int Type = -1, Mode = -1, Track = -1; //*****
extern string ip="";
extern int port=0;
extern bool sente = 0;
int main(){
	gameType Type = PVP;
	gameMode Mode = Snoke;
	gameTrack Track = Casual;
//	menu x;
//	game x(Type, Mode, Track, 0);
	levelPage y;
//	y.draw();
	//测试store
	avatar* avatar_ = new avatar("Fuyang", "123456", "images/微信图片_20241211195719.jpg");
	avatar_->addCoins(1000);
	Store store;
	store.draw(avatar_->sticks, avatar_->coins);
	//测试ranking
	ranking ranking_;
//	ranking_.drawRanking();
	//测试Profile
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "Test Window!");

	avatar_->addCoins(1000);
	avatar_->sticks->purchase(4);
	avatar_->sticks->equip(4);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::White);
		avatar_->drawProfile(window);
		window.display();
	}
    return 0;
}*/
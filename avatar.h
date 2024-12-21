#pragma once
#ifndef AVATAR_H
#define AVATAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include "button_.h"
#include "item.h"

class avatar {
public:

	Inventory* sticks; //直接放一个Store类记录当前用户的皮肤状态
	int coins = 0; //**********暂时为了方便设置成public

	//avatar (const std::string& name, const std::string& password) : name(name), coins(0), points(0), password(password) {}
	avatar(const std::string& name, const std::string& password, std::string path);
	avatar(const std::string& name, const std::string& password, std::string mibao, std::string path, int coin, int point);
	~avatar() {
		delete sticks;
	}
	void addCoins(const int x) { coins += x; }
	void addPoints(const int x) { points += x; }
	int getCoins() { return coins; }
	int getPoints() { return points; }
	std::string getPassword() { return password; }
	std::string getmibao() { return mibao; }
	std::string getName() { return name; }
	//Inventory* getSticks() { return sticks; }

	//渲染排名
	void drawRanking(sf::RenderWindow& window, float x, float y, bool current);

	//处理事件
	void handleEvent(sf::RenderWindow& window, sf::Event event);

	//渲染用户信息
	void drawProfile(sf::RenderWindow& window);

private:
	//用于渲染的部分
	sf::Texture texture;
	sf::Sprite sprite; //头像
	sf::Text nameText, pointsText; //名字，得分
	float avatarSize = 80; //显示大小
	sf::Font font; //字体文件

	std::string name, password,mibao;
	int points = 0;

	//显示名字的按钮（具体位置看是什么场景再设置）
	button_ nameButton;
	//在事件循环中判断nameButton有没有被点击。点击->drawProfile
};
#endif
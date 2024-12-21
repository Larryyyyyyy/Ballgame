#pragma once
#ifndef PLAYER
#define PLAYER
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include"func.h"
using namespace std;
class player {
public:
	player(const std::string& name, const std::string& password, const std::string& mibao, int coins,int points) :name(name), password(password), mibao(mibao), coins(coins), points(points) {}
	player(const std::string& name,const std::string& password,const std::string& mibao,int op):name(name),password(password),mibao(mibao),coins(0),points(0){}
	player(const std::string& name, const std::string& password) : name(name), coins(0), points(0), password(password) {}
	player(const std::string& name, const std::string& password, std::string path) : name(name), coins(0), points(0), password(password) {
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}
	player():name(""){}
	void addCoins(const int x) { coins += x; }
	void addPoints(const int x) { points += x; }
	string getpassword() { return password; }
	string getmibao() { return mibao; }
	int getCoins() { return coins; }
	int getPoints() { return points; }
	string getName() { return name; }
private:
	sf::Texture texture;
	sf::Sprite sprite;

	string name, password,mibao;
	int coins, points;
};
#endif
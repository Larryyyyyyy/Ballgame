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

	Inventory* sticks; //ֱ�ӷ�һ��Store���¼��ǰ�û���Ƥ��״̬
	int coins = 0; //**********��ʱΪ�˷������ó�public

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

	//��Ⱦ����
	void drawRanking(sf::RenderWindow& window, float x, float y, bool current);

	//�����¼�
	void handleEvent(sf::RenderWindow& window, sf::Event event);

	//��Ⱦ�û���Ϣ
	void drawProfile(sf::RenderWindow& window);

private:
	//������Ⱦ�Ĳ���
	sf::Texture texture;
	sf::Sprite sprite; //ͷ��
	sf::Text nameText, pointsText; //���֣��÷�
	float avatarSize = 80; //��ʾ��С
	sf::Font font; //�����ļ�

	std::string name, password,mibao;
	int points = 0;

	//��ʾ���ֵİ�ť������λ�ÿ���ʲô���������ã�
	button_ nameButton;
	//���¼�ѭ�����ж�nameButton��û�б���������->drawProfile
};
#endif
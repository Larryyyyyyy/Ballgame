#pragma once
#ifndef RANKING_H
#define RANKING_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include "avatar.h"
#include "button.h"

//const int WINDOW_WIDTH = 1500;
//const int WINDOW_HEIGHT = 1000; //��С
//const int WINDOW_WIDTH = 802;
//const int WINDOW_HEIGHT = 603; //��С

class ranking {
public:
	ranking();
	~ranking() {
		delete currentAvatar;
		for (auto* avatar : avatars)
			delete avatar;
		avatars.clear();
	}

	//ע���µ�Avatar������һ��Avatar���ָ�루�����洴�����µ�Avatar�����
	void registerAvatar(avatar* avatar);

	//��¼Avatar����¼�µ�ǰ�û��ĵ�ַ
	void loginAvatar(const std::string& name);

	//��Ⱦ����
	void drawRanking();

private:
	//������ʾ
	sf::RenderWindow window;
    int topHeight;

	//�û���
	std::vector<avatar*> avatars; //��ָ���¼�����û� //ֻ���ַ
	avatar* currentAvatar; //��ǰ�û�

	float offsetx = 200, offsety; //��ʼλ������
	float rowHeight = 150; //�и�
	float rankingSize = 100; //������ŵĴ�С
};
#endif
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
//const int WINDOW_HEIGHT = 1000; //大小
//const int WINDOW_WIDTH = 802;
//const int WINDOW_HEIGHT = 603; //大小

class ranking {
public:
	ranking();
	~ranking() {
		delete currentAvatar;
		for (auto* avatar : avatars)
			delete avatar;
		avatars.clear();
	}

	//注册新的Avatar，传递一个Avatar类的指针（在外面创建好新的Avatar类对象）
	void registerAvatar(avatar* avatar);

	//登录Avatar，记录下当前用户的地址
	void loginAvatar(const std::string& name);

	//渲染排名
	void drawRanking();

private:
	//窗口显示
	sf::RenderWindow window;
    int topHeight;

	//用户们
	std::vector<avatar*> avatars; //用指针记录所有用户 //只存地址
	avatar* currentAvatar; //当前用户

	float offsetx = 200, offsety; //初始位置坐标
	float rowHeight = 150; //行高
	float rankingSize = 100; //排名序号的大小
};
#endif
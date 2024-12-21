#pragma once
#ifndef LEVEL_H
#define LEVEL_H
#include "button_.h"

class Level {
public:
	Level(int index, sf::Vector2f position, sf::RenderWindow& window) : isAccessible(0) {
		//两种不同颜色（是否开放）按钮的初始化
		
		string path = "images/level" + std::to_string(index) + "_1.png";
		button_* button__ = new button_(position, { 300.f * scale_, 230.f * scale_ }, path, window, { 0, 0, 0 });
		button[1] = button__;

		path = "images/level" + std::to_string(index) + "_0.png";
		button__ = new button_(position, { 300.f * scale_, 230.f * scale_ }, path, window, { 0, 0, 0 });
		button[0] = button__;
	}

	void openAccess() { isAccessible = 1; }

	void draw(sf::RenderWindow& window) {
		button[isAccessible]->Draw(window);
	}

	//判断是否点击了关卡，并且能否进入关卡
	bool handleEvent(sf::Vector2f position) {
		if (!isAccessible) return 0;
		return button[1]->if_contain(position);
	}

private:
	button_* button[2];
	bool isAccessible;
	const float scale_ = 0.714;
};

#endif
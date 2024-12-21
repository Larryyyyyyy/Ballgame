#pragma once
#ifndef BUTTON__H
#define BUTTON__H

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>//获取时间
#include <iomanip>
#include <sstream>
using namespace std;

class button_
{
public:
	//文字按键的构造函数
	button_(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color);

	//**************
	//文字按键的构造函数，但字体文件通过path传递
	button_(const string& text, const std::string& path, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color);

	//图片按钮的构造函数
	button_(const sf::Vector2f& position, const sf::Vector2f& size, const string& path, sf::RenderWindow& window, const sf::Vector3f& color);

	//在屏幕上显示按键
	void Draw(sf::RenderWindow& window) const;

	//检查鼠标点击（piont）是否在区域内
	bool if_contain(const sf::Vector2f& point) const;
private:
	sf::RectangleShape m_Rect;
	sf::Text m_Text;
	sf::Texture texture;
	sf::Sprite ButtonSprite;

	//创建标志以便Draw函数的显示
	int flag = -1;
};


#endif #pragma once

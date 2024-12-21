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

class gButton
{
public:
	//文字按键的构造函数
	gButton(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color);

	//图片按钮的构造函数
	gButton(const sf::Vector2f& position, const sf::Vector2f& size, const string& path, sf::RenderWindow& window, const sf::Vector3f& color);

	//在屏幕上显示按键
	void Draw(sf::RenderWindow& window) const;

	//检查鼠标点击（piont）是否在区域内
	bool if_contain(const sf::Vector2f& point) const;
	sf::RectangleShape m_Rect;
	sf::Text m_Text;
	sf::Texture texture;
	sf::Sprite ButtonSprite;

	//创建标志以便Draw函数的显示
	int flag = -1;
};
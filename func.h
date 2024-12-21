#ifndef FUNC_H
#define FUNC_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include"player.h"
using namespace std;

class Button
{
public:
	Button(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size,int flag=0);
	Button();
	Button& operator =(const Button& temp) {
		this->m_Rect = temp.m_Rect;
		this->m_Text = temp.m_Text;
		return *this;
	}
	void Draw(sf::RenderWindow& window) const;

	//检查鼠标点击（piont）是否在区域内
	bool if_contain(const sf::Vector2f& point) const;

	void changeColor(sf::Texture & t) {
		m_Rect.setTexture(&t);
	}
private:
	sf::RectangleShape m_Rect;
	sf::Text m_Text;
};

int midtext( sf::Text& text, sf::RenderWindow& window);
void colorful(const sf::Text& text,sf::RenderWindow & window);
void modifypassword(const string & username,const string & password);
void modifycoins(const string& username, int add);
void modifypoints(const string& username, int add);
unique_ptr<sf::Shader> loadColor(sf::Vector3f& lefcolor,sf::Vector3f& rigcolor);
int test();
#endif
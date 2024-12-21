#pragma once
#ifndef BUTTON__H
#define BUTTON__H

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>//��ȡʱ��
#include <iomanip>
#include <sstream>
using namespace std;

class button_
{
public:
	//���ְ����Ĺ��캯��
	button_(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color);

	//**************
	//���ְ����Ĺ��캯�����������ļ�ͨ��path����
	button_(const string& text, const std::string& path, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color);

	//ͼƬ��ť�Ĺ��캯��
	button_(const sf::Vector2f& position, const sf::Vector2f& size, const string& path, sf::RenderWindow& window, const sf::Vector3f& color);

	//����Ļ����ʾ����
	void Draw(sf::RenderWindow& window) const;

	//����������piont���Ƿ���������
	bool if_contain(const sf::Vector2f& point) const;
private:
	sf::RectangleShape m_Rect;
	sf::Text m_Text;
	sf::Texture texture;
	sf::Sprite ButtonSprite;

	//������־�Ա�Draw��������ʾ
	int flag = -1;
};


#endif #pragma once

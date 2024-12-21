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

class gButton
{
public:
	//���ְ����Ĺ��캯��
	gButton(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color);

	//ͼƬ��ť�Ĺ��캯��
	gButton(const sf::Vector2f& position, const sf::Vector2f& size, const string& path, sf::RenderWindow& window, const sf::Vector3f& color);

	//����Ļ����ʾ����
	void Draw(sf::RenderWindow& window) const;

	//����������piont���Ƿ���������
	bool if_contain(const sf::Vector2f& point) const;
	sf::RectangleShape m_Rect;
	sf::Text m_Text;
	sf::Texture texture;
	sf::Sprite ButtonSprite;

	//������־�Ա�Draw��������ʾ
	int flag = -1;
};
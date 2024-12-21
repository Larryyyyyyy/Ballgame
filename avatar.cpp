#pragma once
#include "avatar.h"

avatar::avatar(const std::string& name, const std::string& password, std::string mibao, std::string path, int coin, int point) :coins(coin), points(point), name(name), password(password), mibao(mibao), nameButton(name, "fonts/Bear-hard-candy-2.TTF", { 0, 0 }, { 20, 10 }, 10, { 0, 0, 0 }) {
	sticks = new Inventory();

	texture.loadFromFile(path);
	sprite.setTexture(texture);
	//*************
	//����ͷ������
	sf::Vector2u textureSize = texture.getSize();
	sprite.setScale(avatarSize / textureSize.x, avatarSize / textureSize.y); //ʵ��ͼƬ���Ź���

	//�������ְ�ť
	//sf::Font font;
	//font.loadFromFile("fonts/Bear-hard-candy-2.TTF");
	//Button button; //size��position
	//nameButton = button;

	//����������ʾ�ı�
	font.loadFromFile("fonts/Bear-hard-candy-2.TTF");
	nameText.setFont(font);
	nameText.setString(name);
	nameText.setCharacterSize(avatarSize - 20); //���ִ�С
	//nameText.setFillColor(sf::Color::Black);

	//���û�����ʾ�ı�
	pointsText.setFont(font);
	pointsText.setString(std::to_string(points));
	pointsText.setCharacterSize(avatarSize - 20); //���ִ�С
}
avatar::avatar(const std::string& name, const std::string& password, std::string path) : name(name), coins(0), points(0), password(password), nameButton(name, "fonts/Bear-hard-candy-2.TTF", { 0, 0 }, { 20, 10 }, 10, { 0, 0, 0 }) {

	//���Ƥ��ָ���ʼ��
	sticks = new Inventory();

	texture.loadFromFile(path);
	sprite.setTexture(texture);
	//*************
	//����ͷ������
	sf::Vector2u textureSize = texture.getSize();
	sprite.setScale(avatarSize / textureSize.x, avatarSize / textureSize.y); //ʵ��ͼƬ���Ź���

	//�������ְ�ť
	//sf::Font font;
	//font.loadFromFile("fonts/Bear-hard-candy-2.TTF");
	//Button button; //size��position
	//nameButton = button;

	//����������ʾ�ı�
	font.loadFromFile("fonts/Bear-hard-candy-2.TTF");
	nameText.setFont(font);
	nameText.setString(name);
	nameText.setCharacterSize(avatarSize - 20); //���ִ�С
	//nameText.setFillColor(sf::Color::Black);

	//���û�����ʾ�ı�
	pointsText.setFont(font);
	pointsText.setString(std::to_string(points));
	pointsText.setCharacterSize(avatarSize - 20); //���ִ�С
}

//�����а��ϻ��Ƶ�ǰ�û�
void avatar::drawRanking(sf::RenderWindow& window, float x, float y, bool current) {
	//����ͷ��λ��
	sprite.setPosition(x + 60.0f, y - 10);

	//����������ʾ�ı�
	//current��ʾ���û��Ƿ�Ϊ��ǰ��¼���û�
	if (current) {
		nameText.setFillColor(sf::Color::Red); //��Ϊ��ǰ�û�����Ⱦ�ɺ�ɫ
	}
	else {
		nameText.setFillColor(sf::Color::Yellow); //�����û�����Ⱦ�ɻ�ɫ
	}
	nameText.setCharacterSize(avatarSize - 20); //���ִ�С
	nameText.setPosition(x + 200.0f, y);

	//���û�����ʾ�ı�
	pointsText.setString(std::to_string(points));
	//current��ʾ���û��Ƿ�Ϊ��ǰ��¼���û�
	if (current) {
		pointsText.setFillColor(sf::Color::Red); //��Ϊ��ǰ�û�����Ⱦ�ɺ�ɫ
	}
	else {
		pointsText.setFillColor(sf::Color::Yellow); //�����û�����Ⱦ�ɻ�ɫ
	}
	pointsText.setCharacterSize(avatarSize - 20); //���ִ�С
	pointsText.setPosition(x + 1000.0f, y);

	window.draw(sprite);
	window.draw(nameText);
	window.draw(pointsText);
}

//�����¼�
void avatar::handleEvent(sf::RenderWindow& window, sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) { //����¼�Ϊ������
			sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			//�����������֣�����Ⱦ�û���Ϣprofile
			if (nameButton.if_contain(position)) drawProfile(window);
		}
	}
}

//���Ƹ��˼��
//��Ҫ�ж��Ƿ������ְ�ť���������Ƽ�飻�����˳���ť�������ִ�л��Ƽ�麯��
void avatar::drawProfile(sf::RenderWindow& window) {

	//Ҫ��һ���˳���

	//С���ڵĴ�С
	const int WIDTH = 650, HEIGHT = 450;

	//ֱ����ʾ�����м�
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f windowCenter(windowSize.x / 2.f, windowSize.y / 2.f); //��ȡ���м��λ��

	//ƫ��������ʼλ�ã�
	float offsetx = windowCenter.x - WIDTH / 2.f, offsety = windowCenter.y - HEIGHT / 2.f;

	//���ر�����Ƭ
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("images/Profile.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	//******postion
	//��Ⱦͷ�����֡�Ƥ�������֡���ң�����λ�ú�����

	//����ͷ�������
	sf::Vector2u textureSize = texture.getSize();
	sprite.setScale(100.f / textureSize.x, 100.f / textureSize.y); //ʵ��ͼƬ���Ź���

	//���»����ı�
	pointsText.setString(std::to_string(points));

	//�������֡���������Ĵ�С����ɫ
	nameText.setCharacterSize(40);
	pointsText.setCharacterSize(40);
	nameText.setFillColor(sf::Color::Black);
	pointsText.setFillColor(sf::Color::Black);

	//����λ��
	backgroundSprite.setPosition(offsetx, offsety);
	sprite.setPosition(offsetx + 70, offsety + 80);
	nameText.setPosition(offsetx + 370, offsety + 135);
	pointsText.setString(std::to_string(points)); //�ǵø���points����
	pointsText.setPosition(offsetx + 370, offsety + 220);

	//��Ⱦ�û���װ����Ƥ��
	sf::Sprite stickSprite = sticks->getEquipSprite();
	stickSprite.setScale(0.4f, 0.4f);
	stickSprite.setPosition(offsetx + 200, offsety + 300);

	//��Ⱦ
	window.draw(backgroundSprite);
	window.draw(sprite);
	window.draw(nameText);
	window.draw(pointsText);
	window.draw(stickSprite);
}
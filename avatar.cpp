#pragma once
#include "avatar.h"

avatar::avatar(const std::string& name, const std::string& password, std::string mibao, std::string path, int coin, int point) :coins(coin), points(point), name(name), password(password), mibao(mibao), nameButton(name, "fonts/Bear-hard-candy-2.TTF", { 0, 0 }, { 20, 10 }, 10, { 0, 0, 0 }) {
	sticks = new Inventory();

	texture.loadFromFile(path);
	sprite.setTexture(texture);
	//*************
	//设置头像缩放
	sf::Vector2u textureSize = texture.getSize();
	sprite.setScale(avatarSize / textureSize.x, avatarSize / textureSize.y); //实现图片缩放功能

	//设置名字按钮
	//sf::Font font;
	//font.loadFromFile("fonts/Bear-hard-candy-2.TTF");
	//Button button; //size和position
	//nameButton = button;

	//设置名字显示文本
	font.loadFromFile("fonts/Bear-hard-candy-2.TTF");
	nameText.setFont(font);
	nameText.setString(name);
	nameText.setCharacterSize(avatarSize - 20); //名字大小
	//nameText.setFillColor(sf::Color::Black);

	//设置积分显示文本
	pointsText.setFont(font);
	pointsText.setString(std::to_string(points));
	pointsText.setCharacterSize(avatarSize - 20); //积分大小
}
avatar::avatar(const std::string& name, const std::string& password, std::string path) : name(name), coins(0), points(0), password(password), nameButton(name, "fonts/Bear-hard-candy-2.TTF", { 0, 0 }, { 20, 10 }, 10, { 0, 0, 0 }) {

	//球杆皮肤指针初始化
	sticks = new Inventory();

	texture.loadFromFile(path);
	sprite.setTexture(texture);
	//*************
	//设置头像缩放
	sf::Vector2u textureSize = texture.getSize();
	sprite.setScale(avatarSize / textureSize.x, avatarSize / textureSize.y); //实现图片缩放功能

	//设置名字按钮
	//sf::Font font;
	//font.loadFromFile("fonts/Bear-hard-candy-2.TTF");
	//Button button; //size和position
	//nameButton = button;

	//设置名字显示文本
	font.loadFromFile("fonts/Bear-hard-candy-2.TTF");
	nameText.setFont(font);
	nameText.setString(name);
	nameText.setCharacterSize(avatarSize - 20); //名字大小
	//nameText.setFillColor(sf::Color::Black);

	//设置积分显示文本
	pointsText.setFont(font);
	pointsText.setString(std::to_string(points));
	pointsText.setCharacterSize(avatarSize - 20); //积分大小
}

//在排行榜上绘制当前用户
void avatar::drawRanking(sf::RenderWindow& window, float x, float y, bool current) {
	//设置头像位置
	sprite.setPosition(x + 60.0f, y - 10);

	//设置名字显示文本
	//current表示此用户是否为当前登录的用户
	if (current) {
		nameText.setFillColor(sf::Color::Red); //若为当前用户则渲染成红色
	}
	else {
		nameText.setFillColor(sf::Color::Yellow); //其他用户则渲染成黄色
	}
	nameText.setCharacterSize(avatarSize - 20); //名字大小
	nameText.setPosition(x + 200.0f, y);

	//设置积分显示文本
	pointsText.setString(std::to_string(points));
	//current表示此用户是否为当前登录的用户
	if (current) {
		pointsText.setFillColor(sf::Color::Red); //若为当前用户则渲染成红色
	}
	else {
		pointsText.setFillColor(sf::Color::Yellow); //其他用户则渲染成黄色
	}
	pointsText.setCharacterSize(avatarSize - 20); //名字大小
	pointsText.setPosition(x + 1000.0f, y);

	window.draw(sprite);
	window.draw(nameText);
	window.draw(pointsText);
}

//处理事件
void avatar::handleEvent(sf::RenderWindow& window, sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) { //如果事件为鼠标左击
			sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			//如果点击了名字，就渲染用户信息profile
			if (nameButton.if_contain(position)) drawProfile(window);
		}
	}
}

//绘制个人简介
//需要判断是否点击名字按钮，点击则绘制简介；设置退出按钮，点击则不执行绘制简介函数
void avatar::drawProfile(sf::RenderWindow& window) {

	//要放一个退出键

	//小窗口的大小
	const int WIDTH = 650, HEIGHT = 450;

	//直接显示在正中间
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f windowCenter(windowSize.x / 2.f, windowSize.y / 2.f); //获取正中间的位置

	//偏移量（初始位置）
	float offsetx = windowCenter.x - WIDTH / 2.f, offsety = windowCenter.y - HEIGHT / 2.f;

	//加载背景照片
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("images/Profile.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	//******postion
	//渲染头像、名字、皮肤、积分、金币：设置位置和缩放

	//设置头像的缩放
	sf::Vector2u textureSize = texture.getSize();
	sprite.setScale(100.f / textureSize.x, 100.f / textureSize.y); //实现图片缩放功能

	//更新积分文本
	pointsText.setString(std::to_string(points));

	//设置名字、积分字体的大小和颜色
	nameText.setCharacterSize(40);
	pointsText.setCharacterSize(40);
	nameText.setFillColor(sf::Color::Black);
	pointsText.setFillColor(sf::Color::Black);

	//设置位置
	backgroundSprite.setPosition(offsetx, offsety);
	sprite.setPosition(offsetx + 70, offsety + 80);
	nameText.setPosition(offsetx + 370, offsety + 135);
	pointsText.setString(std::to_string(points)); //记得更新points数据
	pointsText.setPosition(offsetx + 370, offsety + 220);

	//渲染用户所装备的皮肤
	sf::Sprite stickSprite = sticks->getEquipSprite();
	stickSprite.setScale(0.4f, 0.4f);
	stickSprite.setPosition(offsetx + 200, offsety + 300);

	//渲染
	window.draw(backgroundSprite);
	window.draw(sprite);
	window.draw(nameText);
	window.draw(pointsText);
	window.draw(stickSprite);
}
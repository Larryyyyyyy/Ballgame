#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "button_.h"

//记录单个item的信息
class item {
public:
	//设置物品名字，图像
	item(const std::string name, const std::string path, int price) : name(name), price(price) {
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		//if (name == "Classic Stick") sprite.setRotation(90); //暴力处理stick1竖向问题
		//后续都通过sprite处理
	}

	void setPosition(sf::RenderWindow& window, float x, float y) {
		sprite.setPosition(x, y); //设置sprite的位置

		buttons.clear();
		//设置purchase、equip按钮，需要用到sprite的位置
		buttons.reserve(3);

		sf::Vector2f position(x + 1000.0f, y); //位置
		sf::Vector2f size(200.f, 70.f); //大小
		sf::Vector3f color(255.0f, 255.0f, 0.0f); //颜色
		std::string path = "images/" + std::to_string(price) + ".png"; //对应价格的购买键
		buttons.emplace_back(position, size, path, window, color); //购买键

		//设置装备、已装备按钮
		position.x += 400.0f; //修改横坐标位置
		buttons.emplace_back(position, size, "images/equip.png", window, color);
		buttons.emplace_back(position, size, "images/isEquip.png", window, color);
	}

	void draw(sf::RenderWindow& window) { //在window上渲染item
		//渲染皮肤图片
		window.draw(sprite);

		if (!isPurchase) {
			buttons[0].Draw(window); //如果没购买就渲染购买按钮
		}
		if (isPurchase) { //如果购买了就渲染装备/已装备按钮
			if (!isEquip) buttons[1].Draw(window);
			else buttons[2].Draw(window);
		}
	}

	//处理事件
	int handleEvent(sf::Vector2f position) {
		//避免一些小bug：防止没显示按钮但会按到按钮

		position.y -= 140.f;
		//bug：点击按钮上方一点的位置才能监控到行为，所以暴力处理，让按钮准确点

		if (buttons[0].if_contain(position) && !isPurchase) { purchase(); return 0; } //购买
		if (buttons[1].if_contain(position) && !isEquip && isPurchase) { equip(); return 1; } //装备
		return -1;
	}

	int getPrice() { return price; }

	//购买、装备
	void purchase() { isPurchase = 1; }
	void equip() { isEquip = 1; }

	//移除购买、装备：处理金币不够的情况
	void removePurchase() { isPurchase = 0; }
	void removeEquip() { isEquip = 0; }

	sf::Sprite getSprite() { return sprite; }
	//sf::Texture getTexture() { return texture; }

private:
	std::string name; //item名字
	sf::Texture texture; //创建一个纹理图像加载照片
	sf::Sprite sprite; //创建一个精灵对象将texture应用到sprite上
	int price; //物品价格

	//记录是否购买、装备
	bool isPurchase = 0, isEquip = 0;

	//存放购买、装备、已装备按钮
	std::vector<button_> buttons;
};

//创建一个Inventory库存类，Item管理器
//对于每个用户都创建一个Inventory类对象，便于记录（初始展示的Item相同）
class Inventory {
public:
	//只有球杆皮肤就直接设置了
	Inventory() : rows(7), cols(1), offsetx(50.0f), offsety(300.0f) {
		/*sticks = new Inventory(6, 1, 50.0f, 300.0f);*/
		item* item_;
		item_ = new item("Classic Stick", "images/stick1.png", 0); //debug
		addItem(*item_);
		item_ = new item("Sword Stick", "images/stick2.png", 100);
		addItem(*item_);
		item_ = new item("Laser Stick", "images/stick3.png", 200);
		addItem(*item_);
		item_ = new item("Pirate Stick", "images/stick4.png", 300);
		addItem(*item_);
		item_ = new item("Octopus Stick", "images/stick5.png", 300);
		addItem(*item_);
		item_ = new item("Rose Stick", "images/stick6.png", 300);
		addItem(*item_);

		//初始化：使用默认皮肤
		purchase(0);
		equip(0);

		//items.reserve(rows * cols); //设置储存量
	}
	Inventory(const Inventory& other) : rows(other.rows), cols(other.cols), offsetx(other.offsetx), offsety(other.offsety) {
		items.reserve(rows * cols); //设置储存量
	}

	void addItem(const item& item_) { //添加新的item
		items.push_back(item_);
	}

	void setPosition(sf::RenderWindow& window) {
		int row = 0, col = 0; //枚举每个item的行列

		for (auto& item : items)
		{
			col == cols - 1 ? row++, col = 0 : col++;
			//设置每个item的位置
			item.setPosition(window, offsetx + col * height, offsety + row * height);
		}
	}

	void draw(sf::RenderWindow& window) { //在window上渲染所有item
		for (auto& item : items) item.draw(window);
	}

	//处理事件
	//position鼠标点击的位置，coins当前用户所用有的金币，offsety记录滚动屏的偏移量(y轴)
	int handleEvent(sf::Vector2f position, int& coins) {
		//std::cout << coins << "  " << equipIndex << std::endl;

		//index记录编号，便于更新equipIndex
		//type记录item处理事件的类型
		int index = 0, type;
		for (auto& item : items) {
			type = item.handleEvent(position);
			if (type == 0) { //用户购买此item
				if (item.getPrice() > coins) { //判断coins是否足够
					item.removePurchase(); //撤回购买操作
					return -1;
				}
				coins -= item.getPrice();
			}
			if (type == 1) {
				items[equipIndex].removeEquip(); //把原先装备的皮肤撤回装备
				equipIndex = index; //装备
			}
			index++;
		}
		return 1;
	}

	item getItem(const int& index) { return items[index]; }

	//购买编号为index的皮肤
	void purchase(const int& index) { items[index].purchase(); }

	//装备编号为index的皮肤
	void equip(const int& index) {
		items[equipIndex].removeEquip();
		items[index].equip();
		equipIndex = index;
	}

	//获取正在装备的皮肤的图像（用于渲染用户信息）
	sf::Sprite getEquipSprite() { return items[equipIndex].getSprite(); }
	int getequipindex() { return equipIndex; }
	//sf::Texture getEquipTexture() { return items[equipIndex].getTexture(); }

private:
	std::vector<item> items; //放Inventory中的物品
	int rows, cols; //记录行与列的容量，便于排列展示
	float offsetx, offsety; //展示的初始位置
	const float height = 170; //Item展示的大小

	int equipIndex = 0; //记录正在装备的编号
};

#endif
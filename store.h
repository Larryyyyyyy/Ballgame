#pragma once
#ifndef STORE_H
#define STORE_H

#include "item.h"

//主要实现
class Store {
public:
	Store();
	~Store() {
		//delete sticks; //释放内存
	}

	void draw(Inventory* sticks, int& coins);
	void purchaseError();
private:
	sf::RenderWindow window;
	//Inventory类对象改为从外部引入，便于记录用户信息
	//Inventory *sticks; //存放所有Item(内部处理购买与装置)
	//指针处理灵活点

	int coins; //用户所拥有的金币
	sf::Clock clock; //控制“金币不足”错误显示时间
	bool showError = 0; //用于产生“金币不足”提示
};

#endif
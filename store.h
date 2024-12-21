#pragma once
#ifndef STORE_H
#define STORE_H

#include "item.h"

//��Ҫʵ��
class Store {
public:
	Store();
	~Store() {
		//delete sticks; //�ͷ��ڴ�
	}

	void draw(Inventory* sticks, int& coins);
	void purchaseError();
private:
	sf::RenderWindow window;
	//Inventory������Ϊ���ⲿ���룬���ڼ�¼�û���Ϣ
	//Inventory *sticks; //�������Item(�ڲ���������װ��)
	//ָ�봦������

	int coins; //�û���ӵ�еĽ��
	sf::Clock clock; //���ơ���Ҳ��㡱������ʾʱ��
	bool showError = 0; //���ڲ�������Ҳ��㡱��ʾ
};

#endif
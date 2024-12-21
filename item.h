#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "button_.h"

//��¼����item����Ϣ
class item {
public:
	//������Ʒ���֣�ͼ��
	item(const std::string name, const std::string path, int price) : name(name), price(price) {
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		//if (name == "Classic Stick") sprite.setRotation(90); //��������stick1��������
		//������ͨ��sprite����
	}

	void setPosition(sf::RenderWindow& window, float x, float y) {
		sprite.setPosition(x, y); //����sprite��λ��

		buttons.clear();
		//����purchase��equip��ť����Ҫ�õ�sprite��λ��
		buttons.reserve(3);

		sf::Vector2f position(x + 1000.0f, y); //λ��
		sf::Vector2f size(200.f, 70.f); //��С
		sf::Vector3f color(255.0f, 255.0f, 0.0f); //��ɫ
		std::string path = "images/" + std::to_string(price) + ".png"; //��Ӧ�۸�Ĺ����
		buttons.emplace_back(position, size, path, window, color); //�����

		//����װ������װ����ť
		position.x += 400.0f; //�޸ĺ�����λ��
		buttons.emplace_back(position, size, "images/equip.png", window, color);
		buttons.emplace_back(position, size, "images/isEquip.png", window, color);
	}

	void draw(sf::RenderWindow& window) { //��window����Ⱦitem
		//��ȾƤ��ͼƬ
		window.draw(sprite);

		if (!isPurchase) {
			buttons[0].Draw(window); //���û�������Ⱦ����ť
		}
		if (isPurchase) { //��������˾���Ⱦװ��/��װ����ť
			if (!isEquip) buttons[1].Draw(window);
			else buttons[2].Draw(window);
		}
	}

	//�����¼�
	int handleEvent(sf::Vector2f position) {
		//����һЩСbug����ֹû��ʾ��ť���ᰴ����ť

		position.y -= 140.f;
		//bug�������ť�Ϸ�һ���λ�ò��ܼ�ص���Ϊ�����Ա��������ð�ť׼ȷ��

		if (buttons[0].if_contain(position) && !isPurchase) { purchase(); return 0; } //����
		if (buttons[1].if_contain(position) && !isEquip && isPurchase) { equip(); return 1; } //װ��
		return -1;
	}

	int getPrice() { return price; }

	//����װ��
	void purchase() { isPurchase = 1; }
	void equip() { isEquip = 1; }

	//�Ƴ�����װ���������Ҳ��������
	void removePurchase() { isPurchase = 0; }
	void removeEquip() { isEquip = 0; }

	sf::Sprite getSprite() { return sprite; }
	//sf::Texture getTexture() { return texture; }

private:
	std::string name; //item����
	sf::Texture texture; //����һ������ͼ�������Ƭ
	sf::Sprite sprite; //����һ���������textureӦ�õ�sprite��
	int price; //��Ʒ�۸�

	//��¼�Ƿ���װ��
	bool isPurchase = 0, isEquip = 0;

	//��Ź���װ������װ����ť
	std::vector<button_> buttons;
};

//����һ��Inventory����࣬Item������
//����ÿ���û�������һ��Inventory����󣬱��ڼ�¼����ʼչʾ��Item��ͬ��
class Inventory {
public:
	//ֻ�����Ƥ����ֱ��������
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

		//��ʼ����ʹ��Ĭ��Ƥ��
		purchase(0);
		equip(0);

		//items.reserve(rows * cols); //���ô�����
	}
	Inventory(const Inventory& other) : rows(other.rows), cols(other.cols), offsetx(other.offsetx), offsety(other.offsety) {
		items.reserve(rows * cols); //���ô�����
	}

	void addItem(const item& item_) { //����µ�item
		items.push_back(item_);
	}

	void setPosition(sf::RenderWindow& window) {
		int row = 0, col = 0; //ö��ÿ��item������

		for (auto& item : items)
		{
			col == cols - 1 ? row++, col = 0 : col++;
			//����ÿ��item��λ��
			item.setPosition(window, offsetx + col * height, offsety + row * height);
		}
	}

	void draw(sf::RenderWindow& window) { //��window����Ⱦ����item
		for (auto& item : items) item.draw(window);
	}

	//�����¼�
	//position�������λ�ã�coins��ǰ�û������еĽ�ң�offsety��¼��������ƫ����(y��)
	int handleEvent(sf::Vector2f position, int& coins) {
		//std::cout << coins << "  " << equipIndex << std::endl;

		//index��¼��ţ����ڸ���equipIndex
		//type��¼item�����¼�������
		int index = 0, type;
		for (auto& item : items) {
			type = item.handleEvent(position);
			if (type == 0) { //�û������item
				if (item.getPrice() > coins) { //�ж�coins�Ƿ��㹻
					item.removePurchase(); //���ع������
					return -1;
				}
				coins -= item.getPrice();
			}
			if (type == 1) {
				items[equipIndex].removeEquip(); //��ԭ��װ����Ƥ������װ��
				equipIndex = index; //װ��
			}
			index++;
		}
		return 1;
	}

	item getItem(const int& index) { return items[index]; }

	//������Ϊindex��Ƥ��
	void purchase(const int& index) { items[index].purchase(); }

	//װ�����Ϊindex��Ƥ��
	void equip(const int& index) {
		items[equipIndex].removeEquip();
		items[index].equip();
		equipIndex = index;
	}

	//��ȡ����װ����Ƥ����ͼ��������Ⱦ�û���Ϣ��
	sf::Sprite getEquipSprite() { return items[equipIndex].getSprite(); }
	int getequipindex() { return equipIndex; }
	//sf::Texture getEquipTexture() { return items[equipIndex].getTexture(); }

private:
	std::vector<item> items; //��Inventory�е���Ʒ
	int rows, cols; //��¼�����е���������������չʾ
	float offsetx, offsety; //չʾ�ĳ�ʼλ��
	const float height = 170; //Itemչʾ�Ĵ�С

	int equipIndex = 0; //��¼����װ���ı��
};

#endif
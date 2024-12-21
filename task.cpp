#include <SFML/Graphics.hpp>
#include <iostream>
#include <sqlite3.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include"func.h"
#include"player.h"
#include"task.h"
using namespace std;

sf::Texture texturecoin, texture_lq, texture_finish, texture_close;
vector<Button> taskbutton;
vector<string> taskButtonLabel = { "finish","back"};
float taskButtonWidth = 150;
float taskButtonHeight = 50;
float taskButtonSpace = 30;
float taskButtonStartX = (650 - taskButtonWidth) / 2.0f;
float taskButtonStartY = 280;//按钮的实现

sf::Font taskfont;
sf::Texture taskimage;
float taskscaleX, taskscaleY;
sf::Vector2u taskscreenSize(802, 602);
sf::Vector2u taskimageSize;

Task::Task(const string& text,const sf::Vector2f & pos,int& times){
	finishcnt = times;
	task.setFont(taskfont);
	task.setCharacterSize(24);
	task.setFillColor(sf::Color::Red);
	task.setPosition(pos);
	task.setString(text);

	finished.setFont(taskfont);
	finished.setCharacterSize(24);
	finished.setFillColor(sf::Color::Red);
	finished.setPosition(pos.x +200, pos.y);
	//Button temp=
	Button temp("", taskfont, sf::Vector2f(pos.x + 400, pos.y), sf::Vector2f(taskButtonWidth, taskButtonHeight));
	temp.changeColor(texture_lq);
	Taskbutton = temp;
	temp.changeColor(texture_finish);
	Taskbutton_red = temp;
	//cout << taskbutton->a << endl;
}
vector<Task> tsk;
int taskmain(player & account,int &times) {//返回一个当前的账户
	
	taskfont.loadFromFile("arial.ttf");
	if (!texturecoin.loadFromFile("coin.png")) {
		return -1;
	}
	if (!texture_lq.loadFromFile("lingqu.png")) {
		return -1;
	}
	if (!texture_finish.loadFromFile("finish.png")) {
		return -1;
	}
	if (!texture_close.loadFromFile("close.png")) {
		return -1;
	}
	sf::RenderWindow taskwindow(sf::VideoMode(802, 602), "tasks");
	taskbutton.emplace_back("", taskfont, sf::Vector2f(690, 500), sf::Vector2f(taskButtonWidth/2.5, taskButtonHeight));
	taskbutton[0].changeColor(texture_close);
	
	taskbutton.emplace_back("", taskfont, sf::Vector2f(115, 500), sf::Vector2f(taskButtonWidth / 2.5, taskButtonHeight));
	taskbutton[1].changeColor(texturecoin);
	taskwindow.clear();
	
	taskwindow.display();
	Task t = Task("1. watch a video", sf::Vector2f(150, 225),times);
	tsk.emplace_back(t);
	tsk[0].Taskbutton.Draw(taskwindow);//一个任务对象
	

	if (!taskimage.loadFromFile("taskbj.png")) {
		cout << "Error!Background not found" << endl;
		return -1;
	}
	sf::Sprite tasksprite(taskimage);
	taskimageSize = taskimage.getSize();
	taskscaleX = (float)taskscreenSize.x / taskimageSize.x;
	taskscaleY = (float)taskscreenSize.y / taskimageSize.y;
	tasksprite.setScale(taskscaleX, taskscaleY);//加载背景图片


	sf::Text tasks,Coin,count;
	


	Coin.setFont(taskfont);
	Coin.setCharacterSize(24);
	Coin.setFillColor(sf::Color::Red);
	Coin.setPosition(185,505);

	
	while (taskwindow.isOpen()) {
		sf::Event event;
		Coin.setString(to_string(account.getCoins()));
		//count.setString("Finished:" + to_string(cnt) + " times");
		taskwindow.draw(tasksprite);
		taskwindow.draw(Coin);
		//taskwindow.draw(count);
		taskbutton[0].Draw(taskwindow);
		taskbutton[1].Draw(taskwindow);
		for (auto& butt : tsk) {
			if (butt.finishcnt)
				butt.Taskbutton.Draw(taskwindow);
			else butt.Taskbutton_red.Draw(taskwindow);
			taskwindow.draw(butt.task);
			butt.finished.setString("finish:" + to_string(butt.finishcnt) + " times");
			taskwindow.draw(butt.finished);

		}
		taskwindow.display();
		while (taskwindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				taskwindow.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = taskwindow.mapPixelToCoords(sf::Mouse::getPosition(taskwindow));
					if (taskbutton[0].if_contain(MousePos)) {
						taskwindow.clear();
						taskwindow.display();
						taskwindow.close();
						tsk.clear();
						return 0;
					}
					for (auto& butt : tsk) {
						if (butt.Taskbutton.if_contain(MousePos)) {
							if (butt.finishcnt) {
								butt.finishcnt--;
								times--;
								account.addCoins(100);
								modifycoins(account.getName(), 100);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
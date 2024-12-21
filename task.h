
#ifndef TASK
#define TASK
#include <SFML/Graphics.hpp>
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include<windows.h>
#include <sstream>
#include"func.h"
#include"player.h"
using namespace std;
class Task {
public:
	int* TEst;
	int finishcnt;
	sf::Text task;
	sf::Text finished;
	Button Taskbutton;
	Button Taskbutton_red;

	Task(const string& text,const sf::Vector2f & pos,int& times);
	~Task() {
		
	}
};
int taskmain(player & temp,int& times);
#endif
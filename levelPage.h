#pragma once
#ifndef LEVELPAGE_H
#define LEVELPAGE_H
#include "level.h"

class levelPage {
public:
	levelPage();
	void initial();
	void draw();
	void openAccess(const int& index);

private:
	sf::RenderWindow window;
	vector<Level*> levels; //·ÅÁù¸ö¹Ø¿¨
	int challengeIndex = 1;
	const float scale_ = 0.714;
};

#endif
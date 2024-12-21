#pragma once
#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <functional>//for function
#include <iostream>
#include "game.h"
#include "textbox.h"
using namespace std;
using namespace sf;
const float scale = 0.5f;
extern int go;
extern int Type, Mode;
class menu {
public:
	menu();
	~menu();
	void initial();
	void drawall();
	void handleButton(const Event& event, const RenderWindow& window, function<void()> onClick);
private:
	RenderWindow stop_window;
	Sprite background;
	button continueGame, restartGame, exitGame;
	button selectPVP, selectPVPOL;
	button selectSnoke, selectChina, selectChallenge, whoFirst;
	Texture picture[21];
	textBox forIP, forPort;
};
#endif // !"CLIENT_H"
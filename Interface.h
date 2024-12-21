#pragma once
#include"gButton.h"
#include"avatar.h"
#include "player.h"
const int WINDOW_WIDTH = 802;
const int WINDOW_HEIGHT = 603;

enum class ScreenState { MainScreen, Avatar, Mode, History, Highlights, Viewing,Ranking, Settings, Mall, Game ,Fame,Full,Task};

void MainShow(ScreenState& state, sf::RenderWindow& window, player& temp);

void gMode(ScreenState& state, sf::RenderWindow& window, int& ModeChoice);
	
void Ranking(ScreenState& state, sf::RenderWindow& window);

void Viewing(ScreenState& state, sf::RenderWindow& window, sf::Music& sound);

void Settings(ScreenState& state, sf::RenderWindow& window, sf::Music& sound,int& Switch_Flag,string& MusicPath, float& volume, int& Acquiesce_Flag);

void Mall(ScreenState& state, sf::RenderWindow& window, player& temp);

void FullViewing(ScreenState& state, sf::RenderWindow& window, sf::Music& sound);

void FameViewing(ScreenState& state, sf::RenderWindow& window, sf::Music& sound);

void Task(ScreenState& state, sf::RenderWindow& window, player& temp,int & times);

int Dialogue(string name);
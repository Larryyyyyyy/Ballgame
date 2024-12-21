#ifndef REGISTER
#define REGISTER
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

void registerUser(const string& filename, sf::RenderWindow& window);
player check(const string& user);
player registermain();
player loginUser(const std::string& filename, sf::RenderWindow& window);
void findUser(sf::RenderWindow& window, player& user);
#endif
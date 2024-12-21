#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "game.h"
int hmain() {
	gameType Type = PVP;
	gameMode Mode = Snoke;
	//cin >> ip >> port;
	game x(Type,Mode,gameTrack{Ranked},0);
	return 0;
}
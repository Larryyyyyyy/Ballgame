#pragma once
#ifndef FMAIN_H
#define FMAIN_H
#include <iostream>
#include "Item.h"
#include "Store.h"
#include "ranking.h"
#include "player.h"
#include "avatar.h"

player fshop(player& account);
void franking();
void fshow(sf::RenderWindow& window, player& account);
#endif
#pragma once
#include <iostream>
#include "Item.h"
#include "Store.h"
#include "ranking.h"
#include "avatar.h"
#include "player.h"
#include "button_.h"
Inventory nowskin;
player lead;
player fshop(player& account)
{
	lead = account;
	avatar favatar(account.getName(), account.getpassword(), account.getmibao(), "images/Î¢ÐÅÍ¼Æ¬_20241211195719.jpg", account.getCoins(), account.getPoints());
	//²âÊÔÊý¾Ý
	//fAvatar* favatar = new fAvatar("Fuycdfang", "123456", "images/Î¢ÐÅÍ¼Æ¬_20241211195719.jpg");

	//²âÊÔStore
	Store store;
	store.draw(favatar.sticks, favatar.coins);

	//²âÊÔranking
	/*Ranking ranking;
	ranking.drawRanking();*/

	//²âÊÔProfile
	/*sf::RenderWindow window(sf::VideoMode(1500, 1000), "Test Window!");
	
	avatar->addCoins(1000);
	avatar->sticks->purchase(4);
	avatar->sticks->equip(4);

	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::White);
		avatar->drawProfile(window);
		window.display();
	}*/
	return lead;
}
void franking() {
	ranking ranking;
	ranking.drawRanking();
}
void fshow(sf::RenderWindow& window, player& account) {
	sf::RenderWindow fwindow(sf::VideoMode(1500, 1000), "Test Window!");
	avatar favatar(account.getName(), account.getpassword(), account.getmibao(), "images/Î¢ÐÅÍ¼Æ¬_20241211195719.jpg", account.getCoins(), account.getPoints());
	favatar.sticks->purchase(nowskin.getequipindex());
	favatar.sticks->equip(nowskin.getequipindex());

	while (fwindow.isOpen()) {
		sf::Event event;
		while (fwindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) fwindow.close();
		}

		fwindow.clear(sf::Color::White);
		favatar.drawProfile(fwindow);
		fwindow.display();
	}
}
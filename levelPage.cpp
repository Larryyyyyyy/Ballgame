#pragma once 
#include "LevelPage.h"
#include "game.h"

levelPage::levelPage() : window(sf::VideoMode(2180 * 0.5, 1800 * 0.5), "Table_Tennis_PVP") {
    initial();
}

void levelPage::initial() {
    //����ÿ���ؿ���λ��
    const int cols = 3;
    const float offsetx = 200 * scale_, offsety = 330 * scale_, height = 400 * scale_;
    int row = 0, col = 0;
    for (int index = 1; index <= 6; index++) //��¼ÿ���ؿ��Ƿ񿪷���
    {
        Level* level = new Level(index, { offsetx + col * height, offsety + row * (height - 70) }, window);
        levels.push_back(level);
        col == cols - 1 ? row++, col = 0 : col++;
    }

    levels[0]->openAccess();
}

void levelPage::draw() {
    //���ر���ͼƬ
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/Challenge.png");
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(scale_, scale_);

    button_ backButton({ 650 * scale_, 1000 * scale_ }, { 250 * scale_, 130 * scale_ }, "images/settlement_back.png", window, { 0, 0, 0 });

    bool buttonClicked = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));//���λ��

        //�������ؿ�
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (!buttonClicked) { //��ֹ��ť��ε��
                    //�������ѵ��
                    buttonClicked = 1;
                    int index = 0;
                    for (auto* level : levels) {
                        index++;
                        if (level->handleEvent(mousePosition)) {
                            game x(PVP, Challenge, Casual, index);
                            if (x.getChallengeIndex()) openAccess(index);
                        }
                    }

                    //�˳���ť
                    if (backButton.if_contain(mousePosition)) window.close();
                }
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) { //���ð�ť״̬
            if (event.mouseButton.button == sf::Mouse::Left) {
                buttonClicked = 0;
            }
        }
        //��Ⱦ
        window.clear();
        window.draw(backgroundSprite);
        backButton.Draw(window);
        for (auto* level : levels) level->draw(window);
        window.display();
    }
}

void levelPage::openAccess(const int& index) {
    if (index < 6) {
        levels[index]->openAccess();
    }
}
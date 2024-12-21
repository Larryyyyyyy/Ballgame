#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Ranking.h"
int WINDOW_WIDTH = 803, WINDOW_HEIGHT = 602;
ranking::ranking() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Real Time Ranking") {}

void ranking::drawRanking () {

    //��������*****
    avatar* avatar_ = new avatar("Fuyang", "123456", "images/΢��ͼƬ_20241211195719.jpg");
    avatar_->addPoints(100);
    registerAvatar(avatar_);

    avatar_ = new avatar("guuu", "123456", "images/΢��ͼƬ_20241211195734.jpg");
    avatar_->addPoints(300);
    registerAvatar(avatar_);

    avatar_ = new avatar("King of egg tart", "123456", "images/΢��ͼƬ_20241211201741.jpg");
    avatar_->addPoints(400);
    registerAvatar(avatar_);

    avatar_ = new avatar("i am pineapple", "123456", "images/pineapple.png");
    avatar_->addPoints(100);
    registerAvatar(avatar_);

    avatar_ = new avatar("i am orange", "123456", "images/orange.png");
    avatar_->addPoints(300);
    registerAvatar(avatar_);

    loginAvatar("Fuyang");

    //�˳���ť
    /*sf::Vector2f position(100, 150);
    sf::Vector2f size(120.0, 120.0);
    sf::Vector3f color(0, 0, 0);
    Button exitButton(position, size, "images/back_ranking.png", window, color);*/ //gzj������

    //���ö����̶�ͼƬ
    sf::Texture topTexture;
    topTexture.loadFromFile("images/ranking_largetop.png");
    sf::Sprite topSprite(topTexture);
    topSprite.setPosition(0, 0);
    topHeight = topSprite.getGlobalBounds().height;

    offsety = topHeight + 10.0f;

    //�������а����ҳ��
    //��ʾ����ͼ
    sf::Texture scrollTexture;
    scrollTexture.loadFromFile("images/ranking_largescroll.png");
    sf::Sprite scrollSprite(scrollTexture);
    scrollSprite.setPosition(0, topHeight);

    //��һ������ҳ��
    //������ʾ��Χ����windowһ����С
    sf::View scrollView(sf::FloatRect(0, topHeight, WINDOW_WIDTH, WINDOW_HEIGHT - topHeight));
    //������ʾ��Χ������window�ı���
    scrollView.setViewport(sf::FloatRect(0.0f, 0.407f, 1.0f, 0.593f));

    //���ù����ٶ�
    float scrollSpeed = 10.f;

    while (window.isOpen()) {
        //�¼�
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //������ٿع���
            else if (event.type == sf::Event::MouseWheelMoved) {

                float delta = event.mouseWheel.delta;

                //��ֹ��ͼԽ��
                //��ȡ��ͼ������λ������
                sf::Vector2f center = scrollView.getCenter();
                //������ͼ�Ŀ��
                float halfHeight = scrollView.getSize().y / 2;
                if (center.y - halfHeight + delta * scrollSpeed >= topHeight)
                    if (center.y + halfHeight + delta * scrollSpeed <= scrollTexture.getSize().y)
                        scrollView.move(0.0f, delta * scrollSpeed);
            }
        }

        //��Ⱦ����

        window.clear(sf::Color::White);

        window.draw(topSprite);
        //exitButton.Draw(window);


        //�����а��ϻ����������
        window.setView(scrollView);
        window.draw(scrollSprite);
        //��������Ұ���points����
        std::sort(avatars.begin(), avatars.end(), [](avatar* a, avatar* b) {
            return a->getPoints() > b->getPoints();
            });

        sf::Texture texture;
        sf::Sprite sprite;

        int index = 0, lastPoints = -1, ranking = 0;
        for (auto*& avatar : avatars) {

            index++;
            //��¼����
            if (lastPoints != avatar->getPoints()) { //����ͬ�����
                lastPoints = avatar->getPoints();
                ranking = index;
            }

            //��ʾ�û�������
            switch (ranking) {
            case 1: {
                texture.loadFromFile("images/ranking1.png");
                sprite.setTexture(texture);
                sprite.setPosition(offsetx - rankingSize - 10, offsety + (index - 1) * rowHeight - 10); //λ��
                sf::Vector2u size = texture.getSize();
                sprite.setScale(rankingSize / size.x, rankingSize / size.y); //ʵ��ͼƬ���Ź���
                window.draw(sprite);
                break;
            }
            case 2: {
                texture.loadFromFile("images/ranking2.png");
                sprite.setTexture(texture);
                sprite.setPosition(offsetx - rankingSize - 10, offsety + (index - 1) * rowHeight - 10); //λ��
                sf::Vector2u size = texture.getSize();
                sprite.setScale(rankingSize / size.x, rankingSize / size.y); //ʵ��ͼƬ���Ź���
                window.draw(sprite);
                break;
            }
            case 3: {
                texture.loadFromFile("images/ranking3.png");
                sprite.setTexture(texture);
                sprite.setPosition(offsetx - rankingSize - 10, offsety + (index - 1) * rowHeight - 10); //λ��
                sf::Vector2u size = texture.getSize();
                sprite.setScale(rankingSize / size.x, rankingSize / size.y); //ʵ��ͼƬ���Ź���
                window.draw(sprite);
                break;
            }
            default: {
                //����һ��Ҫ��Ҫ��ע���ʱ��Ԥ����
                sf::Text text;
                sf::Font font;
                font.loadFromFile("fonts/BASKVILL.TTF"); //����
                text.setFont(font);
                text.setString(std::to_string(ranking));
                text.setCharacterSize(rankingSize - 25);
                text.setFillColor(sf::Color::Black);
                text.setPosition(offsetx - rankingSize + 20, offsety + (index - 1) * rowHeight - 20); //����λ��
                window.draw(text);
            }
            }

            //��ʾ�û����֡�ͷ�񡢻���
            avatar->drawRanking(window, offsetx, offsety + (index - 1) * rowHeight, avatar == currentAvatar);

        }


        window.setView(window.getDefaultView());

        window.display();
    }
}

void ranking::registerAvatar(avatar* avatar) { //ע�����û�������һ���ǼǺ���Ϣ��avatar�������Ϊ����
    avatars.push_back(avatar);
    loginAvatar(avatar->getName()); //ע��ʱ˳�ֵ�¼��
}

void ranking::loginAvatar(const std::string& name) { //��¼�û�����¼��ǰ���
    for (auto* avatar : avatars)
        if (avatar->getName() == name) currentAvatar = avatar;
}
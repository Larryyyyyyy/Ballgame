#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Store.h"

//const int WINDOW_WIDTH = 2180;
//const int WINDOW_HEIGHT = 1500;

Store::Store() : window(sf::VideoMode(2180, 1500), "Welcome to Billiards Store!") {}

//���̵��ϻ��ƴ��е�ǰ�û���Ϣ��Inventory�����sticks
void Store::draw(Inventory* sticks, int &coins) {

    sticks->setPosition(window);

    //Error����Ҳ���
    sf::Text errorText;
    sf::Font font;
    font.loadFromFile("fonts/BASKVILL.TTF");
    errorText.setFont(font); // ��������
    errorText.setString("You don't have enough coins!"); // ����Ҫ��ʾ���ı�
    errorText.setCharacterSize(100); // �����ַ���С
    errorText.setFillColor(sf::Color::Red); // �����ı���ɫ
    errorText.setPosition(400, 700); // �����ı�λ��

    //���Сͼ��
    sf::Texture coinsTexture;
    coinsTexture.loadFromFile("images/coins.png");
    sf::Sprite coinsSprite(coinsTexture);
    coinsSprite.setPosition(1700, 110);
    sf::Vector2u coinsSize = coinsTexture.getSize();
    coinsSprite.setScale(100.0/coinsSize.x, 100.0/coinsSize.y); //ʵ��ͼƬ���Ź���

    //��ʾ�������
    sf::Text coinsText;
    font.loadFromFile("fonts/WangHanZongCuHeiTiYiShiYin-1.TTF");
    coinsText.setFont(font);
    coinsText.setString(std::to_string(coins));
    coinsText.setCharacterSize(100);
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setPosition(1800, 100);

    //�˳���ť
    sf::Vector2f position(100, 100);
    sf::Vector2f size(250.0, 150.0);
    sf::Vector3f color(0.0, 0.0, 0.0);
    button_ exitButton(position, size, "images/back.png", window, color);

    //����һ��������
    //���ö����̶�ͼƬ
    sf::Texture topTexture;
    topTexture.loadFromFile("images/shop_top.png");
    sf::Sprite topSprite(topTexture);
    topSprite.setPosition(0, 0);
    const int topHeight = topSprite.getGlobalBounds().height;
    const int offsety = topHeight + 10.0f;

    //���õײ��̶�ͼƬ
    sf::Texture bottomTexture;
    bottomTexture.loadFromFile("images/store_bottom.png");
    sf::Sprite bottomSprite(bottomTexture);
    const int bottomHeight = bottomSprite.getGlobalBounds().height;
    bottomSprite.setPosition(0, 1500 - bottomHeight);

    //�����̵����ҳ��
    //��ʾ����ͼ
    sf::Texture scrollTexture;
    scrollTexture.loadFromFile("images/store_scroll.png");
    sf::Sprite scrollSprite(scrollTexture);
    scrollSprite.setPosition(0, topHeight);

    //��һ������ҳ��
    //������ʾ��Χ����windowһ����С
    sf::View scrollView(sf::FloatRect(0, topHeight, 2180, 1500 - topHeight - bottomHeight));
    //������ʾ��Χ������window�ı���
    scrollView.setViewport(sf::FloatRect(0.0f, 0.2227f, 1.0f, 0.718f)); //�������

    //���ù����ٶ�
    float scrollSpeed = 10.f;

    //��ȡ�����center������ƫ����
    sf::Vector2f center0 = scrollView.getCenter();

    //��Ϸ��ѭ��
    bool buttonClicked = 0;
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
                //������ͼ��һ��߶�
                float halfHeight = scrollView.getSize().y / 2;

                //�������������ͼ��Χ����ִ�й���
                if (center.y - halfHeight + delta * scrollSpeed >= topHeight)
                    if (center.y + halfHeight + delta * scrollSpeed <= scrollTexture.getSize().y)
                        scrollView.move(0.0f, delta * scrollSpeed);
            }
        }

        //ʵ�ֲ���
        if (showError && clock.getElapsedTime().asSeconds() > 2.0f) showError = 0; //������󾯸棨��ʾ���룩
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (!buttonClicked) { //��ֹ��ť��ε��
                    //�������ѵ��
                    buttonClicked = 1;

                    //��ȡ�������λ��
                    sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    //������Ϊ������View��ƽ�ƣ���������ƫ����
                    int offsety = scrollView.getCenter().y - center0.y;
                    //std::cout << offsety << std::end;

                    //�����Ҳ����򴥷���Ҳ�����ʾ
                    if (sticks->handleEvent({position.x, position.y + offsety}, coins) == -1) purchaseError();
                }
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) { //���ð�ť״̬
            if (event.mouseButton.button == sf::Mouse::Left) {
                buttonClicked = 0;
            }
        }

        //��Ⱦ����
        window.clear();

        window.setView(scrollView);
        window.draw(scrollSprite);
        sticks->draw(window); //������Ʒ
        window.setView(window.getDefaultView());

        window.draw(topSprite);
        exitButton.Draw(window);
        window.draw(coinsSprite);
        coinsText.setString(std::to_string(coins));
        window.draw(coinsText);
        window.draw(bottomSprite);

        if (showError) window.draw(errorText);

        window.display();
    }
}

//������Ҳ���Ĵ���
void Store::purchaseError() { //����ɳ���3��
    showError = 1; //��ǲ�������
    clock.restart(); //���¿�ʼ��ʱ
}
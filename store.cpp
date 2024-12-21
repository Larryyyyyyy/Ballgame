#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Store.h"

//const int WINDOW_WIDTH = 2180;
//const int WINDOW_HEIGHT = 1500;

Store::Store() : window(sf::VideoMode(2180, 1500), "Welcome to Billiards Store!") {}

//在商店上绘制带有当前用户信息的Inventory类对象sticks
void Store::draw(Inventory* sticks, int &coins) {

    sticks->setPosition(window);

    //Error：金币不足
    sf::Text errorText;
    sf::Font font;
    font.loadFromFile("fonts/BASKVILL.TTF");
    errorText.setFont(font); // 设置字体
    errorText.setString("You don't have enough coins!"); // 设置要显示的文本
    errorText.setCharacterSize(100); // 设置字符大小
    errorText.setFillColor(sf::Color::Red); // 设置文本颜色
    errorText.setPosition(400, 700); // 设置文本位置

    //金币小图标
    sf::Texture coinsTexture;
    coinsTexture.loadFromFile("images/coins.png");
    sf::Sprite coinsSprite(coinsTexture);
    coinsSprite.setPosition(1700, 110);
    sf::Vector2u coinsSize = coinsTexture.getSize();
    coinsSprite.setScale(100.0/coinsSize.x, 100.0/coinsSize.y); //实现图片缩放功能

    //显示金币数量
    sf::Text coinsText;
    font.loadFromFile("fonts/WangHanZongCuHeiTiYiShiYin-1.TTF");
    coinsText.setFont(font);
    coinsText.setString(std::to_string(coins));
    coinsText.setCharacterSize(100);
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setPosition(1800, 100);

    //退出按钮
    sf::Vector2f position(100, 100);
    sf::Vector2f size(250.0, 150.0);
    sf::Vector3f color(0.0, 0.0, 0.0);
    button_ exitButton(position, size, "images/back.png", window, color);

    //设置一个滑动屏
    //设置顶部固定图片
    sf::Texture topTexture;
    topTexture.loadFromFile("images/shop_top.png");
    sf::Sprite topSprite(topTexture);
    topSprite.setPosition(0, 0);
    const int topHeight = topSprite.getGlobalBounds().height;
    const int offsety = topHeight + 10.0f;

    //设置底部固定图片
    sf::Texture bottomTexture;
    bottomTexture.loadFromFile("images/store_bottom.png");
    sf::Sprite bottomSprite(bottomTexture);
    const int bottomHeight = bottomSprite.getGlobalBounds().height;
    bottomSprite.setPosition(0, 1500 - bottomHeight);

    //创建商店滚动页面
    //显示背景图
    sf::Texture scrollTexture;
    scrollTexture.loadFromFile("images/store_scroll.png");
    sf::Sprite scrollSprite(scrollTexture);
    scrollSprite.setPosition(0, topHeight);

    //做一个滚动页面
    //控制显示范围，和window一样大小
    sf::View scrollView(sf::FloatRect(0, topHeight, 2180, 1500 - topHeight - bottomHeight));
    //设置显示范围在整个window的比例
    scrollView.setViewport(sf::FloatRect(0.0f, 0.2227f, 1.0f, 0.718f)); //计算比例

    //设置滚动速度
    float scrollSpeed = 10.f;

    //获取最初的center，计算偏移量
    sf::Vector2f center0 = scrollView.getCenter();

    //游戏主循环
    bool buttonClicked = 0;
    while (window.isOpen()) {
        //事件
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //鼠标滚轴操控滚屏
            else if (event.type == sf::Event::MouseWheelMoved) {

                float delta = event.mouseWheel.delta;

                //防止视图越界
                
                //获取视图的中心位置坐标
                sf::Vector2f center = scrollView.getCenter();
                //计算视图的一半高度
                float halfHeight = scrollView.getSize().y / 2;

                //如果滚屏超出视图范围，则不执行滚屏
                if (center.y - halfHeight + delta * scrollSpeed >= topHeight)
                    if (center.y + halfHeight + delta * scrollSpeed <= scrollTexture.getSize().y)
                        scrollView.move(0.0f, delta * scrollSpeed);
            }
        }

        //实现部分
        if (showError && clock.getElapsedTime().asSeconds() > 2.0f) showError = 0; //处理错误警告（显示两秒）
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (!buttonClicked) { //防止按钮多次点击
                    //标记鼠标已点击
                    buttonClicked = 1;

                    //获取鼠标点击的位置
                    sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    //计算因为滚屏（View的平移）而产生的偏移量
                    int offsety = scrollView.getCenter().y - center0.y;
                    //std::cout << offsety << std::end;

                    //如果金币不足则触发金币不足显示
                    if (sticks->handleEvent({position.x, position.y + offsety}, coins) == -1) purchaseError();
                }
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) { //重置按钮状态
            if (event.mouseButton.button == sf::Mouse::Left) {
                buttonClicked = 0;
            }
        }

        //渲染部分
        window.clear();

        window.setView(scrollView);
        window.draw(scrollSprite);
        sticks->draw(window); //绘制商品
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

//触发金币不足的错误
void Store::purchaseError() { //处理成出现3秒
    showError = 1; //标记操作错误
    clock.restart(); //重新开始计时
}
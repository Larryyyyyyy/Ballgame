#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Ranking.h"
int WINDOW_WIDTH = 803, WINDOW_HEIGHT = 602;
ranking::ranking() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Real Time Ranking") {}

void ranking::drawRanking () {

    //测试数据*****
    avatar* avatar_ = new avatar("Fuyang", "123456", "images/微信图片_20241211195719.jpg");
    avatar_->addPoints(100);
    registerAvatar(avatar_);

    avatar_ = new avatar("guuu", "123456", "images/微信图片_20241211195734.jpg");
    avatar_->addPoints(300);
    registerAvatar(avatar_);

    avatar_ = new avatar("King of egg tart", "123456", "images/微信图片_20241211201741.jpg");
    avatar_->addPoints(400);
    registerAvatar(avatar_);

    avatar_ = new avatar("i am pineapple", "123456", "images/pineapple.png");
    avatar_->addPoints(100);
    registerAvatar(avatar_);

    avatar_ = new avatar("i am orange", "123456", "images/orange.png");
    avatar_->addPoints(300);
    registerAvatar(avatar_);

    loginAvatar("Fuyang");

    //退出按钮
    /*sf::Vector2f position(100, 150);
    sf::Vector2f size(120.0, 120.0);
    sf::Vector3f color(0, 0, 0);
    Button exitButton(position, size, "images/back_ranking.png", window, color);*/ //gzj已设置

    //设置顶部固定图片
    sf::Texture topTexture;
    topTexture.loadFromFile("images/ranking_largetop.png");
    sf::Sprite topSprite(topTexture);
    topSprite.setPosition(0, 0);
    topHeight = topSprite.getGlobalBounds().height;

    offsety = topHeight + 10.0f;

    //创建排行榜滚动页面
    //显示背景图
    sf::Texture scrollTexture;
    scrollTexture.loadFromFile("images/ranking_largescroll.png");
    sf::Sprite scrollSprite(scrollTexture);
    scrollSprite.setPosition(0, topHeight);

    //做一个滚动页面
    //控制显示范围，和window一样大小
    sf::View scrollView(sf::FloatRect(0, topHeight, WINDOW_WIDTH, WINDOW_HEIGHT - topHeight));
    //设置显示范围在整个window的比例
    scrollView.setViewport(sf::FloatRect(0.0f, 0.407f, 1.0f, 0.593f));

    //设置滚动速度
    float scrollSpeed = 10.f;

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
                //计算视图的宽度
                float halfHeight = scrollView.getSize().y / 2;
                if (center.y - halfHeight + delta * scrollSpeed >= topHeight)
                    if (center.y + halfHeight + delta * scrollSpeed <= scrollTexture.getSize().y)
                        scrollView.move(0.0f, delta * scrollSpeed);
            }
        }

        //渲染部分

        window.clear(sf::Color::White);

        window.draw(topSprite);
        //exitButton.Draw(window);


        //在排行榜上绘制所有玩家
        window.setView(scrollView);
        window.draw(scrollSprite);
        //将所有玩家按照points排序
        std::sort(avatars.begin(), avatars.end(), [](avatar* a, avatar* b) {
            return a->getPoints() > b->getPoints();
            });

        sf::Texture texture;
        sf::Sprite sprite;

        int index = 0, lastPoints = -1, ranking = 0;
        for (auto*& avatar : avatars) {

            index++;
            //记录排名
            if (lastPoints != avatar->getPoints()) { //处理同分情况
                lastPoints = avatar->getPoints();
                ranking = index;
            }

            //显示用户的排名
            switch (ranking) {
            case 1: {
                texture.loadFromFile("images/ranking1.png");
                sprite.setTexture(texture);
                sprite.setPosition(offsetx - rankingSize - 10, offsety + (index - 1) * rowHeight - 10); //位置
                sf::Vector2u size = texture.getSize();
                sprite.setScale(rankingSize / size.x, rankingSize / size.y); //实现图片缩放功能
                window.draw(sprite);
                break;
            }
            case 2: {
                texture.loadFromFile("images/ranking2.png");
                sprite.setTexture(texture);
                sprite.setPosition(offsetx - rankingSize - 10, offsety + (index - 1) * rowHeight - 10); //位置
                sf::Vector2u size = texture.getSize();
                sprite.setScale(rankingSize / size.x, rankingSize / size.y); //实现图片缩放功能
                window.draw(sprite);
                break;
            }
            case 3: {
                texture.loadFromFile("images/ranking3.png");
                sprite.setTexture(texture);
                sprite.setPosition(offsetx - rankingSize - 10, offsety + (index - 1) * rowHeight - 10); //位置
                sf::Vector2u size = texture.getSize();
                sprite.setScale(rankingSize / size.x, rankingSize / size.y); //实现图片缩放功能
                window.draw(sprite);
                break;
            }
            default: {
                //考虑一下要不要在注册的时候预处理
                sf::Text text;
                sf::Font font;
                font.loadFromFile("fonts/BASKVILL.TTF"); //字体
                text.setFont(font);
                text.setString(std::to_string(ranking));
                text.setCharacterSize(rankingSize - 25);
                text.setFillColor(sf::Color::Black);
                text.setPosition(offsetx - rankingSize + 20, offsety + (index - 1) * rowHeight - 20); //设置位置
                window.draw(text);
            }
            }

            //显示用户名字、头像、积分
            avatar->drawRanking(window, offsetx, offsety + (index - 1) * rowHeight, avatar == currentAvatar);

        }


        window.setView(window.getDefaultView());

        window.display();
    }
}

void ranking::registerAvatar(avatar* avatar) { //注册新用户，传递一个登记好信息的avatar类对象作为参数
    avatars.push_back(avatar);
    loginAvatar(avatar->getName()); //注册时顺手登录了
}

void ranking::loginAvatar(const std::string& name) { //登录用户，记录当前玩家
    for (auto* avatar : avatars)
        if (avatar->getName() == name) currentAvatar = avatar;
}
#pragma once
#ifndef TEXT_H
#define TEXT_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class text {
public:
    text();
    ~text();
    void initializeInfoBox(float x, float y, float width, float height, float scale, Color color);
    void showMessage(const string& message);
    void updateInfoBox();
    Font font;//用于加载字体
    Text infoText;//用于显示文字
    RectangleShape textBox;//文字框的背景
    string currentMessage;//当前显示的信息
    Clock messageClock;//用于计时
    float messageDuration = 2.0f;//信息显示的持续时间（秒）
private:
};
#endif // !"TEXT_H"
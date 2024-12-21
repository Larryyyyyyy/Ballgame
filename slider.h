#pragma once
#ifndef SLIDER_H
#define SLIDER_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class slider {
public:
    slider();
    void initializeslider(float x, float y, float width, float height, float minVal, float maxVal);
    RectangleShape background;//滑动条背景
    RectangleShape handle;//滑块
    bool isDragging;//是否正在拖动滑块
    float minValue, maxValue;//参数的最小值和最大值
    float currentValue;//当前值
private:
};
#endif // !"CLIENT_H"
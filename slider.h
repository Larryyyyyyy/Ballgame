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
    RectangleShape background;//����������
    RectangleShape handle;//����
    bool isDragging;//�Ƿ������϶�����
    float minValue, maxValue;//��������Сֵ�����ֵ
    float currentValue;//��ǰֵ
private:
};
#endif // !"CLIENT_H"
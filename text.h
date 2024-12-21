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
    Font font;//���ڼ�������
    Text infoText;//������ʾ����
    RectangleShape textBox;//���ֿ�ı���
    string currentMessage;//��ǰ��ʾ����Ϣ
    Clock messageClock;//���ڼ�ʱ
    float messageDuration = 2.0f;//��Ϣ��ʾ�ĳ���ʱ�䣨�룩
private:
};
#endif // !"TEXT_H"
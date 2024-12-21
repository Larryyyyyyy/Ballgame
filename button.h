#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class button {
public:
    button();
    ~button();
    void initiallizeButton(float x, float y, float width, float height, const string& text, float scale, Color dColor, Color hColor, Color cColor);
    Font font;
    Text buttonText;
    RectangleShape shape;
    Color defaultColor, hoverColor, clickColor;
private:
};
#endif // !"BUTTON_H"
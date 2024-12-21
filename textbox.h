#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <functional>//for function
#include <iostream>
using namespace std;
using namespace sf;
extern string ip;
extern int port;
class textBox {
public:
    textBox();
    ~textBox();
    void initial(float x, float y, float width, float height);
    void handleEvent(const Event& event);
    void checkFocus(Vector2i mousePos);
    void update();
    string getInputText() const;
    RectangleShape background;
    Text text;

private:
    Font font;
    string inputText;
    bool hasFocus;
};
#endif // !"TEXTBOX_H"
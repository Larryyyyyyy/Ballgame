#include "textbox.h"
textBox::textBox() {
    if (!font.loadFromFile("resources/arial.ttf")) {
        cerr << "Failed to load font!" << std::endl;
    }
}
textBox::~textBox() {}
void textBox::initial(float x, float y, float width, float height) {
    background.setSize(Vector2f(width, height));
    background.setFillColor(Color::White);
    background.setPosition(x, y);
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::Black);
    text.setPosition(x + 5, y + 5);
    inputText = "";
    hasFocus = false;
}
void textBox::handleEvent(const Event& event) {
    if (hasFocus) {
        if (event.type == Event::TextEntered) {
            if (event.text.unicode < 128) {//只处理可打印字符
                char enteredChar = static_cast<char>(event.text.unicode);
                if (enteredChar == '\b' && inputText.length() > 0) {//Backspace
                    inputText.pop_back();
                }
                else if (enteredChar != '\b') {
                    inputText += enteredChar;
                }
            }
        }
    }
}
void textBox::checkFocus(Vector2i mousePos) {
    FloatRect bounds = background.getGlobalBounds();
    if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        hasFocus = true;
    }
    else {
        hasFocus = false;
    }
}
void textBox::update() {
    text.setString(inputText);
}
string textBox::getInputText() const {
    return inputText;
}

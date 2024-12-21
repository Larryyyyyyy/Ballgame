#include "text.h"
text::text() {
    if (!font.loadFromFile("resources/arial.ttf")) {
        cerr << "Error loading font!" << endl;
    }
}
text::~text() {}
//初始化文字框
void text::initializeInfoBox(float x, float y, float width, float height, float scale, Color color) {
    infoText.setFont(font);
    infoText.setCharacterSize(50 * scale);
    infoText.setFillColor(color);
    infoText.setPosition(x, y);
    textBox.setSize(Vector2f(width, height));
    textBox.setFillColor(Color(31, 30, 51));
    textBox.setPosition(x, y);
}
//显示某个信息
void text::showMessage(const string& message) {
    currentMessage = message;
    infoText.setString(currentMessage);
    messageClock.restart();
}
//更新文字框
void text::updateInfoBox() {
    if (messageClock.getElapsedTime().asSeconds() > messageDuration) {
        currentMessage.clear();
        infoText.setString("");//清空文字
    }
}

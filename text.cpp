#include "text.h"
text::text() {
    if (!font.loadFromFile("resources/arial.ttf")) {
        cerr << "Error loading font!" << endl;
    }
}
text::~text() {}
//��ʼ�����ֿ�
void text::initializeInfoBox(float x, float y, float width, float height, float scale, Color color) {
    infoText.setFont(font);
    infoText.setCharacterSize(50 * scale);
    infoText.setFillColor(color);
    infoText.setPosition(x, y);
    textBox.setSize(Vector2f(width, height));
    textBox.setFillColor(Color(31, 30, 51));
    textBox.setPosition(x, y);
}
//��ʾĳ����Ϣ
void text::showMessage(const string& message) {
    currentMessage = message;
    infoText.setString(currentMessage);
    messageClock.restart();
}
//�������ֿ�
void text::updateInfoBox() {
    if (messageClock.getElapsedTime().asSeconds() > messageDuration) {
        currentMessage.clear();
        infoText.setString("");//�������
    }
}

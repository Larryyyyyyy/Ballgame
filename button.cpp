#include "button.h"
button::button() {
    if (!font.loadFromFile("resources/arial.ttf")) {
        cerr << "Error loading font!" << endl;
    }
}
button::~button() {}
void button::initiallizeButton(float x, float y, float width, float height, const string& text, float scale, Color dColor, Color hColor, Color cColor) {
    defaultColor = dColor;//默认颜色
    hoverColor = hColor; //悬停颜色
    clickColor = cColor;//点击颜色
    shape.setPosition(x, y);
    shape.setSize({ width, height });
    shape.setFillColor(defaultColor);
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(50 * scale);
    buttonText.setFillColor(Color::White);
    FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    buttonText.setPosition(x + width / 2, y + height / 2);
}
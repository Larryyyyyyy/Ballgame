#include "slider.h"
slider::slider() :isDragging(false) {}
void slider::initializeslider(float x, float y, float width, float height, float minVal, float maxVal) {
    minValue = minVal;
    maxValue = maxVal;
    currentValue = minVal;
    background.setSize(Vector2f(width, height));
    background.setFillColor(Color(200, 200, 200));
    background.setPosition(x, y);
    handle.setSize(Vector2f(20, height + 10));//ª¨øÈ…‘¥Û“ªµ„
    handle.setFillColor(Color(100, 100, 250));
    handle.setPosition(x, y - 5);
}
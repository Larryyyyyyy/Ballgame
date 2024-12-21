#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"
#include"fmain.h"
void Mall(ScreenState& state, sf::RenderWindow& window,player & temp)
{
    sf::Font font;
    if (!font.loadFromFile("BASKVILL.ttf"))
    {
        return;
    }

    //加载退出键
    gButton BackButton = Back_Button(window);
    //设置主页按键
    gButton HomeButton = Home_Button(window);
    // 使矩形透明，仅用于表示区域
    BackButton.m_Rect.setFillColor(sf::Color::Transparent);
    HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

    while (window.isOpen() && state == ScreenState::Mall)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton,HomeButton, ScreenState::MainScreen);
        }
        temp=fshop(temp);
        state= ScreenState::MainScreen;
        window.clear();
        window.display();
    }
}
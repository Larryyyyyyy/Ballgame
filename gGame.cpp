#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"
#include"gGame.h"

void Game(ScreenState& state, sf::RenderWindow& window, int& ModeChoice)
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

    while (window.isOpen() && state == ScreenState::Game)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton,HomeButton, ScreenState::Mode);
        }

        window.clear();
        BackButton.Draw(window);
        HomeButton.Draw(window);
        window.display();
    }
}
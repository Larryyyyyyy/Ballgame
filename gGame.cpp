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

    //�����˳���
    gButton BackButton = Back_Button(window);
    //������ҳ����
    gButton HomeButton = Home_Button(window);
    // ʹ����͸���������ڱ�ʾ����
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
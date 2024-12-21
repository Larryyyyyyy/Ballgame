#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"
#include"fmain.h"
void Ranking(ScreenState& state, sf::RenderWindow& window)
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

    while (window.isOpen() && state == ScreenState::Ranking)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton, HomeButton,ScreenState::MainScreen);
        }
        franking();
        state = ScreenState::MainScreen;
        window.clear();
        BackButton.Draw(window);
        HomeButton.Draw(window);
        window.display();
    }
}
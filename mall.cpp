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

    //�����˳���
    gButton BackButton = Back_Button(window);
    //������ҳ����
    gButton HomeButton = Home_Button(window);
    // ʹ����͸���������ڱ�ʾ����
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
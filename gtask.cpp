#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"
#include"player.h"
#include"func.h"
#include"task.h"
void Task(ScreenState& state, sf::RenderWindow& window,player& temp,int &times)
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

    while (window.isOpen() && state == ScreenState::Task)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton, HomeButton, ScreenState::MainScreen);
        }
        taskmain(temp,times);
        state = ScreenState::MainScreen;
        window.clear();
        window.display();
        return;
        
    }
}
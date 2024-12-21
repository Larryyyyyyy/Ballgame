#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"
#include"gGame.h"
#include"button.h"
#include"client.h"
#include"game.h"
#include"text.h"
#include"hmain.h"
void gMode(ScreenState& state, sf::RenderWindow& window, int& ModeChoice)
{
    sf::Font font;
    if (!font.loadFromFile("BASKVILL.ttf"))
    {
        return;
    }

    //���뱳��ͼ
    //���õĽ��汳��������
    vector<sf::Texture*> Backgrounds;
    Backgrounds.resize(2);
    for (int i = 0; i < 2; i++)
    {
        sf::Texture background;
        string path = "ModeBackground.png";
        if (!background.loadFromFile(path))
        {
            return;
        }
        Backgrounds[i] = new sf::Texture(background);
    }
    //���õĽ���ľ���
    sf::Sprite BackgroundSprite1(*Backgrounds[0]);
    BackgroundSprite1.setPosition(sf::Vector2f(0, 0));
    BackgroundSprite1.setScale(sf::Vector2f(1.f, 1.f));
    sf::Sprite BackgroundSprite2(*Backgrounds[1]);
    BackgroundSprite2.setPosition(sf::Vector2f(0, 492));
    BackgroundSprite2.setScale(sf::Vector2f(1.f, 1.f));


    //��ͼ
    sf::View MainView(sf::FloatRect(0, 0, 802, 603));
    //MainView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    //����С����ͼ
    sf::View MiniView(sf::FloatRect(0,111,802,492));
    MiniView.setViewport(sf::FloatRect(0.f,0.18407f,1.f, 0.81592f));
    //����һ����ͼ����
    sf::RectangleShape ViewRec;
    ViewRec.setPosition(sf::Vector2f(0, 111));
    ViewRec.setSize(sf::Vector2f(802, 492));//?

    vector<gButton*> Modes = { nullptr };
    Modes.resize(7);
    //�����ָ�����ɫ
    vector<gButton*> Intervals = { nullptr };
    Intervals.resize(6);
    for (int i = 0; i < 7; i++)
    {
        string Path_Of_Mode = "Mode" + to_string(i+1) + ".png";
        //Button(const sf::Vector2f& position, const sf::Vector2f& size, const string& path, sf::RenderWindow& window, const sf::Vector3f& color);
        Modes[i] = new gButton(sf::Vector2f(0.f+i*273,111.f), sf::Vector2f(257.f,381.f), Path_Of_Mode, window, sf::Vector3f(0.f, 0.f, 0.f));
        Modes[i]->m_Rect.setFillColor(sf::Color::Transparent);
        if (i != 6)
        {
            Intervals[i] = new gButton(sf::Vector2f(257+i*273,111.f), sf::Vector2f(16.f,381.f), "ModeInterval.png", window, sf::Vector3f(0.f, 0.f, 0.f));
            Intervals[i]->m_Rect.setFillColor(sf::Color::Transparent);
        }
    }


    //�����˳���
    gButton BackButton = Back_Button(window);
    //������ҳ����
    gButton HomeButton = Home_Button(window);
    // ʹ����͸���������ڱ�ʾ����
    BackButton.m_Rect.setFillColor(sf::Color::Transparent);
    HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

    //����ƫ��ֵ
    float scroll = 0;

    while (window.isOpen() && state == ScreenState::Mode)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton, HomeButton,ScreenState::MainScreen);

            for (int i = 0; i < 7; i++)
            {
                Suspention(window, Modes[i]);
            }


            //����
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                sf::Vector2i MousePos = sf::Mouse::getPosition(window);
                    scroll -= event.mouseWheelScroll.delta * 80;
                    scroll = (scroll > 1092) ? 1092 : scroll;
                    scroll = (scroll < 0) ? 0 : scroll;
            }

            //���������Ϸ
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int i = 0; i < 6; i++)
                {
                    if (Modes[i]->if_contain(MousePos))
                    {
                        ModeChoice = i + 1;
                        state = ScreenState::Game; // �л�����һ������
                        hmain();
                       // dsfdsafadfdsafas
                        return;
                    }
                }
            }
        }

        //����
        //����ͼƬλ��
        for (int i = 0; i < 7; i++)
        {
            Modes[i]->ButtonSprite.setPosition(sf::Vector2f(0.f + i * 273 - scroll, 111.f));
            Modes[i]->m_Rect.setPosition(sf::Vector2f(0.f + i * 273 - scroll, 111.f));
            if (i != 6)
            {
                Intervals[i]->ButtonSprite.setPosition(sf::Vector2f(257 + i * 273 - scroll, 111.f));
                Intervals[i]->m_Rect.setPosition(sf::Vector2f(257 + i * 273 - scroll, 111.f));
            }
        }

        window.clear();

        window.setView(MiniView);
        for (int i = 0; i < 7; i++)
        {
            if (i != 6)
            {
                Intervals[i]->Draw(window);
            }
            Modes[i]->Draw(window);
        }

        window.setView(MainView);
        window.draw(BackgroundSprite1);
        window.draw(BackgroundSprite2);
        BackButton.Draw(window);
        HomeButton.Draw(window);
        window.display();
    }
    for (int i = 0; i < 7; ++i)
    {
        if (Modes[i] != nullptr)
        {
            delete Modes[i];
            Modes[i] = nullptr;
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        if (Intervals[i] != nullptr)
        {
            delete Intervals[i];
            Intervals[i] = nullptr;
        }
    }
}
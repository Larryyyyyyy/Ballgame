#include"gButton.h"
#include"Interface.h"
#include"BacisFunction.h"
extern int watchtimes;
void Viewing(ScreenState& state, sf::RenderWindow& window, sf::Music& sound)
{
    sf::Font font;
    if (!font.loadFromFile("BASKVILL.ttf"))
    {
        return;
    }

    sf::Vector2f YiewBackgroundPosition(0,0);
    sf::Vector2f YiewBackgroundSize(802,603);
    gButton YiewBackgroundButton(YiewBackgroundPosition, YiewBackgroundSize, "FameBackground.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    YiewBackgroundButton.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f FamePosition(123,129);
    sf::Vector2f FameSize(552,166);
    gButton FameButton(FamePosition, FameSize, "Fame.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    FameButton.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f FullPosition(123, 314);
    sf::Vector2f FullSize(552,166);
    gButton FullButton(FullPosition, FullSize, "Full.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    FullButton.m_Rect.setFillColor(sf::Color::Transparent);

    //加载退出键
    gButton BackButton = Back_Button(window);
    //设置主页按键
    gButton HomeButton = Home_Button(window);
    // 使矩形透明，仅用于表示区域
    BackButton.m_Rect.setFillColor(sf::Color::Transparent);
    HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

    while (window.isOpen() && state == ScreenState::Viewing)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton, HomeButton, ScreenState::MainScreen);

            Suspention(window, &FameButton);
            Suspention(window, &FullButton);

            sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::MouseButtonReleased)
            {
                //判断左键点击
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (FameButton.if_contain(MousePos))
                    {
                        state = ScreenState::Fame; // 切换到另一个界面
                        return;
                    }
                    if (FullButton.if_contain(MousePos))
                    {
                        state = ScreenState::Full; // 切换到另一个界面
                        return;
                    }
                }
            }
        }

        window.clear();

        YiewBackgroundButton.Draw(window);

        FameButton.Draw(window);

        FullButton.Draw(window);

        BackButton.Draw(window);

        HomeButton.Draw(window);

        window.display();
    }
}

void FameViewing(ScreenState& state, sf::RenderWindow& window, sf::Music& sound)
{
    sf::Font font;
    if (!font.loadFromFile("BASKVILL.ttf"))
    {
        return;
    }

    sf::Vector2f YiewBackgroundPosition(0, 0);
    sf::Vector2f YiewBackgroundSize(802, 603);
    gButton YiewBackgroundButton(YiewBackgroundPosition, YiewBackgroundSize, "FameBackground.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    YiewBackgroundButton.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f Position1(136,62);
    sf::Vector2f Size1(530,147);
    gButton Button1(Position1, Size1, "OSullivan.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    Button1.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f Position2(136,228);
    sf::Vector2f Size2(530,127);
    gButton Button2(Position2, Size2, "MrDing.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    Button2.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f Position3(130,394);
    sf::Vector2f Size3(530, 127);
    gButton Button3(Position3, Size3, "Selby.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    Button3.m_Rect.setFillColor(sf::Color::Transparent);

    //加载退出键
    gButton BackButton = Back_Button(window);
    //设置主页按键
    gButton HomeButton = Home_Button(window);
    // 使矩形透明，仅用于表示区域
    BackButton.m_Rect.setFillColor(sf::Color::Transparent);
    HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

    while (window.isOpen() && state == ScreenState::Fame)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton, HomeButton, ScreenState::Viewing);

            Suspention(window, &Button1);
            Suspention(window, &Button2);
            Suspention(window, &Button3);

            sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::MouseButtonReleased)
            {
                string path;
                //判断左键点击
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Button1.if_contain(MousePos))
                    {
                        path = "OSullivan.mp4";
                        watchtimes++;
                        VideoPlay(window, state, path,1,sound);
                        return;
                    }
                    if (Button2.if_contain(MousePos))
                    {
                        path = "MrDing.mp4";
                        watchtimes++;
                        VideoPlay(window, state, path,1, sound);
                        return;
                    }
                    if (Button3.if_contain(MousePos))
                    {
                        path = "Selby.mp4";
                        watchtimes++;
                        VideoPlay(window, state, path,1, sound);
                        return;
                    }
                }
            }
        }

        window.clear();

        YiewBackgroundButton.Draw(window);

        Button1.Draw(window);

        Button2.Draw(window);

        Button3.Draw(window);

        BackButton.Draw(window);

        HomeButton.Draw(window);

        window.display();
    }
}

void FullViewing(ScreenState& state, sf::RenderWindow& window, sf::Music& sound)
{
    sf::Font font;
    if (!font.loadFromFile("BASKVILL.ttf"))
    {
        return;
    }

    sf::Vector2f YiewBackgroundPosition(0, 0);
    sf::Vector2f YiewBackgroundSize(802, 603);
    gButton YiewBackgroundButton(YiewBackgroundPosition, YiewBackgroundSize, "FameBackground.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    YiewBackgroundButton.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f Position1(136, 62);
    sf::Vector2f Size1(530, 147);
    gButton Button1(Position1, Size1, "Full1.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    Button1.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f Position2(136, 228);
    sf::Vector2f Size2(530, 127);
    gButton Button2(Position2, Size2, "Full2.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    Button2.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f Position3(130, 394);
    sf::Vector2f Size3(530, 127);
    gButton Button3(Position3, Size3, "Full3.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    Button3.m_Rect.setFillColor(sf::Color::Transparent);

    //加载退出键
    gButton BackButton = Back_Button(window);
    //设置主页按键
    gButton HomeButton = Home_Button(window);
    // 使矩形透明，仅用于表示区域
    BackButton.m_Rect.setFillColor(sf::Color::Transparent);
    HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

    while (window.isOpen() && state == ScreenState::Full)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton, HomeButton, ScreenState::Viewing);

            Suspention(window, &Button1);
            Suspention(window, &Button2);
            Suspention(window, &Button3);

            sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::MouseButtonReleased)
            {
                //判断左键点击
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    string path;
                    if (Button1.if_contain(MousePos))
                    {
                        
                        path = "147-1.mp4";
                        watchtimes++;
                        VideoPlay(window, state ,path,2, sound);
                        return;
                    }
                    if (Button2.if_contain(MousePos))
                    {
                        path = "147-2.mp4";
                        watchtimes++;
                        VideoPlay(window, state, path,2, sound);
                        return;
                    }
                    if (Button3.if_contain(MousePos))
                    {
                        path = "147-3.mp4";
                        watchtimes++;
                        VideoPlay(window, state, path,2, sound);
                        return;
                    }
                }
            }
        }

        window.clear();

        YiewBackgroundButton.Draw(window);

        Button1.Draw(window);

        Button2.Draw(window);

        Button3.Draw(window);

        BackButton.Draw(window);

        HomeButton.Draw(window);

        window.display();
    }
}
#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"
#include "player.h"


void MainShow(ScreenState& state, sf::RenderWindow& window, player& temp)
{
    sf::Font font;
    //检查错误，如有则返回结束
    if (!font.loadFromFile("Font.ttf"))
    {
        cerr << "Failed to load font!" << endl;
        return;
    }

    //设置头像
    sf::Texture AvatarTexure;
    //检查错误，如有则返回结束
    if (!AvatarTexure.loadFromFile("Avatar.jpg"))
    {
        cerr << "Failed to load avatar texture!" << endl;
        return;
    }

    //设置头像位置
    sf::Sprite avatar(AvatarTexure);
    avatar.setScale(0.08f, 0.08f);
    avatar.setPosition(0,0);

    //设置用户名
    //Button(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, int& CharacterSize);
    string text = "AVATAR";
    sf::Vector2f AvatarPosition(avatar.getGlobalBounds().width, 2);
    sf::Vector2f AvatarSize(100,36);
    gButton Avatar(text, font, AvatarPosition, AvatarSize, 30, sf::Vector3f(150.0f, 100.0f, 250.0f));

    //设置背景
    sf::Texture BackGround;
    //检查错误，如有则返回结束
    if (!BackGround.loadFromFile("Background.png"))
    {
        cerr << "Failed to load background!" << endl;
        return;
    }
    //设置背景位置
    sf::Sprite background(BackGround);
    background.setScale(1.0f, 1.0f);
    background.setPosition(0, 0);

    //设置真背景
    sf::Texture BasicBackGround;
    //检查错误，如有则返回结束
    if (!BasicBackGround.loadFromFile("BasicBackground.png"))
    {
        cerr << "Failed to load background!" << endl;
        return;
    }
    //设置背景位置
    sf::Sprite Basicbackground(BasicBackGround);
    Basicbackground.setScale(1.0f, 1.0f);
    Basicbackground.setPosition(0, 40);


    //设置商城
    sf::Vector2f MallPosition(WINDOW_WIDTH - 76, -4);
    sf::Vector2f MallSize(45,50);
    gButton Mall(MallPosition, MallSize, "Mall.png",window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    Mall.m_Rect.setFillColor(sf::Color::Transparent);

    //设置设置
    sf::Vector2f SetPosition(WINDOW_WIDTH - 36, 0);
    sf::Vector2f SetSize(45, 45);
    gButton Set(SetPosition, SetSize, "Mall.png", window, sf::Vector3f(150.0f, 100.0f, 250.0f));


    //设置现有积分
    int score = temp.getPoints();
    //将整数转化为字符串与Score拼接在一起
    string ScoreText = std::to_string(score);
    sf::Vector2f ScorePosition(WINDOW_WIDTH-190, 2);
    sf::Vector2f ScoreSize(120, 36);
    gButton Score(ScoreText, font, ScorePosition, ScoreSize, 30, sf::Vector3f(150.0f, 100.0f, 250.0f));

    //设置积分图标
    sf::Texture ScoreTexure;
    //检查错误，如有则返回结束
    if (!ScoreTexure.loadFromFile("Score.png"))
    {
        cerr << "Failed to load score texture!" << endl;
        return;
    }

    //设置位置
    sf::Sprite ScorePic(ScoreTexure);
    ScorePic.setScale(0.25f, 0.25f);
    ScorePic.setPosition(WINDOW_WIDTH - 192, -5);

    //设置现有金币
    int money = temp.getCoins();
    //将整数转化为字符串与Score拼接在一起
    string MoneyText = std::to_string(money);
    sf::Vector2f MoneyPosition(WINDOW_WIDTH - 310, 2);
    sf::Vector2f MoneySize(120, 36);
    gButton Money(MoneyText, font, MoneyPosition, MoneySize, 30, sf::Vector3f(150.0f, 100.0f, 250.0f));

    //设置金币图标
    sf::Texture MoneyTexure;
    //检查错误，如有则返回结束
    if (!MoneyTexure.loadFromFile("Money.png"))
    {
        cerr << "Failed to load money texture!" << endl;
        return;
    }

    //设置位置
    sf::Sprite MoneyPic(MoneyTexure);
    MoneyPic.setScale(0.18f, 0.18f);
    MoneyPic.setPosition(WINDOW_WIDTH - 310, 2);

    //renwu
    sf::Vector2f TaskPosition(WINDOW_WIDTH - 500, -4);
    sf::Vector2f TaskSize(65, 50);
    gButton Task(TaskPosition, TaskSize, "task.png", window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    Task.m_Rect.setFillColor(sf::Color::Transparent);

    //设置现有排名
    int rank = 1;
    //将整数转化为字符串与Score拼接在一起
    string RankText = std::to_string(rank);
    sf::Vector2f RankPosition(WINDOW_WIDTH - 430, 2);
    sf::Vector2f RankSize(120, 36);
    gButton Rank(RankText, font, RankPosition, RankSize, 30, sf::Vector3f(150.0f,100.0f,250.0f));

    // 设置排名图标
        sf::Texture RankTexure;
    //检查错误，如有则返回结束
    if (!RankTexure.loadFromFile("Rank.png"))
    {
        cerr << "Failed to load rank texture!" << endl;
        return;
    }

    //设置位置
    sf::Sprite RankPic(RankTexure);
    RankPic.setScale(0.18f, 0.18f);
    RankPic.setPosition(WINDOW_WIDTH - 430, 2);



    //设置选项按键形状
    gButton* Option[4] = { nullptr }; // 初始化为nullptr
    for (int i = 0; i < 4; i++)
    {
        string path = "Button" + std::to_string(i+1)+".png";

        sf::Vector2f OptionPosition(5+199*i, 245);
        sf::Vector2f OptionSize(215,360);
        //Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,const string& path)
        /*Button button(OptionPosition, OptionSize, path, window);*/
        Option[i] = new gButton(OptionPosition, OptionSize, path, window,sf::Vector3f(0.0f,0.0f,0.0f));
       /* Button button(OptionPosition, OptionSize, path, window);
        Option.push_back(button);*/
    }
    
    //游戏主循环
    //是程序保持运行知道显示关闭：window.close()
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //检测事件，如果点击关闭则关闭
            Window_Close(window,event);

            for (int i = 0; i < 4; i++)
            {
                Suspention(window, Option[i]);
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                //判断左键点击
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    /*sf::Mouse::getPosition(window) :
                        这个函数返回当前鼠标在指定窗口中的像素坐标。window 是一个 sf::RenderWindow 对象，表示当前的渲染窗口。
                        返回值是一个 sf::Vector2i 类型的对象，表示鼠标在窗口中的像素坐标（x, y）。

                     window.mapPixelToCoords(sf::Mouse::getPosition(window)) :
                        这个函数将像素坐标转换为世界坐标。mapPixelToCoords 是 sf::RenderWindow 类的一个成员函数。
                        它接受一个 sf::Vector2i 类型的参数（像素坐标），并返回一个 sf::Vector2f 类型的对象（世界坐标）。
                        世界坐标是相对于窗口的视图（view）的坐标系，通常用于绘制和处理游戏对象的位置。

                    sf::Vector2f MousePos :
                        这是一个 sf::Vector2f 类型的变量，用于存储转换后的世界坐标。*/
                    sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (Avatar.if_contain(MousePos))
                    {
                        state = ScreenState::Avatar; // 切换到另一个界面
                        return;
                    }
                    if (Option[0]->if_contain(MousePos))
                    {
                        state = ScreenState::Mode; // 切换到另一个界面
                        return;
                    }
                    if (Option[1]->if_contain(MousePos))
                    {
                        state = ScreenState::History; // 切换到另一个界面
                        return;
                    }
                    if (Option[2]->if_contain(MousePos))
                    {
                        state = ScreenState::Highlights; // 切换到另一个界面
                        return;
                    }
                    if (Option[3]->if_contain(MousePos))
                    {
                        state = ScreenState::Viewing; // 切换到另一个界面
                        return;
                    }
                    if (Avatar.if_contain(MousePos))
                    {
                        state = ScreenState::Avatar; // 切换到另一个界面
                        return;
                    }
                    if (Rank.if_contain(MousePos))
                    {
                        state = ScreenState::Ranking; // 切换到另一个界面
                        return;
                    }
                    if (Mall.if_contain(MousePos))
                    {
                        state = ScreenState::Mall; // 切换到另一个界面
                        return;
                    }
                    if (Set.if_contain(MousePos))
                    {
                        state = ScreenState::Settings; // 切换到另一个界面
                        return;
                    }
                    if (Task.if_contain(MousePos)) {
                        state = ScreenState::Task;
                        return;
                    }
                }
            }
        }
        window.clear();

        Set.Draw(window);

        window.draw(background);

        window.draw(avatar);

        Avatar.Draw(window);

        Mall.Draw(window);

        Score.Draw(window);

        Money.Draw(window);

        Rank.Draw(window);

        Task.Draw(window);
        for (const auto& entry : Option)
        {
            entry->Draw(window);
        }
        
        //Option[1]->Draw(window);

        window.draw(ScorePic);

        window.draw(MoneyPic);

        //window.draw(Basicbackground);

        window.draw(RankPic);

        window.display();
    }

    for (int i = 0; i < 4; ++i)
    {
        if (Option[i] != nullptr)
        {
            delete Option[i];
            Option[i] = nullptr;
        }
    }
}
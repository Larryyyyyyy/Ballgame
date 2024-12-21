#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"
#include "player.h"


void MainShow(ScreenState& state, sf::RenderWindow& window, player& temp)
{
    sf::Font font;
    //�����������򷵻ؽ���
    if (!font.loadFromFile("Font.ttf"))
    {
        cerr << "Failed to load font!" << endl;
        return;
    }

    //����ͷ��
    sf::Texture AvatarTexure;
    //�����������򷵻ؽ���
    if (!AvatarTexure.loadFromFile("Avatar.jpg"))
    {
        cerr << "Failed to load avatar texture!" << endl;
        return;
    }

    //����ͷ��λ��
    sf::Sprite avatar(AvatarTexure);
    avatar.setScale(0.08f, 0.08f);
    avatar.setPosition(0,0);

    //�����û���
    //Button(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, int& CharacterSize);
    string text = "AVATAR";
    sf::Vector2f AvatarPosition(avatar.getGlobalBounds().width, 2);
    sf::Vector2f AvatarSize(100,36);
    gButton Avatar(text, font, AvatarPosition, AvatarSize, 30, sf::Vector3f(150.0f, 100.0f, 250.0f));

    //���ñ���
    sf::Texture BackGround;
    //�����������򷵻ؽ���
    if (!BackGround.loadFromFile("Background.png"))
    {
        cerr << "Failed to load background!" << endl;
        return;
    }
    //���ñ���λ��
    sf::Sprite background(BackGround);
    background.setScale(1.0f, 1.0f);
    background.setPosition(0, 0);

    //�����汳��
    sf::Texture BasicBackGround;
    //�����������򷵻ؽ���
    if (!BasicBackGround.loadFromFile("BasicBackground.png"))
    {
        cerr << "Failed to load background!" << endl;
        return;
    }
    //���ñ���λ��
    sf::Sprite Basicbackground(BasicBackGround);
    Basicbackground.setScale(1.0f, 1.0f);
    Basicbackground.setPosition(0, 40);


    //�����̳�
    sf::Vector2f MallPosition(WINDOW_WIDTH - 76, -4);
    sf::Vector2f MallSize(45,50);
    gButton Mall(MallPosition, MallSize, "Mall.png",window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    Mall.m_Rect.setFillColor(sf::Color::Transparent);

    //��������
    sf::Vector2f SetPosition(WINDOW_WIDTH - 36, 0);
    sf::Vector2f SetSize(45, 45);
    gButton Set(SetPosition, SetSize, "Mall.png", window, sf::Vector3f(150.0f, 100.0f, 250.0f));


    //�������л���
    int score = temp.getPoints();
    //������ת��Ϊ�ַ�����Scoreƴ����һ��
    string ScoreText = std::to_string(score);
    sf::Vector2f ScorePosition(WINDOW_WIDTH-190, 2);
    sf::Vector2f ScoreSize(120, 36);
    gButton Score(ScoreText, font, ScorePosition, ScoreSize, 30, sf::Vector3f(150.0f, 100.0f, 250.0f));

    //���û���ͼ��
    sf::Texture ScoreTexure;
    //�����������򷵻ؽ���
    if (!ScoreTexure.loadFromFile("Score.png"))
    {
        cerr << "Failed to load score texture!" << endl;
        return;
    }

    //����λ��
    sf::Sprite ScorePic(ScoreTexure);
    ScorePic.setScale(0.25f, 0.25f);
    ScorePic.setPosition(WINDOW_WIDTH - 192, -5);

    //�������н��
    int money = temp.getCoins();
    //������ת��Ϊ�ַ�����Scoreƴ����һ��
    string MoneyText = std::to_string(money);
    sf::Vector2f MoneyPosition(WINDOW_WIDTH - 310, 2);
    sf::Vector2f MoneySize(120, 36);
    gButton Money(MoneyText, font, MoneyPosition, MoneySize, 30, sf::Vector3f(150.0f, 100.0f, 250.0f));

    //���ý��ͼ��
    sf::Texture MoneyTexure;
    //�����������򷵻ؽ���
    if (!MoneyTexure.loadFromFile("Money.png"))
    {
        cerr << "Failed to load money texture!" << endl;
        return;
    }

    //����λ��
    sf::Sprite MoneyPic(MoneyTexure);
    MoneyPic.setScale(0.18f, 0.18f);
    MoneyPic.setPosition(WINDOW_WIDTH - 310, 2);

    //renwu
    sf::Vector2f TaskPosition(WINDOW_WIDTH - 500, -4);
    sf::Vector2f TaskSize(65, 50);
    gButton Task(TaskPosition, TaskSize, "task.png", window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    Task.m_Rect.setFillColor(sf::Color::Transparent);

    //������������
    int rank = 1;
    //������ת��Ϊ�ַ�����Scoreƴ����һ��
    string RankText = std::to_string(rank);
    sf::Vector2f RankPosition(WINDOW_WIDTH - 430, 2);
    sf::Vector2f RankSize(120, 36);
    gButton Rank(RankText, font, RankPosition, RankSize, 30, sf::Vector3f(150.0f,100.0f,250.0f));

    // ��������ͼ��
        sf::Texture RankTexure;
    //�����������򷵻ؽ���
    if (!RankTexure.loadFromFile("Rank.png"))
    {
        cerr << "Failed to load rank texture!" << endl;
        return;
    }

    //����λ��
    sf::Sprite RankPic(RankTexure);
    RankPic.setScale(0.18f, 0.18f);
    RankPic.setPosition(WINDOW_WIDTH - 430, 2);



    //����ѡ�����״
    gButton* Option[4] = { nullptr }; // ��ʼ��Ϊnullptr
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
    
    //��Ϸ��ѭ��
    //�ǳ��򱣳�����֪����ʾ�رգ�window.close()
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //����¼����������ر���ر�
            Window_Close(window,event);

            for (int i = 0; i < 4; i++)
            {
                Suspention(window, Option[i]);
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                //�ж�������
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    /*sf::Mouse::getPosition(window) :
                        ����������ص�ǰ�����ָ�������е��������ꡣwindow ��һ�� sf::RenderWindow ���󣬱�ʾ��ǰ����Ⱦ���ڡ�
                        ����ֵ��һ�� sf::Vector2i ���͵Ķ��󣬱�ʾ����ڴ����е��������꣨x, y����

                     window.mapPixelToCoords(sf::Mouse::getPosition(window)) :
                        �����������������ת��Ϊ�������ꡣmapPixelToCoords �� sf::RenderWindow ���һ����Ա������
                        ������һ�� sf::Vector2i ���͵Ĳ������������꣩��������һ�� sf::Vector2f ���͵Ķ����������꣩��
                        ��������������ڴ��ڵ���ͼ��view��������ϵ��ͨ�����ڻ��ƺʹ�����Ϸ�����λ�á�

                    sf::Vector2f MousePos :
                        ����һ�� sf::Vector2f ���͵ı��������ڴ洢ת������������ꡣ*/
                    sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (Avatar.if_contain(MousePos))
                    {
                        state = ScreenState::Avatar; // �л�����һ������
                        return;
                    }
                    if (Option[0]->if_contain(MousePos))
                    {
                        state = ScreenState::Mode; // �л�����һ������
                        return;
                    }
                    if (Option[1]->if_contain(MousePos))
                    {
                        state = ScreenState::History; // �л�����һ������
                        return;
                    }
                    if (Option[2]->if_contain(MousePos))
                    {
                        state = ScreenState::Highlights; // �л�����һ������
                        return;
                    }
                    if (Option[3]->if_contain(MousePos))
                    {
                        state = ScreenState::Viewing; // �л�����һ������
                        return;
                    }
                    if (Avatar.if_contain(MousePos))
                    {
                        state = ScreenState::Avatar; // �л�����һ������
                        return;
                    }
                    if (Rank.if_contain(MousePos))
                    {
                        state = ScreenState::Ranking; // �л�����һ������
                        return;
                    }
                    if (Mall.if_contain(MousePos))
                    {
                        state = ScreenState::Mall; // �л�����һ������
                        return;
                    }
                    if (Set.if_contain(MousePos))
                    {
                        state = ScreenState::Settings; // �л�����һ������
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
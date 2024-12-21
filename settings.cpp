#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"

//设计一个滑块类用于调节音量
class VolumeSlider
{
    friend void Settings(ScreenState& state, sf::RenderWindow& window, sf::Music& sound, int& Switch_Flag, string& MusicPath, float& volume,int& Acquiesce_Flag);
public:
    //设置滑块形状
    VolumeSlider(sf::RenderWindow& window, const sf::Font& font, float& volume);

    // 绘制音量文本
    void draw(sf::RenderWindow& window)
    {
        SliderBackgroundButton->Draw(window);
        SliderButton->Draw(window);
        window.draw(VolumeText); 
    }

    //更新音量
    void update(sf::Vector2f mousePosition, sf::Music& sound, float& volume);
    
    //更新音量显示
    void updateVolumeText(float& volume)
    {
        VolumeText.setString(std::to_string((int)(volume * 100)) + "%");
    }

    // 计算点击位置的音量
    void AdjustVolume(sf::Vector2f mousePosition, float& volume);

    void startDrag() 
    {
        is_Dragging = true;
    }

    void stopDrag() 
    {
        is_Dragging = false;
    }

    bool if_Dragging() const 
    {
        return is_Dragging;
    }
private:
    gButton* SliderBackgroundButton = nullptr;
    gButton* SliderButton = nullptr;
    
    sf::Text VolumeText;

    bool is_Dragging = false;
};

VolumeSlider::VolumeSlider(sf::RenderWindow& window, const sf::Font& font, float& volume)
{
    //设置滑条
    string path = "";
    SliderBackgroundButton = new gButton(sf::Vector2f(434.0f,48.0f), sf::Vector2f(272.0f,18.0f), path, window, sf::Vector3f(200.0f, 200.0f,200.0f));

    //设置滑块
    SliderButton = new gButton(sf::Vector2f(434.0f, 48.0f), sf::Vector2f(volume * SliderBackgroundButton->m_Rect.getSize().x, 18.0f), path, window, sf::Vector3f(0.0f,0.0f,0.0f));

    VolumeText.setFont(font);
    VolumeText.setCharacterSize(15);
    VolumeText.setFillColor(sf::Color::Black);
    VolumeText.setPosition(708, 44); // 文本位置在进度条旁边
    updateVolumeText(volume);
}

void VolumeSlider::update(sf::Vector2f mousePosition, sf::Music& sound, float& volume)
{
    if (is_Dragging == true)
    {
        //根据鼠标移动的位置比上整段长度
        float NewVolume = (mousePosition.x - SliderBackgroundButton->m_Rect.getPosition().x) / SliderBackgroundButton->m_Rect.getSize().x;

        //限制音量在0到1之间
        NewVolume = std::max(0.0f, std::min(NewVolume, 1.0f));

        //更新音量
        volume = NewVolume;
        sound.setVolume(volume * 100);

        // 更新文本显示
        SliderButton->m_Rect.setSize(sf::Vector2f(volume * SliderBackgroundButton->m_Rect.getSize().x, 18)); // 设置滑块宽度
        updateVolumeText(volume); 
    }
}

void VolumeSlider::AdjustVolume(sf::Vector2f mousePosition, float& volume)
{
    if (mousePosition.x >= SliderBackgroundButton->m_Rect.getPosition().x &&
        mousePosition.x <= SliderBackgroundButton->m_Rect.getPosition().x + SliderBackgroundButton->m_Rect.getSize().x)
    {
        float NewVolume = (mousePosition.x - SliderBackgroundButton->m_Rect.getPosition().x) / SliderBackgroundButton->m_Rect.getSize().x;
        volume = NewVolume;
        SliderButton->m_Rect.setSize(sf::Vector2f(volume * SliderBackgroundButton->m_Rect.getSize().x, 18)); // 设置滑块宽度
        updateVolumeText(volume);
    }
}

void Settings(ScreenState& state, sf::RenderWindow& window, sf::Music& sound, int& Switch_Flag, string& MusicPath, float& volume, int& Acquiesce_Flag)
{
    // 加载字体
    sf::Font font;
    if (!font.loadFromFile("BASKVILL.ttf"))
    {
        return;
    }

    
    //导入背景图
    //设置的界面背景的纹理
    vector<sf::Texture*> Backgrounds;
    Backgrounds.resize(4);
    for(int i = 0;i<4;i++)
    {
        sf::Texture background;
        string path = "SettingsBackground" + to_string(i + 1) + ".png";
        if (!background.loadFromFile(path))
        {
            return;
        }
        Backgrounds[i] = new sf::Texture(background);
    }
    //设置的界面的精灵
    sf::Sprite BackgroundSprite1(*Backgrounds[0]);
    BackgroundSprite1.setPosition(sf::Vector2f(0,0));
    BackgroundSprite1.setScale(sf::Vector2f(1.f,1.f));
    sf::Sprite BackgroundSprite2(*Backgrounds[1]);
    BackgroundSprite2.setPosition(sf::Vector2f(0,192));
    BackgroundSprite2.setScale(sf::Vector2f(1.f, 1.f));
    sf::Sprite BackgroundSprite3(*Backgrounds[2]);
    BackgroundSprite3.setPosition(sf::Vector2f(716,192));
    BackgroundSprite3.setScale(sf::Vector2f(1.f, 1.f));
    sf::Sprite BackgroundSprite4(*Backgrounds[3]);
    BackgroundSprite4.setPosition(sf::Vector2f(0, 504));
    BackgroundSprite4.setScale(sf::Vector2f(1.f, 1.f));

    //导入开关
    //开关的纹理
    sf::Texture switches;
    if(Switch_Flag)
    {
        if (!switches.loadFromFile("On.png"))
        {
            return;
        }
    }
    else
    {
        if (!switches.loadFromFile("Off.png"))
        {
            return;
        }
    }
    //开关的精灵
    sf::Sprite SwitchesSprite(switches);
    SwitchesSprite.setPosition(sf::Vector2f(202,14));
    SwitchesSprite.setScale(sf::Vector2f(1.0f, 1.0f));
    //开关的矩阵
    sf::RectangleShape SwitchesRec;
    SwitchesRec.setPosition(sf::Vector2f(202.f, 14.f));
    SwitchesRec.setSize(sf::Vector2f(80.f, 80.f));
    // 使矩形透明，仅用于表示区域
    SwitchesRec.setFillColor(sf::Color::Transparent);

    //加载滑块
    VolumeSlider volumeSlider(window, font,volume);

    //加载退出键
    gButton BackButton = Back_Button(window);
    //设置主页按键
    gButton HomeButton = Home_Button(window);
    // 使矩形透明，仅用于表示区域
    BackButton.m_Rect.setFillColor(sf::Color::Transparent);
    HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

    //设置默认键
    sf::Texture Acquiesce;
    if (Acquiesce_Flag)
    {
        if (!Acquiesce.loadFromFile("Acquiesce.png"))
        {
            return;
        }
    }
    else
    {
        if (!Acquiesce.loadFromFile("Unacquiesce.png"))
        {
            return;
        }
    }
    //开关的精灵
    sf::Sprite AcquiesceSprite(Acquiesce);
    AcquiesceSprite.setPosition(sf::Vector2f(550,130));
    AcquiesceSprite.setScale(sf::Vector2f(1.0f, 1.0f));
    //开关的矩阵
    sf::RectangleShape AcquiesceRec;
    AcquiesceRec.setPosition(sf::Vector2f(559.f, 136.f));
    AcquiesceRec.setSize(sf::Vector2f(20.f, 20.f));
    // 使矩形透明，仅用于表示区域
    AcquiesceRec.setFillColor(sf::Color::Transparent);

    //导入关闭键
    //关闭键的纹理
    sf::Texture exit;
    if (!exit.loadFromFile("Exit.png"))
    {
        return;
    }
    //设置的界面的精灵
    sf::Sprite ExitSprite(exit);
    ExitSprite.setPosition(sf::Vector2f(706.f,531.f));
    ExitSprite.setScale(sf::Vector2f(0.24f, 0.24f));
    //开关的矩阵
    sf::RectangleShape ExitRec;
    ExitRec.setPosition(sf::Vector2f(706.f, 531.f));
    ExitRec.setSize(sf::Vector2f(48.f, 48.f));
    // 使矩形透明，仅用于表示区域
    ExitRec.setFillColor(sf::Color::Transparent);


    //视图
    sf::View MainView(sf::FloatRect(0, 0, 802, 603));
    //MainView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    //创建小窗视图
    sf::View MiniView(sf::FloatRect(87,192,630,312));
    MiniView.setViewport(sf::FloatRect(0.10848f, 0.31841f, 0.78500f, 0.53000f));
    //创建一个视图矩阵
    sf::RectangleShape ViewRec;
    ViewRec.setPosition(sf::Vector2f(87.f, 192.f));
    ViewRec.setSize(sf::Vector2f(48.f, 48.f));

    vector<gButton*> Songs = { nullptr };
    Songs.resize(6);
    //建立分割填充白色
    vector<gButton*> Intervals = { nullptr };
    Intervals.resize(5);
    for (int i = 0; i < 6; i++)
    {
        string Path_Of_Song = "Song" + to_string(i) + ".png";
        //Button(const sf::Vector2f& position, const sf::Vector2f& size, const string& path, sf::RenderWindow& window, const sf::Vector3f& color);
        Songs[i] = new gButton(sf::Vector2f(97.f, 192.f + i * 110.f), sf::Vector2f(619.f, 92.f), Path_Of_Song, window, sf::Vector3f(0.f, 0.f, 0.f));
        Songs[i]->m_Rect.setFillColor(sf::Color::Transparent);
        if(i != 5)
        {
            Intervals[i] = new gButton(sf::Vector2f(87.f, 284.f + i * 110.f), sf::Vector2f(630.f, 18.f), "Interval.png", window, sf::Vector3f(0.f, 0.f, 0.f));
            Intervals[i]->m_Rect.setFillColor(sf::Color::Transparent);
        }
    }

    //滑动
    //滑动偏移值
    float scroll = 0;

    while (window.isOpen() && state == ScreenState::Settings)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            Window_Back(window, event, state, BackButton, HomeButton, ScreenState::MainScreen);

            // 点击调节音量
            sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if(volumeSlider.SliderBackgroundButton->if_contain(MousePos) == true)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        volumeSlider.AdjustVolume(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), volume);
                        // 开始拖动
                        volumeSlider.startDrag();
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        volumeSlider.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), sound, volume);
                        volumeSlider.stopDrag();

                       
                    }
                }
            }

            // 更新音量值
            if (event.type == sf::Event::MouseMoved && volumeSlider.if_Dragging()) 
            {
                volumeSlider.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), sound,volume);
                volumeSlider.AdjustVolume(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), volume);
            }

            //设计音效
            //利用flag来判断
            //仅在按下鼠标左键时改变flag，在送开始不变
            //是这样的这很奇怪，按下和分开时两件事
            //这让作者奇怪了很久
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (SwitchesRec.getGlobalBounds().contains(static_cast<float>(MousePos.x), static_cast<float>(MousePos.y)))
                {
                    Switch_Flag = (Switch_Flag == 0) ? 1 : 0;
                    return;
                }
            }

            //设置默认
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (AcquiesceRec.getGlobalBounds().contains(static_cast<float>(MousePos.x), static_cast<float>(MousePos.y)))
                {
                    Acquiesce_Flag = (Acquiesce_Flag == 0) ? 1 : 0;
                    return;
                }
            }

            //滑动
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                sf::Vector2i MousePos = sf::Mouse::getPosition(window);
                if (static_cast<float>(MousePos.y) >= 192
                    && static_cast<float>(MousePos.y) <= 504)
                {
                    scroll -= event.mouseWheelScroll.delta * 80;
                    scroll = (scroll > 330) ? 330 : scroll;
                    scroll = (scroll < 0) ? 0 : scroll;
                }
            }

            for(int i = 0;i<6;i++)
            {
                Suspention(window, Songs[i]);
            }

            //切换音乐
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int i = 0; i < 5; i++)
                {
                    //要注意如果点击的就是当前音乐不需要重新播放
                    if (Songs[i]->if_contain(MousePos))
                    {
                        MusicPath = "Song" + to_string(i) + ".wav";
                        break;
                    }
                }
                return;
            }
        }

        //滑动
        //更新图片位置
        for (int i = 0; i < 6; i++)
        {
            Songs[i]->ButtonSprite.setPosition(sf::Vector2f(97.f, 192.f + i * 110.f - scroll));
            Songs[i]->m_Rect.setPosition(sf::Vector2f(97.f, 192.f + i * 110.f - scroll));
            if(i != 5)
            {
                Intervals[i]->ButtonSprite.setPosition(sf::Vector2f(87.f, 284.f + i * 110.f - scroll));
                Intervals[i]->m_Rect.setPosition(sf::Vector2f(87.f, 284.f + i * 110.f - scroll));
            }
        }

        window.clear(sf::Color::White);

        window.setView(MiniView);
        for (int i = 0; i < 6; i++)
        {
            if (i != 5)
            {
                Intervals[i]->Draw(window);
            }
            Songs[i]->Draw(window);
        }

        window.setView(MainView);

        window.draw(BackgroundSprite1);
        window.draw(BackgroundSprite2);
        window.draw(BackgroundSprite3);
        window.draw(BackgroundSprite4);

        BackButton.Draw(window);
        HomeButton.Draw(window);

        window.draw(SwitchesSprite);
        window.draw(SwitchesRec);

        window.draw(AcquiesceSprite);
        window.draw(AcquiesceRec);

        window.draw(ExitSprite);
        window.draw(ExitRec);

        volumeSlider.draw(window);

        window.display();
    }

    for (int i = 0; i < 5; ++i)
    {
        if (Songs[i] != nullptr)
        {
            delete Songs[i];
            Songs[i] = nullptr;
        }
    }
    for (int i = 0; i < 5; ++i)
    {
        if (Intervals[i] != nullptr)
        {
            delete Intervals[i];
            Intervals[i] = nullptr;
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        if (Backgrounds[i] != nullptr)
        {
            delete Backgrounds[i];
            Backgrounds[i] = nullptr;
        }
    }
}
#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"

void Icon(sf::RenderWindow& window)
{
    //设置窗口图标
    sf::Image icon;
    if (!icon.loadFromFile("GameIcon.png"))
    {
        return ;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void playMusic(sf::Music& music,string MusicPath)
{
	//设置背景音乐
    // 创建音乐对象
    // 加载音频文件
    if (!music.openFromFile(MusicPath))
    {
            exit(0);
    }

    // 播放音乐
    music.play();

    // 设置为循环播放
    music.setLoop(true);

    // 设置音量为 70%
    music.setVolume(70.f);
}

//退格键
gButton Back_Button(sf::RenderWindow& window)
{
	string Picture = "Back.png";
	sf::Vector2f PicturePosition(40, 0);
	sf::Vector2f PictureSize(40, 40);
	gButton BackButton(PicturePosition, PictureSize, Picture, window,sf::Vector3f(150.0f,100.0f,250.0f));
	return BackButton;
}

//主页
gButton Home_Button(sf::RenderWindow& window)
{
    string Picture = "Home.png";
    sf::Vector2f PicturePosition(5, 0);
    sf::Vector2f PictureSize(40, 40);
    gButton HomeButton(PicturePosition, PictureSize, Picture, window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    return HomeButton;
}

//关闭
void Window_Close(sf::RenderWindow& window,sf::Event& event)
{
    if (event.type == sf::Event::Closed)
        window.close();
}

//返回
void Window_Back(sf::RenderWindow& window, sf::Event& event,ScreenState& state,gButton& BackButton, gButton& HomeButton, ScreenState NewState)
{

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (BackButton.if_contain(MousePos))
        {
            state = NewState; // 切换到另一个界面
            return;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (HomeButton.if_contain(MousePos))
        {
            state = ScreenState::MainScreen; // 切换到另一个界面
            return;
        }
    }
}

void Suspention(sf::RenderWindow& window, gButton* button)
{
    // 获取鼠标位置
    sf::Vector2i MousePos = sf::Mouse::getPosition(window);

    // 检查鼠标是否悬停在矩形上
    for (int i = 0; i < 4; i++)
    {
        if (button->m_Rect.getGlobalBounds().contains(static_cast<float>(MousePos.x), static_cast<float>(MousePos.y)))
        {
            button->ButtonSprite.setScale(1.1f, 1.1f); // 鼠标悬停时改变大小
        }
        else
        {
            button->ButtonSprite.setScale(1.0f, 1.0f); // 鼠标不在上面时恢复大小
        }
    }
}
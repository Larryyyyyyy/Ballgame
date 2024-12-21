#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"

void Icon(sf::RenderWindow& window)
{
    //���ô���ͼ��
    sf::Image icon;
    if (!icon.loadFromFile("GameIcon.png"))
    {
        return ;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void playMusic(sf::Music& music,string MusicPath)
{
	//���ñ�������
    // �������ֶ���
    // ������Ƶ�ļ�
    if (!music.openFromFile(MusicPath))
    {
            exit(0);
    }

    // ��������
    music.play();

    // ����Ϊѭ������
    music.setLoop(true);

    // ��������Ϊ 70%
    music.setVolume(70.f);
}

//�˸��
gButton Back_Button(sf::RenderWindow& window)
{
	string Picture = "Back.png";
	sf::Vector2f PicturePosition(40, 0);
	sf::Vector2f PictureSize(40, 40);
	gButton BackButton(PicturePosition, PictureSize, Picture, window,sf::Vector3f(150.0f,100.0f,250.0f));
	return BackButton;
}

//��ҳ
gButton Home_Button(sf::RenderWindow& window)
{
    string Picture = "Home.png";
    sf::Vector2f PicturePosition(5, 0);
    sf::Vector2f PictureSize(40, 40);
    gButton HomeButton(PicturePosition, PictureSize, Picture, window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    return HomeButton;
}

//�ر�
void Window_Close(sf::RenderWindow& window,sf::Event& event)
{
    if (event.type == sf::Event::Closed)
        window.close();
}

//����
void Window_Back(sf::RenderWindow& window, sf::Event& event,ScreenState& state,gButton& BackButton, gButton& HomeButton, ScreenState NewState)
{

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (BackButton.if_contain(MousePos))
        {
            state = NewState; // �л�����һ������
            return;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (HomeButton.if_contain(MousePos))
        {
            state = ScreenState::MainScreen; // �л�����һ������
            return;
        }
    }
}

void Suspention(sf::RenderWindow& window, gButton* button)
{
    // ��ȡ���λ��
    sf::Vector2i MousePos = sf::Mouse::getPosition(window);

    // �������Ƿ���ͣ�ھ�����
    for (int i = 0; i < 4; i++)
    {
        if (button->m_Rect.getGlobalBounds().contains(static_cast<float>(MousePos.x), static_cast<float>(MousePos.y)))
        {
            button->ButtonSprite.setScale(1.1f, 1.1f); // �����ͣʱ�ı��С
        }
        else
        {
            button->ButtonSprite.setScale(1.0f, 1.0f); // ��겻������ʱ�ָ���С
        }
    }
}
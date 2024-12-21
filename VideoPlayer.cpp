#include "gButton.h"
#include "interface.h"
#include "bacisFunction.h"

#include <opencv2/core/utils/logger.hpp>

// ��ȡʱ��
string formatTime(double seconds)
{
    // ���ڽ���ʽ�����ַ���������ڴ��е���
    ostringstream oss;
    int minute = static_cast<int>(seconds) / 60;
    int second = static_cast<int>(seconds) % 60;
    // ������ʵ�ǽ��������oss��
    oss << setw(2) << setfill('0') << minute << ":"
        << setw(2) << setfill('0') << second;
    // ��ȡoss�е���Ϣ��Ϊһ��string���͵��ı�
    return oss.str();
}

void VideoPlay(sf::RenderWindow& window, ScreenState state, string& path,int flag, sf::Music& sound)
{
    //����ֻ��ʾ������־
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

    sound.pause();

    sf::Font font;
    // �����������򷵻ؽ���
    if (!font.loadFromFile("Font.ttf"))
    {
        cerr << "Failed to load font!" << endl;
        return;
    }

    cv::VideoCapture cap(path);
    // ������Ƶ�ļ�
    if (!cap.isOpened())
    {
        std::cerr << "Error: Cannot open video file!" << std::endl;
        return;
    }

    // �����˳���
    gButton BackButton = Back_Button(window);
    // ������ҳ����
    gButton HomeButton = Home_Button(window);
    // ʹ����͸���������ڱ�ʾ����
    BackButton.m_Rect.setFillColor(sf::Color::Transparent);
    HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f YiewBackgroundPosition(0, 0);
    sf::Vector2f YiewBackgroundSize(802, 603);
    gButton YiewBackgroundButton(YiewBackgroundPosition, YiewBackgroundSize, "FameBackground.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    YiewBackgroundButton.m_Rect.setFillColor(sf::Color::Transparent);

    // ��ȡ��Ƶ��Ϣ
    // ��ȡ��Ƶ֡������
    int frameCount = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
    // ��ȡ��Ƶ��֡�ʣ�ÿ�����֡��
    double fps = cap.get(cv::CAP_PROP_FPS);
    // ��Ƶ��ʱ�����룩
    double duration = frameCount / fps;
    // ��ȡ��Ƶ֡�Ŀ�Ⱥ͸߶�
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // ����ÿ��֡��Ϊ60
    window.setFramerateLimit(60);

    // ��Ƶ������;���
    sf::Texture texture;
    texture.create(width, height);
    sf::Sprite videoSprite(texture);
    videoSprite.setPosition(0.f, 40.f);

    // ������ͣ
    sf::Vector2f PausePosition(60.f, 500.f);
    sf::Vector2f PauseSize(60,60);
    gButton Pause(PausePosition, PauseSize, "Play.png", window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    Pause.m_Rect.setScale(0.35f, 0.35f);
    Pause.ButtonSprite.setScale(0.35f, 0.35f);
    Pause.m_Rect.setFillColor(sf::Color::Transparent);

    // ��������
    sf::Vector2f PlayPosition(60.f, 500.f);
    sf::Vector2f PlaySize(60,60);
    gButton Play(PlayPosition, PlaySize, "Pause.png", window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    Play.m_Rect.setScale(0.35f, 0.35f);
    Play.ButtonSprite.setScale(0.35f, 0.35f);
    Play.m_Rect.setFillColor(sf::Color::Transparent);

    gButton Pstate = Play;

    // ����������
    sf::RectangleShape Line(sf::Vector2f(600.f, 20.f));
    Line.setPosition(20,570);
    Line.setFillColor(sf::Color::Black);
    // ����������
    sf::RectangleShape Lin(sf::Vector2f(600.f, 20.f));
    Lin.setPosition(20, 570);
    Lin.setFillColor(sf::Color(143.0f, 143.0f, 143.0f));

    // ����
    float speed = 1.0;
    string text = "Speed";
    sf::Vector2f SpeedPosition(WINDOW_WIDTH - 80, WINDOW_HEIGHT - 42);
    sf::Vector2f SpeedSize(60, 40);
    gButton Speed(text, font, SpeedPosition, SpeedSize, 20, sf::Vector3f(255, 255, 255));
    Speed.m_Rect.setFillColor(sf::Color::Transparent);

    // ʱ��
    sf::Text timeText("00:00 / 00:00", font, 20);
    timeText.setFillColor(sf::Color::Black);
    timeText.setPosition(630.f, 568.f);

    // ���Ʊ���
    bool isPlaying = false;
    bool isDragging = false;
    // ��ǰʱ��λ��
    double currentPosition = 0.0;

    cv::Mat frame;
    // �������ػ�����, RGBA ��ʽ�Ļ�����
    sf::Uint8* pixels = new sf::Uint8[width * height * 4];

    // ��ѭ��
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Window_Close(window, event);
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (BackButton.if_contain(MousePos))
                {
                    sound.play();
                    state = (flag == 1)?ScreenState::Fame:ScreenState::Full; // �л�����һ������
                    return;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (HomeButton.if_contain(MousePos))
                {
                    sound.play();
                    state = ScreenState::MainScreen; // �л�����һ������
                    return;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                // ֻ�����϶������������л�����ʱ�Ų���������/��ͣ
                if (!isDragging)
                {
                    if (Play.if_contain(MousePos))
                    {
                        isPlaying = !isPlaying;
                        if (isPlaying)
                            Pstate = Play;
                        else
                            Pstate = Pause;
                    }
                }

                // �������
                if (Speed.if_contain(MousePos))
                {
                    speed *= 2;
                    if (speed > 2)
                        speed = 0.5f;
                }

                // �����������ת
                if (Lin.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    float mouseX = event.mouseButton.x - Lin.getPosition().x;
                    float LineWidth = Lin.getSize().x;
                    currentPosition = (mouseX / LineWidth) * duration;
                    // ��ת����λ��
                    cap.set(cv::CAP_PROP_POS_MSEC, currentPosition * 1000);
                }

                // �����Ƶ��ͣ/����
                if (videoSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    if (!isDragging)
                    {
                        isPlaying = !isPlaying;
                        if (isPlaying)
                            Pstate = Play;
                        else
                            Pstate = Pause;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                isDragging = false;
            }

            if (event.type == sf::Event::MouseMoved)
            {
                if (isDragging)
                {
                    // �϶�������
                    float mouseX = event.mouseMove.x;
                    float progressBarX = Line.getPosition().x;
                    float progressBarWidth = Line.getSize().x;

                    float newPos = (mouseX - progressBarX) / progressBarWidth;
                    // ��ֹԽ��
                    currentPosition = std::max(0.0, std::min(duration, newPos * duration));
                    // ͬ����Ƶλ��
                    cap.set(cv::CAP_PROP_POS_MSEC, currentPosition * 1000);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (Line.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    isDragging = true;
                }
            }
        }

        // ��ȡ��ǰ���ڴ�С��������������Ƶ��ʾ�ߴ�(������ԭ����)
        sf::Vector2u windowSize = window.getSize();
        float scaleX = static_cast<float>(windowSize.x) / width;
        float scaleY = static_cast<float>(windowSize.y) / height;
        float scale = std::min(scaleX, scaleY);
        videoSprite.setScale(scale, scale);

        // ������Ƶ֡
        if (isPlaying)
        {
            currentPosition += speed / fps;
            if (currentPosition >= duration)
            {
                isPlaying = false;
                // ���¿�ʼ
                currentPosition = 0.0;
                cap.set(cv::CAP_PROP_POS_FRAMES, 0);
            }
            else
            {
                cap.set(cv::CAP_PROP_POS_MSEC, currentPosition * 1000);
                cap.read(frame);
                if (!frame.empty())
                {
                    // �� OpenCV ֡ BGR ת��Ϊ RGBA ��ʽ
                    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGBA);
                    // ������ػ�����
                    std::memcpy(pixels, frame.data, frame.total() * frame.elemSize());
                    // ���� SFML ����
                    texture.update(pixels);
                }
            }
        }
        // ���½�����
        float progress = currentPosition / duration;
        Line.setSize(sf::Vector2f(progress * 600.f, 20.f));

        // ����ʱ����ʾ
        timeText.setString(formatTime(currentPosition) + " / " + formatTime(duration));
        window.clear(sf::Color::White);
        YiewBackgroundButton.Draw(window);
        if (!frame.empty())
        {
            window.draw(videoSprite);
        }
        window.draw(timeText);
        Pstate.Draw(window);
        Speed.Draw(window);
        BackButton.Draw(window);
        HomeButton.Draw(window);
        window.draw(Lin);
        window.draw(Line);
        window.display();
    }
}
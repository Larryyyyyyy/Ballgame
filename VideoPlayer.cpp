#include "gButton.h"
#include "interface.h"
#include "bacisFunction.h"

#include <opencv2/core/utils/logger.hpp>

// 获取时间
string formatTime(double seconds)
{
    // 用于将格式化的字符串输出到内存中的流
    ostringstream oss;
    int minute = static_cast<int>(seconds) / 60;
    int second = static_cast<int>(seconds) % 60;
    // 这里其实是将分秒存入oss中
    oss << setw(2) << setfill('0') << minute << ":"
        << setw(2) << setfill('0') << second;
    // 获取oss中的信息作为一个string类型的文本
    return oss.str();
}

void VideoPlay(sf::RenderWindow& window, ScreenState state, string& path,int flag, sf::Music& sound)
{
    //设置只显示错误日志
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

    sound.pause();

    sf::Font font;
    // 检查错误，如有则返回结束
    if (!font.loadFromFile("Font.ttf"))
    {
        cerr << "Failed to load font!" << endl;
        return;
    }

    cv::VideoCapture cap(path);
    // 加载视频文件
    if (!cap.isOpened())
    {
        std::cerr << "Error: Cannot open video file!" << std::endl;
        return;
    }

    // 加载退出键
    gButton BackButton = Back_Button(window);
    // 设置主页按键
    gButton HomeButton = Home_Button(window);
    // 使矩形透明，仅用于表示区域
    BackButton.m_Rect.setFillColor(sf::Color::Transparent);
    HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

    sf::Vector2f YiewBackgroundPosition(0, 0);
    sf::Vector2f YiewBackgroundSize(802, 603);
    gButton YiewBackgroundButton(YiewBackgroundPosition, YiewBackgroundSize, "FameBackground.png", window, sf::Vector3f(0.f, 0.f, 0.f));
    YiewBackgroundButton.m_Rect.setFillColor(sf::Color::Transparent);

    // 获取视频信息
    // 获取视频帧的总数
    int frameCount = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
    // 获取视频的帧率（每秒多少帧）
    double fps = cap.get(cv::CAP_PROP_FPS);
    // 视频总时长（秒）
    double duration = frameCount / fps;
    // 获取视频帧的宽度和高度
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // 设置每秒帧数为60
    window.setFramerateLimit(60);

    // 视频的纹理和精灵
    sf::Texture texture;
    texture.create(width, height);
    sf::Sprite videoSprite(texture);
    videoSprite.setPosition(0.f, 40.f);

    // 创建暂停
    sf::Vector2f PausePosition(60.f, 500.f);
    sf::Vector2f PauseSize(60,60);
    gButton Pause(PausePosition, PauseSize, "Play.png", window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    Pause.m_Rect.setScale(0.35f, 0.35f);
    Pause.ButtonSprite.setScale(0.35f, 0.35f);
    Pause.m_Rect.setFillColor(sf::Color::Transparent);

    // 创建播放
    sf::Vector2f PlayPosition(60.f, 500.f);
    sf::Vector2f PlaySize(60,60);
    gButton Play(PlayPosition, PlaySize, "Pause.png", window, sf::Vector3f(150.0f, 100.0f, 250.0f));
    Play.m_Rect.setScale(0.35f, 0.35f);
    Play.ButtonSprite.setScale(0.35f, 0.35f);
    Play.m_Rect.setFillColor(sf::Color::Transparent);

    gButton Pstate = Play;

    // 创建进度条
    sf::RectangleShape Line(sf::Vector2f(600.f, 20.f));
    Line.setPosition(20,570);
    Line.setFillColor(sf::Color::Black);
    // 创建进度条
    sf::RectangleShape Lin(sf::Vector2f(600.f, 20.f));
    Lin.setPosition(20, 570);
    Lin.setFillColor(sf::Color(143.0f, 143.0f, 143.0f));

    // 倍速
    float speed = 1.0;
    string text = "Speed";
    sf::Vector2f SpeedPosition(WINDOW_WIDTH - 80, WINDOW_HEIGHT - 42);
    sf::Vector2f SpeedSize(60, 40);
    gButton Speed(text, font, SpeedPosition, SpeedSize, 20, sf::Vector3f(255, 255, 255));
    Speed.m_Rect.setFillColor(sf::Color::Transparent);

    // 时间
    sf::Text timeText("00:00 / 00:00", font, 20);
    timeText.setFillColor(sf::Color::Black);
    timeText.setPosition(630.f, 568.f);

    // 控制变量
    bool isPlaying = false;
    bool isDragging = false;
    // 当前时间位置
    double currentPosition = 0.0;

    cv::Mat frame;
    // 创建像素缓冲区, RGBA 格式的缓冲区
    sf::Uint8* pixels = new sf::Uint8[width * height * 4];

    // 主循环
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
                    state = (flag == 1)?ScreenState::Fame:ScreenState::Full; // 切换到另一个界面
                    return;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (HomeButton.if_contain(MousePos))
                {
                    sound.play();
                    state = ScreenState::MainScreen; // 切换到另一个界面
                    return;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                // 只有在拖动进度条或者切换倍速时才不触发播放/暂停
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

                // 点击倍速
                if (Speed.if_contain(MousePos))
                {
                    speed *= 2;
                    if (speed > 2)
                        speed = 0.5f;
                }

                // 点击进度条跳转
                if (Lin.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    float mouseX = event.mouseButton.x - Lin.getPosition().x;
                    float LineWidth = Lin.getSize().x;
                    currentPosition = (mouseX / LineWidth) * duration;
                    // 跳转到该位置
                    cap.set(cv::CAP_PROP_POS_MSEC, currentPosition * 1000);
                }

                // 点击视频暂停/播放
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
                    // 拖动进度条
                    float mouseX = event.mouseMove.x;
                    float progressBarX = Line.getPosition().x;
                    float progressBarWidth = Line.getSize().x;

                    float newPos = (mouseX - progressBarX) / progressBarWidth;
                    // 防止越界
                    currentPosition = std::max(0.0, std::min(duration, newPos * duration));
                    // 同步视频位置
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

        // 获取当前窗口大小并按比例调整视频显示尺寸(但仍是原比例)
        sf::Vector2u windowSize = window.getSize();
        float scaleX = static_cast<float>(windowSize.x) / width;
        float scaleY = static_cast<float>(windowSize.y) / height;
        float scale = std::min(scaleX, scaleY);
        videoSprite.setScale(scale, scale);

        // 更新视频帧
        if (isPlaying)
        {
            currentPosition += speed / fps;
            if (currentPosition >= duration)
            {
                isPlaying = false;
                // 重新开始
                currentPosition = 0.0;
                cap.set(cv::CAP_PROP_POS_FRAMES, 0);
            }
            else
            {
                cap.set(cv::CAP_PROP_POS_MSEC, currentPosition * 1000);
                cap.read(frame);
                if (!frame.empty())
                {
                    // 将 OpenCV 帧 BGR 转换为 RGBA 格式
                    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGBA);
                    // 填充像素缓冲区
                    std::memcpy(pixels, frame.data, frame.total() * frame.elemSize());
                    // 更新 SFML 纹理
                    texture.update(pixels);
                }
            }
        }
        // 更新进度条
        float progress = currentPosition / duration;
        Line.setSize(sf::Vector2f(progress * 600.f, 20.f));

        // 更新时间显示
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
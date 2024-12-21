#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include"interface.h"

using namespace std;

atomic<bool> running(true); //用于线程间同步
mutex mtx; //用于保护共享资源

//用于处理文本换行
void wrapText(const string& input, sf::Text& text, sf::Font& font, float maxWidth) 
{
    string currentLine;
    vector<string> lines;
    float lineWidth = 0.f;

    for (char c : input)
    {
        currentLine += c;
        text.setString(currentLine);
        lineWidth = text.getLocalBounds().width;

        if (lineWidth > maxWidth)
        { //如果文本宽度超过最大宽度
            lines.push_back(currentLine.substr(0, currentLine.size() - 1)); //去掉最后一个字符
            currentLine = currentLine.substr(currentLine.size() - 1); //保留当前超出的字符
        }
    }

    if (!currentLine.empty()) 
    {
        lines.push_back(currentLine); //把最后一行添加到行列表中
    }

    string wrappedText = "";
    for (const string& line : lines)
    {
        wrappedText += line + "\n"; //将分割后的行重新组成一个字符串
    }

    text.setString(wrappedText);
}

void receiving(sf::TcpSocket& socket, vector<sf::Text>& MesText, vector<sf::RectangleShape>& MesRec, vector<sf::Sprite>& MesSpr, sf::RenderWindow& window, sf::Font& font, int& count, sf::Texture& dialogueText) 
{
    char data[200];
    size_t received;
    count = 0;

    while (running) 
    {
        if (socket.receive(data, sizeof(data), received) == sf::Socket::Done)
        {
            string message(data, received);

            //去除末尾的空字符
            while (!message.empty() && (message.back() == '\0' || message.back() == '\n' || message.back() == '\r'))
            {
                message.pop_back();
            }

            //使用互斥锁保护共享资源
            lock_guard<mutex> lock(mtx);

            //创建消息文本
            sf::Text mestext;
            mestext.setFillColor(sf::Color::Black);
            mestext.setFont(font);
            mestext.setCharacterSize(35);
            wrapText(message, mestext, font, 640.f); //传入最大宽度 656

            // 精灵
            sf::Sprite messpr(dialogueText);
            messpr.setPosition(5, 60 * count); 
            messpr.setScale(sf::Vector2f((mestext.getLocalBounds().width + 20) / 833, (mestext.getLocalBounds().height-20) / 143));

            //创建消息背景矩形
            sf::RectangleShape mesrec;
            mesrec.setFillColor(sf::Color::Transparent);
            mesrec.setSize(sf::Vector2f(mestext.getLocalBounds().width + 20.f, mestext.getLocalBounds().height + 10.f)); //框长度比文字稍长
            mesrec.setPosition(5, 60 * count); 

            //将消息和背景添加到显示列表
            MesRec.push_back(mesrec);
            MesText.push_back(mestext);
            MesSpr.push_back(messpr);

            count++;
        }

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                running = false;
                window.close();
            }
        }
    }
}

void sending(sf::TcpSocket& socket, string& input, atomic<bool>& if_Enter, int& count) 
{
    while (running)
    {
        if (if_Enter)
        {
            if (!input.empty())
            {
                socket.send(input.c_str(), input.size() + 1);
                input.clear();
            }
            if_Enter = false;
        }
    }
}

int Dialogue(string name)
{
    sf::TcpSocket socket;

    int count = 0;

    //连接服务器
    if (socket.connect("10.128.2.71", 53001) != sf::Socket::Done)
    {
        cerr << "Error: Unable to connect to server!" << endl;
        return -1;
    }

    //发送用户名到服务器
    if (socket.send(name.c_str(), name.size() + 1) != sf::Socket::Done)
    {
        cerr << "Error sending name to server!" << endl;
        return -1;
    }

    cout << "Connected to server..." << endl;

    sf::RenderWindow window(sf::VideoMode(656, 480), "Chatting");

    sf::Font font;
    if (!font.loadFromFile("Font.ttf"))
    {
        cerr << "Failed to load font!" << endl;
        return -1;
    }

    vector<sf::Text> MesText;
    vector<sf::RectangleShape> MesRec;
    vector<sf::Sprite> MesSpr;

    //聊天背景
    sf::Texture dialoguebackText;
    if (!dialoguebackText.loadFromFile("Backgr.png"))
    {
        cerr << "Unable to load the DialoguePicture!" << endl;
        return -1;
    }
    sf::Sprite mesback(dialoguebackText);
    mesback.setPosition(0, 0);
    mesback.setScale(sf::Vector2f(0.23985f, 0.31270f));

    //视图
    sf::View MainView(sf::FloatRect(0, 0, 656, 480));
    sf::View MiniView(sf::FloatRect(0, 0, 656, 450));
    MiniView.setViewport(sf::FloatRect(0.f, 0.0f, 1.f, 0.90f));

    //聊天气泡
    sf::Texture dialogueText;
    if (!dialogueText.loadFromFile("dialogue.png")) 
    {
        cerr << "Unable to load the DialoguePicture!" << endl;
        return -1;
    }

    //返回按键
    sf::Texture back;
    if (!back.loadFromFile("BackDown.png"))
    {
        cerr << "Unable to load the DialoguePicture!" << endl;
        return -1;
    }
    sf::Sprite Back(back);
    Back.setPosition(620, 450);
    Back.setScale(0.25f, 0.25f);
    sf::RectangleShape Backrec(sf::Vector2f(32.f, 32.f));
    Backrec.setFillColor(sf::Color::Transparent);
    Backrec.setPosition(620, 450);

    //创建输入框的文本
    sf::Text inputText("", font, 20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(10, 450);

    //输入框背景
    sf::RectangleShape inputLine(sf::Vector2f(620.f, 25.f));
    inputLine.setFillColor(sf::Color(189, 189, 189));
    inputLine.setPosition(0.f, 450.f);

    string mesinput = "";

    atomic<bool> if_Enter(false);

    //启动接收消息的线程
    thread ReceiveThread(receiving, ref(socket), ref(MesText), ref(MesRec), ref(MesSpr), ref(window), ref(font), ref(count), ref(dialogueText));

    //启动发送消息的线程
    thread SendThread(sending, ref(socket), ref(mesinput), ref(if_Enter), ref(count));

    //偏移量
    float scroll = 0;

    //标志当前是否在最底部
    bool isBottom = true;

    //主循环
    while (window.isOpen() && running)
    {
        sf::Event event;

        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !mesinput.empty())
                {
                    mesinput.pop_back();
                }
                //只将标志设为 true，不附加名字
                else if (event.text.unicode == '\r') 
                {
                    if_Enter = true; 
                }
                else if (event.text.unicode < 128 || event.text.unicode >= 0x4E00)
                {
                    mesinput += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled) 
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    scroll -= event.mouseWheelScroll.delta * 60; //改为60
                    if (scroll < 0)
                    {
                        scroll = 0;
                    }
                    if (count > 7 && scroll > (count - 7) * 60)
                    { 
                        scroll = (count - 7) * 60;
                    }
                    isBottom = false; 
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (Backrec.getGlobalBounds().contains(static_cast<float>(MousePos.x), static_cast<float>(MousePos.y)))
                {
                    scroll = (count > 7) ? (count - 7) * 60 : 0;
                    isBottom = true; //滚动回到底部
                }

                if (event.type == sf::Event::Closed) 
                {
                    running = false;
                    window.close();
                }
            }
        }

        //更新消息位置
        for (int i = 0; i < count; i++) 
        {
            MesText[i].setPosition(sf::Vector2f(10, (i * 60) - scroll)); 
            MesRec[i].setPosition(sf::Vector2f(0, (i * 60) - scroll));
            MesSpr[i].setPosition(sf::Vector2f(0, (i * 60) - scroll)); 
        }

        //更新输入框显示内容
        inputText.setString(mesinput);

        //自动滚动到底部
        if (isBottom && count > 7) 
        {
            scroll = (count - 7) * 60; 
        }

        window.clear(sf::Color::White);

        window.setView(MainView);

        window.draw(mesback);
        window.draw(inputLine);
        window.draw(inputText);

        window.draw(Back);
        window.draw(Backrec);

        window.setView(MiniView);

        //绘制接收到的历史消息
        {
            lock_guard<mutex> lock(mtx); //加锁，确保线程安全

            for (size_t i = 0; i < MesText.size(); ++i)
            {
                window.draw(MesSpr[i]);
                window.draw(MesText[i]);
                window.draw(MesRec[i]);
            }
        }

        window.display();
    }

    //确保线程在退出前完成
    ReceiveThread.join();
    SendThread.join();

    return 0;
}

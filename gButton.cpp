#include"gButton.h"

//文字按键的构造函数
gButton::gButton(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color)
{
    flag = 0;
    //设置选项文字
    m_Text.setString(text);

    //设置选项字体
    m_Text.setFont(font);

    //设置字体大小
    m_Text.setCharacterSize(CharacterSize);

    //设置字体颜色
    m_Text.setFillColor(sf::Color::Black);

    //设置选项位置
    m_Rect.setPosition(position);

    //设置选项大小
    m_Rect.setSize(size);
    
    //设置选项颜色
    m_Rect.setFillColor(sf::Color((int)color.x, (int)color.y, (int)color.z));

    //获取文本的局部边界
    sf::FloatRect textRect = m_Text.getLocalBounds();

    //文本的原点（origin）和位置（position）是两个不同的概念；
    // 它们分别控制文本对象的旋转中心和绘制位置
    //设置文本原点
    m_Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    //设置文本位置
    m_Text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

//图片按钮的构造函数
gButton::gButton(const sf::Vector2f& position, const sf::Vector2f& size,const string& path, sf::RenderWindow& window, const sf::Vector3f& color)
{
    flag = 1;
    //设置选项大小
    m_Rect.setSize(size);

    //设置选项颜色
    m_Rect.setFillColor(sf::Color((int)color.x, (int)color.y, (int)color.z));

    //设置选项位置
    m_Rect.setPosition(position);

    //这里有改动！
    if (path != "")
    {
        // 加载纹理
        if (!texture.loadFromFile(path)) {
            return; // 加载失败
        }

        // 获取纹理的大小
        sf::Vector2u ButtonSize = texture.getSize();

        //获取比例
        double RateWidth = (double)size.x / ButtonSize.x;
        double RateHeight = (double)size.y / ButtonSize.y;

        // 创建精灵
        ButtonSprite.setTexture(texture);

        //实现放缩
        ButtonSprite.setScale(RateWidth, RateHeight);

        // 设置精灵的位置
        ButtonSprite.setPosition(position); // 可以设置为矩形的坐标
    }

    // 创建矩形形状
    m_Rect.setPosition(position); // 矩形的位置与精灵的位置相同
}

//在屏幕上显示按键
void gButton::Draw(sf::RenderWindow& window) const
{
    //将矩阵绘制到窗口上
    window.draw(m_Rect);

    if (flag == 1)
    {
        //将图片绘制到窗口上
        window.draw(ButtonSprite);
    }
    if(flag == 0)
    {
        //将文本绘制到窗口上
        window.draw(m_Text);
    }
}

//检查鼠标点击（piont）是否在区域内
bool gButton::if_contain(const sf::Vector2f& point) const
{
    //m_Rect.getGlobalBounds()可以获取矩阵的全边界
    //.contains(point)可以检查给定的点point是否在矩阵全局边界内部
    //返回值是bool
    return m_Rect.getGlobalBounds().contains(point);
}
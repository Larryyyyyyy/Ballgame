#include "button_.h"

//���ְ����Ĺ��캯��
button_::button_(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color)
{
    flag = 0;
    //����ѡ������
    m_Text.setString(text);

    //����ѡ������
    m_Text.setFont(font);

    //���������С
    m_Text.setCharacterSize(CharacterSize);

    //����������ɫ
    m_Text.setFillColor(sf::Color::Black);

    //����ѡ��λ��
    m_Rect.setPosition(position);

    //����ѡ���С
    m_Rect.setSize(size);

    //����ѡ����ɫ
    m_Rect.setFillColor(sf::Color((int)color.x, (int)color.y, (int)color.z));

    //����ѡ��λ��
    m_Rect.setPosition(position);

    //��ȡ�ı��ľֲ��߽�
    sf::FloatRect textRect = m_Text.getLocalBounds();

    //�ı���ԭ�㣨origin����λ�ã�position����������ͬ�ĸ��
    // ���Ƿֱ�����ı��������ת���ĺͻ���λ��
    //�����ı�ԭ��
    m_Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    //�����ı�λ��
    m_Text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

button_::button_(const string& text, const std::string& path, const sf::Vector2f& position, const sf::Vector2f& size, int CharacterSize, const sf::Vector3f& color)
{
    flag = 0;
    //����ѡ������
    m_Text.setString(text);

    //����ѡ������
    sf::Font font;
    font.loadFromFile(path);
    m_Text.setFont(font);

    //���������С
    m_Text.setCharacterSize(CharacterSize);

    //����������ɫ
    m_Text.setFillColor(sf::Color::Black);

    //����ѡ��λ��
    m_Rect.setPosition(position);

    //����ѡ���С
    m_Rect.setSize(size);

    //����ѡ����ɫ
    m_Rect.setFillColor(sf::Color((int)color.x, (int)color.y, (int)color.z));

    //����ѡ��λ��
    m_Rect.setPosition(position);

    //��ȡ�ı��ľֲ��߽�
    sf::FloatRect textRect = m_Text.getLocalBounds();

    //�ı���ԭ�㣨origin����λ�ã�position����������ͬ�ĸ��
    // ���Ƿֱ�����ı��������ת���ĺͻ���λ��
    //�����ı�ԭ��
    m_Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    //�����ı�λ��
    m_Text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}



//ͼƬ��ť�Ĺ��캯��
button_::button_(const sf::Vector2f& position, const sf::Vector2f& size, const string& path, sf::RenderWindow& window, const sf::Vector3f& color)
{
    flag = 1;
    //����ѡ���С
    m_Rect.setSize(size);

    //����ѡ����ɫ
    m_Rect.setFillColor(sf::Color((int)color.x, (int)color.y, (int)color.z));

    //����ѡ��λ��
    m_Rect.setPosition(position);

    // ��������
    if (!texture.loadFromFile(path)) {
        std::cerr << "�޷�����ͼƬ��" << std::endl;
        return; // ����ʧ��
    }


    // ��ȡ����Ĵ�С
    sf::Vector2u ButtonSize = texture.getSize();

    //��ȡ����
    double RateWidth = (double)size.x / ButtonSize.x;
    double RateHeight = (double)size.y / ButtonSize.y;

    // ��������
    ButtonSprite.setTexture(texture);

    //ʵ�ַ���
    ButtonSprite.setScale(RateWidth, RateHeight);

    // ���þ����λ��
    ButtonSprite.setPosition(position); // ��������Ϊ���ε�����

    // ����������״
    m_Rect.setPosition(position); // ���ε�λ���뾫���λ����ͬ
    m_Rect.setFillColor(sf::Color::Transparent); // ʹ����͸���������ڱ�ʾ����
}

//����Ļ����ʾ����
void button_::Draw(sf::RenderWindow& window) const
{
    //��������Ƶ�������
    window.draw(m_Rect);

    if (flag == 1)
    {
        //��ͼƬ���Ƶ�������
        window.draw(ButtonSprite);
    }
    if (flag == 0)
    {
        //���ı����Ƶ�������
        window.draw(m_Text);
    }
}

//����������piont���Ƿ���������
bool button_::if_contain(const sf::Vector2f& point) const
{
    //m_Rect.getGlobalBounds()���Ի�ȡ�����ȫ�߽�
    //.contains(point)���Լ������ĵ�point�Ƿ��ھ���ȫ�ֱ߽��ڲ�
    //����ֵ��bool
    return m_Rect.getGlobalBounds().contains(point);
}

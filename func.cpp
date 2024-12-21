#include"func.h"
#include"task.h"
#include <SFML/Graphics.hpp>
#include<sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include<windows.h>
#include <sstream>
#include<cstdlib>
#include<ctime>
#include<memory>
using namespace std;
//��ɫ����������ʾ���ӵĽ���ɫ
const char* vertexShaderSource =
//������ɫ��,���𽫶���λ��ת������Ļ�ռ�,����������þ��ǽ�ԭʼ�Ķ�������ͨ�� gl_ModelViewProjectionMatrix ����ۺϱ任������б任��
//�õ��ڲü��ռ�����꣬����ֵ�� gl_Position���Ӷ���ɽ�����λ�ô�ģ�Ϳռ�ת������Ļ�ռ��һ���ؼ����衣
"void main() {\n"
"    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
"    gl_TexCoord[0] = gl_MultiTexCoord0;\n"
"}\n";


const char* fragmentShaderSource =//Ƭ����ɫ��,����ÿ�����ص���ɫ
"uniform vec3 leftColor;\n"
"uniform vec3 rightColor;\n"
"void main() {\n"
"    float x = gl_TexCoord[0].x;\n"
"    vec3 color = mix(leftColor, rightColor, x);\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

int midtext(sf::Text& text, sf::RenderWindow& window) {//���ļ�������ʾ
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    text.setPosition(window.getSize().x / static_cast<float>(2), window.getSize().y / static_cast<float>(2));
    return 0;
}

void modifypassword(const string& username,const string& userpassword) {
    sqlite3* db;
    int rc = sqlite3_open("avatar.db", &db);
    if (rc) {
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
        return ;
    }

    const string sql = "UPDATE avatar SET userpassword = '" +userpassword+"'"+" WHERE username = '"+username+"'";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "׼��SQL������: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return ;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "ִ��SQL������: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
void modifycoins(const string& username, const int add) {
    sqlite3* db;
    char* errMsg = 0;
    int rc = sqlite3_open("avatar.db", &db);
    if (rc){
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
        return ;
    }
    const string sql = "UPDATE avatar SET coins = coins + "+to_string(add)+" WHERE username = '"+username+"'";
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    cout << "+10";
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL����: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);
    return ;
}
void modifypoints(const string& username, const int add) {
    sqlite3* db;
    char* errMsg = 0;
    int rc = sqlite3_open("avatar.db", &db);
    if (rc) {
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const string sql = "UPDATE avatar SET points = points " + to_string(add) + " WHERE username = '" + username+"'";
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL����: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);
    return;
}
unique_ptr<sf::Shader> loadColor(sf::Vector3f& lefcolor,sf::Vector3f& rigcolor) {
    /*unique_ptr��c++�ṩ������ָ�룬�������Զ����delete���ܣ����Խ�new��õĶ����ַ��ֵ�������ṩ.get()������Ϊ������
    ͬʱ���ṩ��release()��ȡ������ָ����йܣ����ṩreset()������ָ��ĵ�ַ*/
    unique_ptr<sf::Shader> shader = make_unique<sf::Shader>();
    if (!shader->loadFromMemory(vertexShaderSource, fragmentShaderSource))//������ɫ��
    {
        //cout << "p";
        cerr << "��ɫ������ʧ��" << endl;
        return nullptr;
    }
    shader->setUniform("leftColor", lefcolor);  // ���Ϊ��ɫ
    shader->setUniform("rightColor", rigcolor); // �ұ�Ϊ��ɫ
    return shader;
}
int test() {
    return 0;
}
Button::Button() {

}
Button::Button(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size,int flag)
{
    
    
    //����ѡ������
    m_Text.setString(text);

    //����ѡ������
    m_Text.setFont(font);

    //���������С
    m_Text.setCharacterSize(24);

    //����������ɫ
    m_Text.setFillColor(sf::Color::Black);

    //����ѡ��λ��
    m_Rect.setPosition(position);

    //����ѡ���С
    m_Rect.setSize(size);


    //����ѡ��λ��
    m_Rect.setPosition(position);


    //��ȡ�ı��ľֲ��߽�
    sf::FloatRect textRect = m_Text.getLocalBounds();

    //�ı���ԭ�㣨origin����λ�ã�position����������ͬ�ĸ��
    // ���Ƿֱ�����ı��������ת���ĺͻ���λ��
    // 
    //�����ı�ԭ��
    m_Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    //�����ı�λ��
    m_Text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}
void Button::Draw(sf::RenderWindow& window) const
{
    //��������Ƶ�������
    window.draw(m_Rect);

    //���ı����Ƶ�������
    window.draw(m_Text);
}

bool Button::if_contain(const sf::Vector2f& point) const
{
    //m_Rect.getGlobalBounds()���Ի�ȡ�����ȫ�߽�
    //.contains(point)���Լ����������ĵ�point�Ƿ��ھ���ȫ�ֱ߽��ڲ�
    //����ֵ��bool
    return m_Rect.getGlobalBounds().contains(point);
}

void colorful(const sf::Text& text,sf::RenderWindow & window) {//���ı�ת��Ϊ�ʺ�ɫ��ʾ
    /*�Ƚ��鷳��ԭ����������һ��һ�������ĸ�ģ�ÿ����ĸ�����Լ��Ŀ�ȣ�����Ҫ��֤������ĸ֮������ͬ��ʹ�����ǲ���ֱ�ӽ����ÿ�μ�һ����ֵ�����������*/
    string textString = text.getString();
    vector<sf::Text>  characterTexts;
    vector<sf::Text>  characterTexts1;
    srand(static_cast<unsigned int>(time(nullptr)));


    // ���������ַ����ܿ�ȣ���������ࣩ
    float totalCharWidth = 0.0f;
    for (int i = 0; i < textString.length(); i++)
    {
        sf::Text tempText;
        const sf::Font* fontPtr = text.getFont();
        if (fontPtr != nullptr)
        {
            tempText.setFont(*fontPtr);
        }
        tempText.setCharacterSize(text.getCharacterSize());
        tempText.setString(textString.substr(i, 1));
        sf::FloatRect bounds = tempText.getLocalBounds();
        totalCharWidth += bounds.width;
    }
    // �����������ַ�������ΪfixedSpacing�����磬5.0f��
    const float fixedSpacing = 5.0f;
    float totalExpectedWidth = totalCharWidth + (textString.length() - 1) * fixedSpacing;
    // ����ʣ��ɷ���ļ��ռ䣨��ȥ�ַ�ʵ�ʿ�Ⱥ�ļ��ռ䣩
    float remainingSpacingSpace = totalExpectedWidth - totalCharWidth;



    sf::Vector2f firstCharacterPos = text.findCharacterPos(0);
    float currentX = firstCharacterPos.x;

    for (int i = 0; i < textString.length(); i++)
    {
        sf::Text characterText;
        const sf::Font* fontPtr = text.getFont();
         if (fontPtr != nullptr)
         {
             characterText.setFont(*fontPtr);
         }
        characterText.setCharacterSize(text.getCharacterSize());
        characterText.setString(textString.substr(i, 1));
        sf::FloatRect bounds = characterText.getLocalBounds();
        // ���㵱ǰ�ַ����ռ���ַ���ȵı���
        float widthProportion = bounds.width / totalCharWidth;
        // ���ݱ�������ʣ����ռ䵽��ǰ�ַ�����
        float sideSpacing = remainingSpacingSpace * widthProportion / 2.0f;
        characterText.setPosition(currentX+sideSpacing, text.getPosition().y );
        currentX += (bounds.width+sideSpacing) ;
        sf::Color randomColor(static_cast<sf::Uint8>(rand() % 256), static_cast<sf::Uint8>(rand() % 256), static_cast<sf::Uint8>(rand() % 256));
        characterText.setFillColor(randomColor);
        characterTexts.push_back(characterText);
    }
    for (auto& outtext : characterTexts) {
        window.draw(outtext);
    }
}

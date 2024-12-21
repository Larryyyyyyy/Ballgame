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
//着色器，用来显示复杂的渐变色
const char* vertexShaderSource =
//顶点着色器,负责将顶点位置转换到屏幕空间,这句代码的作用就是将原始的顶点坐标通过 gl_ModelViewProjectionMatrix 这个综合变换矩阵进行变换，
//得到在裁剪空间的坐标，并赋值给 gl_Position，从而完成将顶点位置从模型空间转换到屏幕空间的一个关键步骤。
"void main() {\n"
"    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
"    gl_TexCoord[0] = gl_MultiTexCoord0;\n"
"}\n";


const char* fragmentShaderSource =//片段着色器,计算每个像素的颜色
"uniform vec3 leftColor;\n"
"uniform vec3 rightColor;\n"
"void main() {\n"
"    float x = gl_TexCoord[0].x;\n"
"    vec3 color = mix(leftColor, rightColor, x);\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

int midtext(sf::Text& text, sf::RenderWindow& window) {//将文件居中显示
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    text.setPosition(window.getSize().x / static_cast<float>(2), window.getSize().y / static_cast<float>(2));
    return 0;
}

void modifypassword(const string& username,const string& userpassword) {
    sqlite3* db;
    int rc = sqlite3_open("avatar.db", &db);
    if (rc) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        return ;
    }

    const string sql = "UPDATE avatar SET userpassword = '" +userpassword+"'"+" WHERE username = '"+username+"'";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "准备SQL语句出错: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return ;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "执行SQL语句出错: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
void modifycoins(const string& username, const int add) {
    sqlite3* db;
    char* errMsg = 0;
    int rc = sqlite3_open("avatar.db", &db);
    if (rc){
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        return ;
    }
    const string sql = "UPDATE avatar SET coins = coins + "+to_string(add)+" WHERE username = '"+username+"'";
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    cout << "+10";
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL错误: " << errMsg << std::endl;
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
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const string sql = "UPDATE avatar SET points = points " + to_string(add) + " WHERE username = '" + username+"'";
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL错误: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);
    return;
}
unique_ptr<sf::Shader> loadColor(sf::Vector3f& lefcolor,sf::Vector3f& rigcolor) {
    /*unique_ptr是c++提供的智能指针，它可以自动完成delete功能，可以将new获得的对象地址赋值给它，提供.get()函数意为解引用
    同时还提供了release()以取消智能指针的托管，还提供reset()来重置指向的地址*/
    unique_ptr<sf::Shader> shader = make_unique<sf::Shader>();
    if (!shader->loadFromMemory(vertexShaderSource, fragmentShaderSource))//加载着色器
    {
        //cout << "p";
        cerr << "着色器加载失败" << endl;
        return nullptr;
    }
    shader->setUniform("leftColor", lefcolor);  // 左边为红色
    shader->setUniform("rightColor", rigcolor); // 右边为蓝色
    return shader;
}
int test() {
    return 0;
}
Button::Button() {

}
Button::Button(const string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size,int flag)
{
    
    
    //设置选项文字
    m_Text.setString(text);

    //设置选项字体
    m_Text.setFont(font);

    //设置字体大小
    m_Text.setCharacterSize(24);

    //设置字体颜色
    m_Text.setFillColor(sf::Color::Black);

    //设置选项位置
    m_Rect.setPosition(position);

    //设置选项大小
    m_Rect.setSize(size);


    //设置选项位置
    m_Rect.setPosition(position);


    //获取文本的局部边界
    sf::FloatRect textRect = m_Text.getLocalBounds();

    //文本的原点（origin）和位置（position）是两个不同的概念；
    // 它们分别控制文本对象的旋转中心和绘制位置
    // 
    //设置文本原点
    m_Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    //设置文本位置
    m_Text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}
void Button::Draw(sf::RenderWindow& window) const
{
    //将矩阵绘制到窗口上
    window.draw(m_Rect);

    //将文本绘制到窗口上
    window.draw(m_Text);
}

bool Button::if_contain(const sf::Vector2f& point) const
{
    //m_Rect.getGlobalBounds()可以获取矩阵的全边界
    //.contains(point)可以见擦汗给定的点point是否在矩阵全局边界内部
    //返回值是bool
    return m_Rect.getGlobalBounds().contains(point);
}

void colorful(const sf::Text& text,sf::RenderWindow & window) {//将文本转化为彩虹色显示
    /*比较麻烦的原因是我们是一个一个输出字母的，每个字母都有自己的宽度，我们要保证两个字母之间宽度相同，使得我们不能直接将间距每次加一个定值，必须算出来*/
    string textString = text.getString();
    vector<sf::Text>  characterTexts;
    vector<sf::Text>  characterTexts1;
    srand(static_cast<unsigned int>(time(nullptr)));


    // 计算所有字符的总宽度（不包括间距）
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
    // 假设期望的字符间隔宽度为fixedSpacing（例如，5.0f）
    const float fixedSpacing = 5.0f;
    float totalExpectedWidth = totalCharWidth + (textString.length() - 1) * fixedSpacing;
    // 计算剩余可分配的间距空间（除去字符实际宽度后的间距空间）
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
        // 计算当前字符宽度占总字符宽度的比例
        float widthProportion = bounds.width / totalCharWidth;
        // 根据比例分配剩余间距空间到当前字符两侧
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

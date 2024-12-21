#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <vector>
#include <sqlite3.h>
#include"func.h"
#include"player.h"
#include"registerlogin.h"
#include"task.h"
using namespace std;

player ret;
vector<Button> button;
vector<string> ButtonLabel = { "register","login","confirm" ,"zhaohui"};
float ButtonWidth = 150;
float ButtonHeight = 50;
float ButtonSpace = 30;
float ButtonStartX = (650 - ButtonWidth) / 2.0f;
float ButtonStartY = 280;//按钮的实现
sf::Text Welcome;
sf::RectangleShape rec,inputRec;
sf::Vector3f leftColor(1.0, 0.7137, 0.7569);//淡粉色
sf::Vector3f rightColor(0.6784, 0.8471, 0.9020);//淡蓝色
unique_ptr<sf::Shader> shader;//智能指针

sf::Font font,font_youyuan,font_bri;
std::string filename = "user_log.txt";//注册日志文件
sf::Texture image;
sf::Vector2u screenSize(802, 602);
float scaleX, scaleY;
sf::Vector2u imageSize;
vector<player> checklist;
void registerUser(const string& filename,sf::RenderWindow &window);
int callback(void* data, int argc, char** argv, char** azColName) {//回调函数，argc为列数，argv为字符串数组，最后一个存储列名
	checklist.emplace_back(player(argv[0], argv[1], argv[2], 0));
	return 0;
}
player check( const string& user) {//检查输入用户名是否已经注册，mode为0检查用户名，为1检查密码 ,2检查密保
	checklist.clear();
	sqlite3* db;
	int rc = sqlite3_open("player.db", &db);
	if (rc != SQLITE_OK) {
		// 处理打开数据库错误
		cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return player();
	}

	string query = "SELECT * FROM player";//读取所有列数据

	char* errMsg = nullptr;
	rc = sqlite3_exec(db, query.c_str(), callback, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		// 处理查询执行错误
		cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	sqlite3_close(db);
	for (int i = 0;i < checklist.size();i++) {
		if (checklist[i].getName() == user) return player(user,checklist[i].getpassword(),checklist[i].getmibao(),checklist[i].getCoins(),checklist[i].getPoints());
	}
	return player();
}
void findUser(sf::RenderWindow & window,player & user) {
	/*ifstream file(filename);
	string userans;
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ins(line);
			string username, userpassword, usermibao, usercoin, userachievement;
			ins >> username;
			ins >> userpassword;
			ins >> usermibao;
			ins >> usercoin;
			ins >> userachievement;
			if (username == user) {
				userans = userpassword;
				break;
			}
		}
	}*/
	sf::Sprite sprite(image);
	scaleX = (float)screenSize.x / imageSize.x;
	scaleY = (float)screenSize.y / imageSize.y;
	imageSize = image.getSize();
	sprite.setScale(scaleX, scaleY);//使背景图片能够全屏显示

	sf::Text inputText, success, cue, fail;
	inputText.setFont(font);
	inputText.setCharacterSize(24);
	inputText.setFillColor(sf::Color::Red);
	inputText.setPosition(325, 225);
	//midtext(inputText, window);


	success.setFont(font);
	success.setCharacterSize(24);
	success.setFillColor(sf::Color::Red);
	success.setPosition(225, 275);
	success.setString("Success!");
	midtext(success, window);


	cue.setFont(font);
	cue.setCharacterSize(24);
	cue.setFillColor(sf::Color::Red);
	//cue.setPosition(325, 280);
	cue.setString("Who is your father");//提示文本的构建
	midtext(cue, window);


	fail.setFont(font);
	fail.setCharacterSize(24);
	fail.setFillColor(sf::Color::Red);
	//fail.setPosition(305, 239);
	fail.setString("wrong mibao");
	midtext(fail, window);
	std::string inputString = "";
	bool flag = 0;
	while (window.isOpen()) {
		sf::Event event;
		window.clear(sf::Color::Transparent);
		window.draw(sprite);
		colorful(cue, window);
		//window.draw(cue);
		window.draw(inputRec);
		window.draw(inputText);
		button[2].Draw(window);
		button[3].Draw(window);
		button[4].Draw(window);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) { // 只处理ASCII字符
					char c = static_cast<char>(event.text.unicode);
					if (c == '\b') { // 处理退格键
						if (inputString.length() > 0)
							inputString.erase(inputString.length() - 1);
					}
					else if (c != 13) { //13是回车键的ascii
						inputString += c;
					}
					inputText.setString(inputString);//将输入的字符串加载到Text中以展示在屏幕上
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				//判断左键点击
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (button[2].if_contain(MousePos)) {
						//cout << inputString << endl;
						if (user.getmibao()==inputString) {//按下confirm，检查用户注册情况
							
							window.clear(sf::Color::Transparent);
							window.draw(sprite);
							window.draw(success);
							window.display();
							Sleep(3000);
							inputString = "";
							inputText.setString(inputString);
							flag = 1;
							break;
						}
						else {
							window.clear(sf::Color::Transparent);//未注册，重新输入
							window.draw(sprite);
							//colorful(fail, window);
							window.draw(fail);
							window.display();
							Sleep(1500);
							inputString = "";
							inputText.setString(inputString);
						}
					}
					else if (button[3].if_contain(MousePos)) {
						return;
					}
				}

			}
		}
		if (flag) break;
	}

	cue.setString("Please enter new password");
	midtext(cue, window);

	while (window.isOpen()) {
		sf::Event event;
		window.clear(sf::Color::Transparent);
		window.draw(sprite);
		colorful(cue, window);
		//window.draw(cue);
		window.draw(inputRec);
		window.draw(inputText);
		button[2].Draw(window);
		button[3].Draw(window);
		button[4].Draw(window);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) { // 只处理ASCII字符
					char c = static_cast<char>(event.text.unicode);
					if (c == '\b') { // 处理退格键
						if (inputString.length() > 0)
							inputString.erase(inputString.length() - 1);
					}
					else if (c != 13) { //13是回车键的ascii
						inputString += c;
					}
					inputText.setString(inputString);//将输入的字符串加载到Text中以展示在屏幕上
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				//判断左键点击
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (button[2].if_contain(MousePos)) {
						modifypassword(user.getName(), inputString);
						window.clear(sf::Color::Transparent);
						window.draw(sprite);
						window.draw(success);
						window.display();
						Sleep(1000);
						return;
					}
					else if (button[3].if_contain(MousePos)) {
						return;
					}
				}

			}
		}
	}
}
player loginUser(const std::string& filename,sf::RenderWindow &window) {
	player target;
	sf::Sprite sprite(image);
	scaleX = (float)screenSize.x / imageSize.x;
	scaleY = (float)screenSize.y / imageSize.y;
	imageSize = image.getSize();
	sprite.setScale(scaleX, scaleY);//使背景图片能够全屏显示

	sf::Text inputText, success, cue, fail;
	inputText.setFont(font);
	inputText.setCharacterSize(24);
	inputText.setFillColor(sf::Color::Red);
	inputText.setPosition(325, 225);
	//midtext(inputText, window);


	success.setFont(font);
	success.setCharacterSize(24);
	success.setFillColor(sf::Color::Red);
	success.setPosition(325, 275);
	success.setString("Success!");
	midtext(success, window);


	cue.setFont(font);
	cue.setCharacterSize(24);
	cue.setFillColor(sf::Color::Red);
	//cue.setPosition(325, 280);
	cue.setString("Please input username");//提示文本的构建
	midtext(cue, window);


	fail.setFont(font);
	fail.setCharacterSize(24);
	fail.setFillColor(sf::Color::Red);
	//fail.setPosition(305, 239);
	fail.setString("Username Doesn't exist");
	midtext(fail, window);
	std::string inputString = "";
	bool flag = 0;
	string username;
	while (window.isOpen()) {
		sf::Event event;
		window.clear(sf::Color::Transparent);
		window.draw(sprite);
		colorful(cue, window);
		//window.draw(cue);
		window.draw(inputRec);
		window.draw(inputText);
		button[2].Draw(window);
		button[3].Draw(window);
		button[4].Draw(window);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) { // 只处理ASCII字符
					char c = static_cast<char>(event.text.unicode);
					if (c == '\b') { // 处理退格键
						if (inputString.length() > 0)
							inputString.erase(inputString.length() - 1);
					}
					else if (c != 13) { //13是回车键的ascii
						inputString += c;
					}
					inputText.setString(inputString);//将输入的字符串加载到Text中以展示在屏幕上
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				//判断左键点击
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (button[2].if_contain(MousePos)) {
						target = check(inputString);
						if (target.getName()!="") {//按下confirm，检查用户注册情况
				
							window.clear(sf::Color::Transparent);
							window.draw(sprite);
							//colorful(success, window);
							window.draw(success);
							window.display();
							Sleep(1500);
							inputString = "";
							inputText.setString(inputString);
							flag = 1;
							break;
						}
						else {
							window.clear(sf::Color::Transparent);//未注册，重新输入
							window.draw(sprite);
							//colorful(fail, window);
							window.draw(fail);
							window.display();
							Sleep(1500);
							inputString = "";
							inputText.setString(inputString);
						}
					}
					else if (button[3].if_contain(MousePos)) {
						return player();
					}
				}

			}
		}
		if (flag) break;
	}

	cue.setString("Please enter password");
	fail.setString("Password Wrong");
	fail.setPosition(300, 239);
	midtext(cue, window);
	midtext(fail, window);


	inputString = "";
	while (window.isOpen()) {//登录输入密码
		sf::Event event;
		window.clear(sf::Color::Transparent);
		window.draw(sprite);
		colorful(cue, window);
		//window.draw(cue);
		window.draw(inputRec);
		window.draw(inputText);
		button[3].Draw(window);
		button[4].Draw(window);
		button[5].Draw(window);
		button[6].Draw(window);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) { // 只处理ASCII字符
					char c = static_cast<char>(event.text.unicode);
					if (c == '\b') { // 处理退格键
						if (inputString.length() > 0)
							inputString.erase(inputString.length() - 1);
					}
					else if (c != 13) { //13是回车键的ascii
						inputString += c;
					}
					inputText.setString(inputString);//将输入的字符串加载到Text中以展示在屏幕上
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				//判断左键点击
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (button[5].if_contain(MousePos)) {
						if (target.getpassword()==inputString) {//按下confirm，检查用户注册情况
							window.clear(sf::Color::Transparent);
							window.draw(sprite);
							//colorful(success, window);
							window.draw(success);
							window.display();
							Sleep(1500);
							return target;
						}
						else {
							window.clear(sf::Color::Transparent);//未注册，重新输入
							window.draw(sprite);
							//colorful(fail, window);
							window.draw(fail);
							window.display();
							Sleep(1500);
							inputString = "";
							inputText.setString(inputString);
						}
					}
					else if (button[3].if_contain(MousePos)) {
						return player();
					}
					else if (button[6].if_contain(MousePos)) {
						findUser(window, target);
						target = check(target.getName());
					}
				}

			}
		}
	}
	return player();
}

player registermain() {
	
	sf::RenderWindow window(sf::VideoMode(802, 602), "register/login");

	Welcome.setFont(font_youyuan);
	Welcome.setString("WELCOME!");
	Welcome.setPosition(261, 30);
	Welcome.setCharacterSize(60);
	Welcome.setFillColor(sf::Color::Red);

	
	rec.setPosition(0,0);
	rec.setSize(sf::Vector2f(802,150));

	inputRec.setPosition(325, 225);
	inputRec.setFillColor(sf::Color::White);
	inputRec.setSize(sf::Vector2f(150, 25));//输入白框的实现
	//rec.setFillColor(sf::Color::White);

	sf::Texture ttexture;//利用纹理生成纹理坐标来进行着色器的渐变计算，必须这样做，否则只会出现leftcolor的颜色！！！
	ttexture.create(1, 1);  // 创建一个 1x1 像素的空白纹理
	rec.setTexture(&ttexture);  // 给矩形绑定纹理，此时会自动生成纹理坐标

	
	shader = loadColor(leftColor,rightColor);//头顶一片渐变色的实现




	font.loadFromFile("arial.ttf");//字体
	font_youyuan.loadFromFile("arial.ttf");//幼圆字体
	font_bri.loadFromFile("arial.ttf");//BRI字体
	

	sf::Texture texture_close, texture_logo, texture_gonggao, texture12, texture_login,texture_register,texture_confirm,texture_find;
	if (!texture_close.loadFromFile("close.png")) {
		return player();
	}
	if (!texture_logo.loadFromFile("wudataiqiu.png")) {
		return player();
	}
	if (!texture_gonggao.loadFromFile("gonggao.png")) {
		return player();
	}
	if (!texture12.loadFromFile("12plus.png")) {
		return player();
	}
	if (!texture_login.loadFromFile("login.png")) {
		return player();
	}
	if (!texture_register.loadFromFile("register.bmp")) {
		return player();
	}
	if (!texture_confirm.loadFromFile("confirm.png")) {
		return player();
	}
	if (!texture_find.loadFromFile("findpassword.bmp")) {
		return player();
	}
	/*for (int i = 0; i < 2; i++) {
		sf::Vector2f position(ButtonStartX-100 + i * (ButtonWidth * 2 + ButtonSpace), ButtonStartY);
		button.emplace_back("", font_bri, position, sf::Vector2f(ButtonWidth, ButtonHeight));
	}*/
	
	button.emplace_back("", font_bri, sf::Vector2f(330,400), sf::Vector2f(ButtonWidth, ButtonHeight));
	button[0].changeColor(texture_register);
	button.emplace_back("", font_bri, sf::Vector2f(250, 250), sf::Vector2f(ButtonWidth*2, ButtonHeight*2.5));
	button[1].changeColor(texture_login);
	sf::Vector2f position(ButtonStartX + 1 * (ButtonWidth * 0.33 + ButtonSpace), ButtonStartY + 200);
	button.emplace_back("", font_bri, position, sf::Vector2f(ButtonWidth, ButtonHeight));//定义三个按钮
	button[2].changeColor(texture_confirm);



	position=sf::Vector2f(700,550);
	button.emplace_back("", font_bri, position, sf::Vector2f(ButtonWidth / 2.15, ButtonHeight));//关闭键
	button[3].changeColor(texture_close);

	position = sf::Vector2f(0, 520);
	button.emplace_back("", font_bri, position, sf::Vector2f(ButtonWidth*1.5 , ButtonHeight*1.5));//logo
	button[4].changeColor(texture_logo);

	position = sf::Vector2f(170, 440);
	button.emplace_back("", font_bri, position, sf::Vector2f(ButtonWidth, ButtonHeight));//搭配找回密码的confirm
	button[5].changeColor(texture_confirm);

	position = sf::Vector2f(470, 440);
	button.emplace_back("", font_bri, position, sf::Vector2f(ButtonWidth, ButtonHeight));//找回密码
	button[6].changeColor(texture_find);

	position = sf::Vector2f(130, 450);
	button.emplace_back("", font_bri, position, sf::Vector2f(ButtonWidth*4, ButtonHeight*3.5));//gongao
	button[7].changeColor(texture_gonggao);
	
	position = sf::Vector2f(640, 10);
	button.emplace_back("", font_bri, position, sf::Vector2f(ButtonWidth , ButtonHeight*2.8 ));//12+
	button[8].changeColor(texture12);
	
	
	if (!image.loadFromFile("taiqiu.jpg")) {
		cout << "Error!Background not found" << endl;
		return player();
	}
	sf::Sprite sprite(image);
	imageSize = image.getSize();
	scaleX = (float)screenSize.x / imageSize.x;
	scaleY = (float)screenSize.y / imageSize.y;
	sprite.setScale(scaleX, scaleY);//加载背景图片


	
	while (window.isOpen()) {
		
		sf::Event event;
		window.clear(sf::Color::Transparent);

		window.draw(sprite);
		if (shader) {
			window.draw(rec, shader.get());
		}
		window.draw(Welcome);

		button[0].Draw(window);
		button[1].Draw(window);
		button[3].Draw(window);
		button[4].Draw(window);
		button[7].Draw(window);
		button[8].Draw(window);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				//判断左键点击
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					//遍历按键，判断点击的是那个按键
					for (const auto& entry : button) {
						if (entry.if_contain(MousePos)) {
							if (&entry - &button[0] == 0) {//按下register
								registerUser(filename,window);
							}
							else if(&entry-&button[0]==1) { //按下login
								ret=loginUser(filename,window);
								return ret;
							}
							else if(&entry-&button[0]==3){//按下关闭键
								return player();
							}
						}
					}
				}

			}
		}
	}
	return player();
}
void registerUser(const string& filename,sf::RenderWindow &window) {
	
	sqlite3* db;
	int rc = sqlite3_open("player.db", &db);
	if (rc != SQLITE_OK) {
		// 处理打开数据库错误
		cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return ;
	}

	sf::Sprite sprite(image);
	sf::Vector2u imageSize = image.getSize();
	float scaleX = (float)screenSize.x / imageSize.x;
	float scaleY = (float)screenSize.y / imageSize.y;
	sprite.setScale(scaleX, scaleY);//设置背景大小


	sf::Text inputText, success, cue;
	inputText.setFont(font);
	inputText.setCharacterSize(24);
	inputText.setFillColor(sf::Color::Red);
	inputText.setPosition(325, 225);


	success.setFont(font);
	success.setCharacterSize(24);
	success.setFillColor(sf::Color::Red);
	success.setPosition(325, 275);
	success.setString("Success!");
	midtext(success, window);


	cue.setFont(font);
	cue.setCharacterSize(24);
	cue.setFillColor(sf::Color::Red);
	cue.setPosition(275, 280);
	cue.setString("Please input username");//提示文本的构建
	midtext(cue, window);


	std::string inputString = "";
	ofstream file(filename, ios::app);
	if (!file.is_open()) {
		cout << "Error!" << endl;
		return;
	}

	bool flag = 0;
	string Username, Password,Mibao;
	while (window.isOpen()) {//注册用户名
		sf::Event event;
		window.draw(sprite);
		/*if (shader) {
			window.draw(rec, shader.get());
		}*/
		colorful(cue, window);
		//window.draw(cue);
		window.draw(inputRec);
		window.draw(inputText);
		//window.draw(Welcome);
		button[2].Draw(window);
		button[3].Draw(window);
		button[4].Draw(window);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) { // 只处理ASCII字符
					char c = static_cast<char>(event.text.unicode);
					if (c == '\b') { // 处理退格键
						if (inputString.length() > 0)
							inputString.erase(inputString.length() - 1);
					}
					else if (c != 13) {
						inputString += c;
					}
					inputText.setString(inputString);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				//判断左键点击
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (button[2].if_contain(MousePos)) {
						window.clear(sf::Color::Transparent);//回车键输入完毕
						window.draw(sprite);
						//colorful(success, window);
						window.draw(success);
						window.display();
						file << inputString << " ";
						Username = inputString;
						inputString = "";
						inputText.setString(inputString);
						Sleep(1000);
						flag = 1;
						break;
					}
					else if (button[3].if_contain(MousePos)) {
						return ;
					}
				}

			}
		}
		if (flag) break;
	}

	
	cue.setString("Please enter password");
	midtext(cue, window);
	flag = 0;

	while (window.isOpen()) {//输入密码
		sf::Event event;
		window.draw(sprite);
		colorful(cue, window);
		//window.draw(cue);
		window.draw(inputRec);
		window.draw(inputText);
		button[2].Draw(window);
		button[3].Draw(window);
		button[4].Draw(window);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) { // 只处理ASCII字符
					char c = static_cast<char>(event.text.unicode);
					if (c == '\b') { // 处理退格键
						if (inputString.length() > 0)
							inputString.erase(inputString.length() - 1);
					}
					else if (c != 13) {
						inputString += c;
					}
					inputText.setString(inputString);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				//判断左键点击
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (button[2].if_contain(MousePos)) {
						window.clear(sf::Color::Transparent);//回车键输入完毕
						window.draw(sprite);
						//colorful(success, window);
						window.draw(success);
						window.display();
						file << inputString<<" " ;
						Password = inputString;
						inputString = "";
						inputText.setString(inputString);
						Sleep(1000);
						flag = 1;
						break;
					}
					else if (button[3].if_contain(MousePos)) {
						return ;
					}
				}

			}
		}
		if (flag) break;
	}


	cue.setString("Who is your father?");
	midtext(cue, window);

	flag = 0;
	while (window.isOpen()) {//输入mibao
		//cout << "d";
		sf::Event event;
		window.draw(sprite);
		colorful(cue, window);
		//window.draw(cue);
		window.draw(inputRec);
		window.draw(inputText);
		button[2].Draw(window);
		button[3].Draw(window);
		button[4].Draw(window);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) { // 只处理ASCII字符
					char c = static_cast<char>(event.text.unicode);
					if (c == '\b') { // 处理退格键
						if (inputString.length() > 0)
							inputString.erase(inputString.length() - 1);
					}
					else if (c != 13) {
						inputString += c;
					}
					inputText.setString(inputString);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				//判断左键点击
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (button[2].if_contain(MousePos)) {
						window.clear(sf::Color::Transparent);//回车键输入完毕
						window.draw(sprite);
						//colorful(success, window);
						window.draw(success);
						window.display();
						file << inputString << " 0 0" << endl;
						Mibao = inputString;
						inputString = "";
						inputText.setString(inputString);
						Sleep(1000);
						flag = 1;
						break;
					}
					else if (button[3].if_contain(MousePos)) {
						return;
					}
				}

			}
		}
		if (flag) break;
	}
	string query = "INSERT INTO player (username, userpassword, usermibao, coins, points) VALUES ('" + Username + "', '" + Password + "', '" + Mibao + "', 0, 0)";
	char* errMsg = nullptr;//定义了一个字符指针errMsg并初始化为nullptr，它将用于接收执行 SQL 语句过程中出现的错误信息。
	rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);//通过c_str()函数获取query字符串的 C 风格字符串表示形式,第三个参数nullptr，在这里表示不需要回调函数来处理查询结果
	//cout << "d";
	if (rc != SQLITE_OK) {
		// 处理插入错误
		cerr << "SQL error: " << errMsg << endl;
		sqlite3_free(errMsg);
	}

	//query = "SELECT * FROM player";
	//rc = sqlite3_exec(db, query.c_str(), callback, nullptr, &errMsg);
	//if (rc != SQLITE_OK) {
	//	// 处理查询执行错误
	//	std::cerr << "SQL error: " << errMsg << std::endl;
	//	sqlite3_free(errMsg);
	//}
	sqlite3_close(db);
}
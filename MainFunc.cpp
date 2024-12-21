#include"gButton.h"
#include"interface.h"
#include"bacisFunction.h"
#include"gGame.h"
#include"fmain.h"
#include"player.h"
extern int watchtimes;
void AVatar(ScreenState& state, sf::RenderWindow& window, player& temp)
{
	sf::Font font;
	if (!font.loadFromFile("BASKVILL.ttf"))
	{
		return;
	}

	//加载退出键
	gButton BackButton = Back_Button(window);
	//设置主页按键
	gButton HomeButton = Home_Button(window);
	// 使矩形透明，仅用于表示区域
	BackButton.m_Rect.setFillColor(sf::Color::Transparent);
	HomeButton.m_Rect.setFillColor(sf::Color::Transparent);

	while (window.isOpen() && state == ScreenState::Avatar)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			Window_Close(window, event);
			Window_Back(window, event, state, BackButton, HomeButton, ScreenState::MainScreen);
		}
		fshow(window, temp);
		state = ScreenState::MainScreen;
		window.clear();
		BackButton.Draw(window);
		HomeButton.Draw(window);
		window.display();
	}
}
int gzjmain(player& temp){
	int Switch_Flag = 1;
	int Acquiesce_Flag = 0;
	int ModeChoice = 0;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Billiards Game");

	ScreenState state = ScreenState::MainScreen;

	Icon(window);

	//sf::Music和SF::Sound不同，前者在对象消亡时才会关闭
	sf::Music sound;
	string MusicPath = "Song0.wav";
	string Temp_Path = MusicPath;
	playMusic(sound, MusicPath);

	float volume = 0.7f;

	MainShow(state, window, temp);

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (MusicPath != Temp_Path)
		{
			playMusic(sound, MusicPath);
			Temp_Path = MusicPath;
		}
		switch (state)
		{
		case ScreenState::MainScreen:
			//cout << temp.getCoins() << " ";
			MainShow(state, window,temp);
			//cout << temp.getCoins() << endl;
			break;
		case ScreenState::Avatar:
			AVatar(state, window,temp);
			break;
		case ScreenState::Mode:
			gMode(state, window, ModeChoice);
			break;
		case ScreenState::Ranking:
			Ranking(state, window);
			break;
		case ScreenState::Viewing:
			Viewing(state, window,sound);
			break;
		case ScreenState::Settings:
			Settings(state, window,sound,Switch_Flag, MusicPath,volume, Acquiesce_Flag);
			break;
		case ScreenState::Mall:
			Mall(state, window,temp);
			break;
		case ScreenState::Game:
			Game(state, window, ModeChoice);
			break;
		case ScreenState::Full:
			FullViewing(state, window,sound);
			break;
		case ScreenState::Fame:
			FameViewing(state, window,sound);
			break;
		case ScreenState::Task:
			Task(state, window, temp,watchtimes);
			break;
		}
	}
	return 0;
}
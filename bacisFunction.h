#pragma once
#ifndef BASICFUNCTION_H
#define BASICFUNCTION_H
#include"gButton.h"
#include"Interface.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>

//游戏图标
void Icon(sf::RenderWindow& window);

//音乐播放
void playMusic(sf::Music& music, string MusicPath);

//返回按键
gButton Back_Button(sf::RenderWindow& window);

//主页按键
gButton Home_Button(sf::RenderWindow& window);

//关闭界面
void Window_Close(sf::RenderWindow& window, sf::Event& event);

//返回
void Window_Back(sf::RenderWindow& window, sf::Event& event, ScreenState& state, gButton& BackButton, gButton& HomeButton, ScreenState NewState);

//悬浮放大
void Suspention(sf::RenderWindow& window, gButton* button);

//视频播放
void VideoPlay(sf::RenderWindow& window, ScreenState state, string& path,int flag, sf::Music& sound);
#endif
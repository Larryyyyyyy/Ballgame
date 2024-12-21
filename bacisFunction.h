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

//��Ϸͼ��
void Icon(sf::RenderWindow& window);

//���ֲ���
void playMusic(sf::Music& music, string MusicPath);

//���ذ���
gButton Back_Button(sf::RenderWindow& window);

//��ҳ����
gButton Home_Button(sf::RenderWindow& window);

//�رս���
void Window_Close(sf::RenderWindow& window, sf::Event& event);

//����
void Window_Back(sf::RenderWindow& window, sf::Event& event, ScreenState& state, gButton& BackButton, gButton& HomeButton, ScreenState NewState);

//�����Ŵ�
void Suspention(sf::RenderWindow& window, gButton* button);

//��Ƶ����
void VideoPlay(sf::RenderWindow& window, ScreenState state, string& path,int flag, sf::Music& sound);
#endif
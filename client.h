#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
struct Ball {
	CircleShape shape;
	Vector2f velocity; // 球的速度向量
	float angularVelocity; //角速度
};
class client {
public:
	client();
	void connectToServer(string ipAddress, int port);
	void sendMessage(float px, float py, bool leftClicked, bool playWay, bool isCuePressed, float magnitude, float angle, int version, vector<Ball> balls);
	void receiveMessage(float& px, float& py, bool& leftClicked, bool& playWay, bool& isCuePressed, float& magnitude, float& angle, int& version, vector<Ball>& balls);
private:
	TcpSocket socket;
	Packet packet;
};
#endif // !"CLIENT_H"
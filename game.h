#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>//for physics
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>//for debug
#include <functional>//for function
#include "client.h"
#include "text.h"
#include "button.h"
#include "slider.h"
#include "menu.h"
#include "textbox.h"
#include "avatar.h"
#include "level.h"
#include "button_.h"
#include "levelPage.h"
#include "store.h"
#include "ranking.h"
#define M_PI 3.1415926
using namespace std;
using namespace sf;
extern string ip;
extern int port,Track;
extern bool sente;
const float width = 780;
const float hole_radius = float(42.5) / float(1778) * width;//�򶴰뾶
const float wall_length = float(1699.5) / float(1778) * width;//����һ��ǽ�ĳ���
const float wall_width = float(1693) / float(1778) * width;//����һ��ǽ�ĳ���
const float wall_thick = float(86) / float(1778) * width;//ǽ��ȣ������Կ�һ���
const float len_width = float(3569) / float(1778) * width;//��׼��������
const float ball_radius = 23.47;//��׼��뾶
enum gameType { PVP, PVPOL };
enum gameMode { Snoke, China, Challenge };
enum gameTrack { Ranked, Casual }; //��֪����ʲô�������ˣ���gameTrack��¼������/��λ��
class game {
public://�������.cpp
    game(gameType Type_, gameMode Mode_, gameTrack Track_, const int& challengeIndex_);
    ~game();
    //��ʼ����
    void initial();
    void initialControls();
    void initialBalls_Snoke();
    void initialBalls_China();
    void initialBalls_Challenge();
    void initialInfoBox();
    void initialButton();
    void initialSlider();
    //�˶���
    void handleMove();
    void showScore(int s1, int s2);
    void updateInfoBox();
    Ball createBall(float x, float y, Color color);
    bool checkCollision(Ball& b1, Ball& b2);
    void handleCollision(Ball& ball1, Ball& ball2);
    bool checkCollision_wall(const CircleShape& ball, const FloatRect& rect);
    Vector2f calculateNormal(const CircleShape& ball, const FloatRect& rect);
    void updateBalls(vector<Ball>& balls, Sprite s[]);
    void ballinHole();
    void ballBack();
    float distance(float x, float y,float z,float w);
    float distance(Vector2f p1, Vector2f p2);
    float calculateAngle(const sf::Vector2f& ballPosition, const sf::Vector2f& mousePosition);
    //��˺���׼����
    void createStick();
    void updateCuePosition(Sprite& cueSprite, const Vector2f& ballPos, const Vector2f& mousePos);
    void updateCuePosition2(Sprite& cueSprite, Vector2f& ballPos, Vector2f& mousePos);
    void updateAimingLines(Vector2f ballPos, Vector2f mousePos);
    //����
    void placeCueball(const Vector2f& mousePosition);
    void stateAnnouncement();
    void drawAll();
    void ballsBackup();
    void ballsGetbackup(int nowVersion);
    void handleButton(const Event& event, const RenderWindow& window, function<void()> onClick);
    void handleSlider(const Event& event, const RenderWindow& window, function<void()> onClick);

    //********
    void drawSettlement();
    void checkOutcome();
    int getChallengeIndex() { return challengeIndex; }

private:
    //0-14:���� 15:���� 16:���� 17:���� 18:���� 19:���� 20:���� 21:����
    vector<Ball> balls;//����
    vector<Ball> ballsRecord[1010];//���¼
    int version,totalversion;
    Ball cueBall,greenBall,brownBall,yellowBall,blueBall,pinkBall,blackBall;//����͸�����ɫ����
    Vector2f mousePosition;
    Vector2f cueBallposition, greenBallposition, brownBallposition, 
        yellowBallposition, blueBallposition, pinkBallposition, blackBallposition;
    RenderWindow window;//��������
    bool canShoot, isCuePressed, touched, hide;//���Ի������ڰ����(����)����������׼�����أ����뷿��ǰ�Ⱥ���
    bool placed, nowplay, hitBalltype, fangui, haveShoot, leftClicked, playWay;//������ã������֣���Ҫ����������ͣ����棬ȷ����������������ʽ
    int p1score, p2score;//˫������ �����������
    int red, color, redClear;//���򣬲����붴 for snoke
    int green, blue, greenClear, blueClear;//���������붴 for china
    int state;
    string message;//������Ϣ
    Texture wall[16],hole[16],background,cueTexture;//����������ͼ
    Sprite sprite[16], spriteBackground, cueSprite;//������ʾ��ͼ(������Ϊ���������ͼ�����������Ǹ�)
    CircleShape rhole[16];//���
    bool ballVisible[32];//�������ʧ
    Clock forceClock,waitClock;//���ʱ��,���򶯻�ʱ��
    float magnitude;//�������
    vector<VertexArray> aimingLines; // ��׼�ߺͷ����ߵļ���

    text info, scoreP1, scoreP2;
    button goLast, goNext, hitMethod1, hitMethod2, hitBall, stop;
    slider forMagnitude, forAngle;

    client player;

    int challengeIndex = 1, shots = 0, cntBall;
    bool hitBlack = 0;
};
#endif // !"GAME_H"
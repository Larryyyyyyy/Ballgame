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
const float hole_radius = float(42.5) / float(1778) * width;//球洞半径
const float wall_length = float(1699.5) / float(1778) * width;//上下一个墙的长度
const float wall_width = float(1693) / float(1778) * width;//左右一个墙的长度
const float wall_thick = float(86) / float(1778) * width;//墙厚度，比球洞稍宽一点点
const float len_width = float(3569) / float(1778) * width;//标准球桌长度
const float ball_radius = 23.47;//标准球半径
enum gameType { PVP, PVPOL };
enum gameMode { Snoke, China, Challenge };
enum gameTrack { Ranked, Casual }; //不知道用什么变量名了，用gameTrack记录休闲赛/排位赛
class game {
public://功能详见.cpp
    game(gameType Type_, gameMode Mode_, gameTrack Track_, const int& challengeIndex_);
    ~game();
    //初始化区
    void initial();
    void initialControls();
    void initialBalls_Snoke();
    void initialBalls_China();
    void initialBalls_Challenge();
    void initialInfoBox();
    void initialButton();
    void initialSlider();
    //运动区
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
    //球杆和瞄准线区
    void createStick();
    void updateCuePosition(Sprite& cueSprite, const Vector2f& ballPos, const Vector2f& mousePos);
    void updateCuePosition2(Sprite& cueSprite, Vector2f& ballPos, Vector2f& mousePos);
    void updateAimingLines(Vector2f ballPos, Vector2f mousePos);
    //其它
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
    //0-14:红球 15:白球 16:绿球 17:棕球 18:黄球 19:蓝球 20:粉球 21:黑球
    vector<Ball> balls;//球们
    vector<Ball> ballsRecord[1010];//球记录
    int version,totalversion;
    Ball cueBall,greenBall,brownBall,yellowBall,blueBall,pinkBall,blackBall;//白球和各种颜色的球
    Vector2f mousePosition;
    Vector2f cueBallposition, greenBallposition, brownBallposition, 
        yellowBallposition, blueBallposition, pinkBallposition, blackBallposition;
    RenderWindow window;//创建窗口
    bool canShoot, isCuePressed, touched, hide;//可以击球，正在按左键(蓄力)，杆碰球，瞄准线隐藏，进入房间前先后手
    bool placed, nowplay, hitBalltype, fangui, haveShoot, leftClicked, playWay;//白球放置，现在手，需要击打球的类型，犯规，确定射击，左键，击球方式
    int p1score, p2score;//双方分数 红球进袋数量
    int red, color, redClear;//红球，彩球入洞 for snoke
    int green, blue, greenClear, blueClear;//绿球，蓝球入洞 for china
    int state;
    string message;//进球信息
    Texture wall[16],hole[16],background,cueTexture;//用来加载贴图
    Sprite sprite[16], spriteBackground, cueSprite;//用来显示贴图(可以认为这个代表贴图而不是上面那个)
    CircleShape rhole[16];//球袋
    bool ballVisible[32];//球进袋消失
    Clock forceClock,waitClock;//点击时间,击打动画时间
    float magnitude;//打击力度
    vector<VertexArray> aimingLines; // 瞄准线和反弹线的集合

    text info, scoreP1, scoreP2;
    button goLast, goNext, hitMethod1, hitMethod2, hitBall, stop;
    slider forMagnitude, forAngle;

    client player;

    int challengeIndex = 1, shots = 0, cntBall;
    bool hitBlack = 0;
};
#endif // !"GAME_H"
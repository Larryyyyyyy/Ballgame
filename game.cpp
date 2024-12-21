#include "game.h"
game::game(gameType Type_, gameMode Mode_, gameTrack Track_, const int& challengeIndex_):window(VideoMode(2180*scale, 1800*scale), "Table_Tennis_PVP") {

    window.setFramerateLimit(60);//����֡��
    
    Type = Type_;
    Mode = Mode_;
    Track = Track_;
    challengeIndex = challengeIndex_;
    initial();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            //�ⲿ��go���ɲ˵���������
            if (event.type == Event::Closed || go==3)
                window.close();
        }
        if (go == 2)initial();
        go = 0;
        mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));//���λ��
        leftClicked = Mouse::isButtonPressed(Mouse::Left);//����������
        handleButton(event, window, []() {
            });
        handleSlider(event, window, []() {
            });
        if (!(nowplay^sente)) {
            if (!hitBalltype)state = 0;
            else state = 1;
            player.sendMessage(mousePosition.x, mousePosition.y, leftClicked, playWay, isCuePressed, forMagnitude.currentValue, forAngle.currentValue, version, balls);//������Ϣ
        }
        else {
            if (!hitBalltype)state = 2;
            else state = 3;

            player.receiveMessage(mousePosition.x, mousePosition.y, leftClicked, playWay, isCuePressed, forMagnitude.currentValue, forAngle.currentValue, version, balls);//������Ϣ
        }
        if (canShoot && !placed) {
            placeCueball(mousePosition);//���ð���
        }
        if (version == totalversion)handleMove();
        // �������λ�ú���ײ
        updateBalls(balls, sprite);
        ballinHole();
        if (message != "") {
            if (!(nowplay^sente))state = 6;
            else state = 7;
        }
        drawAll();

        //***********
        checkOutcome();
    }
}
game::~game(){}

void game::initial() {
    if(Type==PVPOL)player.connectToServer(ip, port);//����һ�����Ӿ�����ip�Ͷ˿ڵĴ���
    canShoot = 1, isCuePressed = 0, touched = 0, hide = 0, placed = 0, state = 0,
    nowplay = 0, hitBalltype = 0, p1score = 0, p2score = 0, fangui = 0, haveShoot = 0, leftClicked = 0,
    redClear = 0, red = 0, color = 0, green = 0, greenClear = 0, blue = 0, blueClear = 0, version = 0, totalversion = 0, playWay = 0;
    message = "";
    balls.clear();
    ballsRecord->clear();
    initialControls();//���ÿؼ�
    if (Mode == Snoke)initialBalls_Snoke();//������(˹ŵ��)
    if (Mode == China)initialBalls_China();//������(�а�)
    if (Mode == Challenge)initialBalls_Challenge();//������(����)
    initialInfoBox();//�������ֿ�
    initialButton();
    initialSlider();
    ballsBackup();
}
//��ʼ���ؼ�
void game::initialControls() {
    createStick();//�������
    background.loadFromFile("resources/background.png");//���ر���
    spriteBackground.setTexture(background);//��ʾ��������ͬ��
    spriteBackground.setScale(2.54 * scale, 2.54 * scale);//�Ŵ���
    spriteBackground.setPosition(50.f * scale, 150.f * scale);//��ͼ���Ͻǵ�λ��
    /*      wall1              wall2
       #############    ##############
       #                             #
       #                             #  wall3
 wall6 #                             #
       #                             #
       #############    ##############
         wall5                 wall4
    */
    //ǽ��
    wall[1].loadFromFile("resources/wall1.jpg");
    sprite[1].setTexture(wall[1]);
    sprite[1].setPosition(158.f * scale, 150.f * scale);
    sprite[1].setScale(scale, scale);
    wall[2].loadFromFile("resources/wall2.jpg");
    sprite[2].setTexture(wall[2]);
    sprite[2].setPosition(1127.f * scale, 150.f * scale);
    sprite[2].setScale(scale, scale);
    wall[3].loadFromFile("resources/wall3.jpg");
    sprite[3].setTexture(wall[3]);
    sprite[3].setPosition(2030.f * scale, 255.f * scale);
    sprite[3].setScale(scale, scale);
    wall[4].loadFromFile("resources/wall4.jpg");
    sprite[4].setTexture(wall[4]);
    sprite[4].setPosition(1127.f * scale, 1227.f * scale);
    sprite[4].setScale(scale, scale);
    wall[5].loadFromFile("resources/wall5.jpg");
    sprite[5].setTexture(wall[5]);
    sprite[5].setPosition(156.f * scale, 1223.f * scale);
    sprite[5].setScale(scale, scale);
    wall[6].loadFromFile("resources/wall6.jpg");
    sprite[6].setTexture(wall[6]);
    sprite[6].setPosition(50.f * scale, 253.f * scale);
    sprite[6].setScale(scale, scale);
    //��ͼ��
    hole[1].loadFromFile("resources/hole1.jpg");
    sprite[7].setTexture(hole[1]);
    sprite[7].setPosition(50.f * scale, 150.f * scale);
    sprite[7].setScale(scale, scale);
    hole[2].loadFromFile("resources/hole2.jpg");
    sprite[8].setTexture(hole[2]);
    sprite[8].setPosition(1005.f * scale, 150.f * scale);
    sprite[8].setScale(scale, scale);
    hole[3].loadFromFile("resources/hole3.jpg");
    sprite[9].setTexture(hole[3]);
    sprite[9].setPosition(1965.f * scale, 150.f * scale);
    sprite[9].setScale(scale, scale);
    hole[4].loadFromFile("resources/hole4.jpg");
    sprite[10].setTexture(hole[4]);
    sprite[10].setPosition(1975.f * scale, 1150.f * scale);
    sprite[10].setScale(scale, scale);
    hole[5].loadFromFile("resources/hole5.jpg");
    sprite[11].setTexture(hole[5]);
    sprite[11].setPosition(1005.f * scale, 1195.f * scale);
    sprite[11].setScale(scale, scale);
    hole[6].loadFromFile("resources/hole6.jpg");
    sprite[12].setTexture(hole[6]);
    sprite[12].setPosition(50.f * scale, 1170.f * scale);
    sprite[12].setScale(scale, scale);
    //����
    rhole[1].setFillColor(Color::Black);
    rhole[1].setPosition(100 * scale, 205 * scale);
    rhole[1].setRadius(38 * scale);
    rhole[1].setOrigin(19 * scale, 19 * scale);
    rhole[1].setScale(scale, scale);
    rhole[2].setFillColor(Color::Black);
    rhole[2].setPosition(1049 * scale, 175 * scale);
    rhole[2].setRadius(38 * scale);
    rhole[2].setOrigin(19 * scale, 19 * scale);
    rhole[2].setScale(scale, scale);
    rhole[3].setFillColor(Color::Black);
    rhole[3].setPosition(1999 * scale, 195 * scale);
    rhole[3].setRadius(38 * scale);
    rhole[3].setOrigin(19 * scale, 19 * scale);
    rhole[3].setScale(scale, scale);
    rhole[4].setFillColor(Color::Black);
    rhole[4].setPosition(1999 * scale, 1181 * scale);
    rhole[4].setRadius(38 * scale);
    rhole[4].setOrigin(19 * scale, 19 * scale);
    rhole[4].setScale(scale, scale);
    rhole[5].setFillColor(Color::Black);
    rhole[5].setPosition(1049 * scale, 1211 * scale);
    rhole[5].setRadius(38 * scale);
    rhole[5].setOrigin(19 * scale, 19 * scale);
    rhole[5].setScale(scale, scale);
    rhole[6].setFillColor(Color::Black);
    rhole[6].setPosition(90 * scale, 1191 * scale);
    rhole[6].setRadius(38 * scale);
    rhole[6].setOrigin(19 * scale, 19 * scale);
    rhole[6].setScale(scale, scale);
}
//��ʼ����(˹ŵ��)
void game::initialBalls_Snoke() {
    //**********
    cntBall = 15;

    memset(ballVisible, 1, sizeof(ballVisible));
    Ball ball;
    ball = createBall(1520 * scale, 710 * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 2 * ball_radius + 2) * scale, (710 + ball_radius + 1) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 2 * ball_radius + 2) * scale, (710 - ball_radius - 1) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 4 * ball_radius + 4) * scale, (710 + 2 * ball_radius + 2) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 4 * ball_radius + 4) * scale, 710 * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 4 * ball_radius + 4) * scale, (710 - 2 * ball_radius - 2) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 + 3 * ball_radius + 3) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 + ball_radius + 1) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 - ball_radius - 1) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 - 3 * ball_radius - 3) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 + 4 * ball_radius + 4) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 + 2 * ball_radius + 2) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, 710 * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 - 2 * ball_radius - 2) * scale, Color::Red);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 - 4 * ball_radius- 4) * scale, Color::Red);
    balls.push_back(ball);
    cueBall = createBall(600 * scale, 300 * scale, Color::White);
    balls.push_back(cueBall);
    ballVisible[15] = 0;
    greenBall = createBall(525 * scale, 530 * scale, Color::Green);
    balls.push_back(greenBall);
    brownBall = createBall(525 * scale, 710 * scale, Color (139, 69, 19));
    balls.push_back(brownBall);
    yellowBall = createBall(525 * scale, 890 * scale, Color::Yellow);
    balls.push_back(yellowBall);
    blueBall = createBall(1070 * scale, 710 * scale, Color::Blue);
    balls.push_back(blueBall);
    pinkBall = createBall(1469.06 * scale, 710 * scale, Color(255, 192, 203));
    balls.push_back(pinkBall);
    blackBall = createBall(1820 * scale, 710 * scale, Color::Black);
    balls.push_back(blackBall);
}
//��ʼ����(�а�)
void game::initialBalls_China() {
    //************
    cntBall = 15;
    hitBlack = 0;

    memset(ballVisible, 1, sizeof(ballVisible));
    Ball ball;
    ball = createBall(1520 * scale, 710 * scale, Color::Green);
    balls.push_back(ball);
    ball = createBall((1520 + 2 * ball_radius + 2) * scale, (710 + ball_radius + 1) * scale, Color::Blue);
    balls.push_back(ball);
    ball = createBall((1520 + 2 * ball_radius + 2) * scale, (710 - ball_radius - 1) * scale, Color::Green);
    balls.push_back(ball);
    ball = createBall((1520 + 4 * ball_radius + 4) * scale, (710 + 2 * ball_radius + 2) * scale, Color::Blue);
    balls.push_back(ball);
    ball = createBall((1520 + 4 * ball_radius + 4) * scale, 710 * scale, Color::Black);
    balls.push_back(ball);
    ball = createBall((1520 + 4 * ball_radius + 4) * scale, (710 - 2 * ball_radius - 2) * scale, Color::Green);
    balls.push_back(ball);
    ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 + 3 * ball_radius + 3) * scale, Color::Blue);
    balls.push_back(ball);
    ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 + ball_radius + 1) * scale, Color::Green);
    balls.push_back(ball);
    ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 - ball_radius - 1) * scale, Color::Blue);
    balls.push_back(ball);
    ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 - 3 * ball_radius - 3) * scale, Color::Green);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 + 4 * ball_radius + 4) * scale, Color::Blue);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 + 2 * ball_radius + 2) * scale, Color::Green);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, 710 * scale, Color::Blue);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 - 2 * ball_radius - 2) * scale, Color::Green);
    balls.push_back(ball);
    ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 - 4 * ball_radius - 4) * scale, Color::Blue);
    balls.push_back(ball);
    cueBall = createBall(600 * scale, 300 * scale, Color::White);
    balls.push_back(cueBall);
    ballVisible[15] = 0;
}
//***********
//��ʼ����(��ս)
void game::initialBalls_Challenge() {//��������
    //challengeIndex = 5;

    memset(ballVisible, 1, sizeof(ballVisible));
    Ball ball;
    switch (challengeIndex) {
    case 1: { //ֻ��һ�������˴���
        shots = 3;
        cntBall = 1;
        ball = createBall(1520 * scale, 710 * scale, Color::Red);
        balls.push_back(ball);
        for (int i = 1; i <= 14; i++) {
            ball = createBall(100 * scale, 100 * scale, Color::Red);
            ballVisible[i] = 0;
            balls.push_back(ball);
        }
        cueBall = createBall(600 * scale, 300 * scale, Color::White);
        balls.push_back(cueBall);
        ballVisible[15] = 0;
        break;
    }
    case 2: { //����һ������
        shots = 30;
        cntBall = 15;
        ball = createBall(1258 * scale, 592 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1343 * scale, 516 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1455 * scale, 538 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1489 * scale, 633 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1456 * scale, 724 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1362 * scale, 809 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1298 * scale, 848 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1226 * scale, 875 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1194 * scale, 592 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1109 * scale, 516 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(997 * scale, 538 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(963 * scale, 633 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(996 * scale, 724 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1090 * scale, 809 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1154 * scale, 848 * scale, Color::Red);
        balls.push_back(ball);

        cueBall = createBall(600 * scale, 300 * scale, Color::White);
        balls.push_back(cueBall);
        ballVisible[15] = 0;
        break;
    }
    case 3: { //����һ��б��
        shots = 20;
        cntBall = 15;
        ball = createBall(600.00 * scale, 200.00 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(654.03 * scale, 254.03 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(708.06 * scale, 308.06 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(762.09 * scale, 362.09 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(816.12 * scale, 416.12 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(870.15 * scale, 470.15 * scale, Color::Yellow);
        balls.push_back(ball);
        ball = createBall(924.18 * scale, 524.18 * scale, Color::Yellow);
        balls.push_back(ball);
        ball = createBall(978.21 * scale, 578.21 * scale, Color::Yellow);
        balls.push_back(ball);
        ball = createBall(1032.24 * scale, 632.24 * scale, Color::Yellow);
        balls.push_back(ball);
        ball = createBall(1086.27 * scale, 686.27 * scale, Color::Yellow);
        balls.push_back(ball);
        ball = createBall(1140.30 * scale, 740.30 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1194.33 * scale, 794.33 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1248.36 * scale, 848.36 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1302.39 * scale, 902.39 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1356.42 * scale, 956.42 * scale, Color::Red);
        balls.push_back(ball);

        cueBall = createBall(600 * scale, 300 * scale, Color::White);
        balls.push_back(cueBall);
        ballVisible[15] = 0;
        break;
    }
    case 4: { //��������һ�˴���
        shots = 1;
        cntBall = 2;
        ball = createBall(1800 * scale, 350 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1700 * scale, 400 * scale, Color::Red);
        balls.push_back(ball);
        for (int i = 2; i <= 14; i++) {
            ball = createBall(100 * scale, 100 * scale, Color::Black);
            ballVisible[i] = 0;
            balls.push_back(ball);
        }
        cueBall = createBall(600 * scale, 300 * scale, Color::White);
        balls.push_back(cueBall);
        ballVisible[15] = 0;
        break;
    }
    case 5: { //����һ��èèͷ???
        shots = 45;
        cntBall = 32;
        ball = createBall(952 * scale, 604 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(956 * scale, 561 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(957 * scale, 513 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(986 * scale, 568 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1002 * scale, 608 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(954 * scale, 674 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(991 * scale, 675 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(821 * scale, 718 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(865 * scale, 739 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(914 * scale, 769 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(824 * scale, 793 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(867 * scale, 794 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(972 * scale, 802 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(851 * scale, 883 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(892 * scale, 860 * scale, Color::Red);
        balls.push_back(ball);
        cueBall = createBall(1800 * scale, 800 * scale, Color::White);
        balls.push_back(cueBall);
        ballVisible[15] = 0;
        ball = createBall(933 * scale, 827 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1252 * scale, 604 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1248 * scale, 561 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1247 * scale, 513 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1218 * scale, 568 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1202 * scale, 608 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1250 * scale, 674 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1213 * scale, 675 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1383 * scale, 718 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1339 * scale, 739 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1290 * scale, 769 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1380 * scale, 793 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1337 * scale, 794 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1232 * scale, 802 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1353 * scale, 883 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1312 * scale, 860 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall(1271 * scale, 827 * scale, Color::Red);
        balls.push_back(ball);


        break;
    }
    case 6: { //һ����̨
        shots = 1;
        cntBall = 1;
        ball = createBall(1520 * scale, 710 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 2 * ball_radius + 2) * scale, (710 + ball_radius + 1) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 2 * ball_radius + 2) * scale, (710 - ball_radius - 1) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 4 * ball_radius + 4) * scale, (710 + 2 * ball_radius + 2) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 4 * ball_radius + 4) * scale, 710 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 4 * ball_radius + 4) * scale, (710 - 2 * ball_radius - 2) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 + 3 * ball_radius + 3) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 + ball_radius + 1) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 - ball_radius - 1) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 6 * ball_radius + 6) * scale, (710 - 3 * ball_radius - 3) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 + 4 * ball_radius + 4) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 + 2 * ball_radius + 2) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 8 * ball_radius + 8) * scale, 710 * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 - 2 * ball_radius - 2) * scale, Color::Red);
        balls.push_back(ball);
        ball = createBall((1520 + 8 * ball_radius + 8) * scale, (710 - 4 * ball_radius - 4) * scale, Color::Red);
        balls.push_back(ball);
        cueBall = createBall(1800 * scale, 800 * scale, Color::White);
        balls.push_back(cueBall);
        ballVisible[15] = 0;
        break;
    }
    }
    challengeIndex = 0;
}
//��ʼ�����ֿ�
void game::initialInfoBox() {
    info.initializeInfoBox(10.f * scale, 10.f * scale, 1000.f * scale, 50.f * scale, scale, Color::White);
    scoreP1.initializeInfoBox(10.f * scale, 90.f * scale, 270.f * scale, 50.f * scale, scale, Color::White);
    scoreP2.initializeInfoBox(300.f * scale, 90.f * scale, 270.f * scale, 50.f * scale, scale, Color::White);
}
//��ʼ����ť
void game::initialButton() {
    goLast.initiallizeButton(100.f * scale, 1420.f * scale, 100.f * scale, 100.f * scale, "Last status", scale, Color(255, 255, 250), Color(150, 150, 250), Color(50, 50, 200));
    wall[7].loadFromFile("resources/leftarrow.png");
    goLast.shape.setTexture(&wall[7]);
    goNext.initiallizeButton(300.f * scale, 1420.f * scale, 100.f * scale, 100.f * scale, "Next status", scale, Color(255, 255, 250), Color(150, 150, 250), Color(50, 50, 200));
    wall[8].loadFromFile("resources/rightarrow.png");
    goNext.shape.setTexture(&wall[8]);
    hitMethod1.initiallizeButton(500.f * scale, 1370.f * scale, 200.f * scale, 200.f * scale, "Switch method", scale, Color(255, 255, 250), Color(150, 150, 250), Color(50, 50, 200));
    wall[9].loadFromFile("resources/mouse.png");
    hitMethod1.shape.setTexture(&wall[9]);
    hitMethod2.initiallizeButton(700.f * scale, 1420.f * scale, 200.f * scale, 100.f * scale, "Switch method", scale, Color(255, 255, 250), Color(150, 150, 250), Color(50, 50, 200));
    wall[10].loadFromFile("resources/slider.png");
    hitMethod2.shape.setTexture(&wall[10]);
    hitBall.initiallizeButton(2000.f * scale, 1420.f * scale, 100.f * scale, 100.f * scale, "Go hit", scale, Color(255, 255, 250), Color(150, 150, 250), Color(50, 50, 200));
    wall[11].loadFromFile("resources/hitball.png");
    hitBall.shape.setTexture(&wall[11]);
    wall[12].loadFromFile("resources/stop.png");
    stop.initiallizeButton(2050.f * scale, 40.f * scale, 100.f * scale, 100.f * scale, "Stop", scale, Color(255,255,255), Color(150, 150, 250), Color(50, 50, 200));
    stop.shape.setTexture(&wall[12]);
}
//��ʼ��������
void game::initialSlider() {
    forMagnitude.initializeslider(1000.f * scale, 1350.f * scale, 800.f * scale, 100.f * scale, 5.f, 30.f);
    forAngle.initializeslider(1000.f * scale, 1490.f * scale, 800.f * scale, 100.f * scale, 0, 360.f);
}
//��������߼�
void game::handleMove() {
    // �û�����(������)
    if (!playWay) {
        Vector2f ballPosition = balls[15].shape.getPosition();//����λ��
        if (canShoot && placed) {
            ballBack();
            if (haveShoot) {
                nowplay = !nowplay;
                haveShoot = false;
                ballsBackup();//��¼��ǰ״̬����
            }
            updateCuePosition(cueSprite, ballPosition, mousePosition);//���¸�
            updateAimingLines(ballPosition,mousePosition);//������׼��
        }
        if (placed && canShoot && leftClicked) {
            hide = 0;
            if (!isCuePressed) {
                isCuePressed = 1;
                forceClock.restart(); // ��ʼ�ۻ�����
            }
            magnitude = forceClock.getElapsedTime().asSeconds() * 5.0f;
            if (magnitude < 5.0f)magnitude = 0.f;
        }
        else if (isCuePressed && touched && placed) {
            isCuePressed = 0;
            touched = 0;
            Vector2f mousePos = mousePosition;
            Vector2f cueBallPos = balls[15].shape.getPosition();
            mousePos.x = 2 * cueBallPos.x - mousePos.x;
            mousePos.y = 2 * cueBallPos.y - mousePos.y;
            Vector2f direction = mousePos - cueBallPos;
            if (magnitude > 0.f) {
                haveShoot = 1;
                Vector2f normalizedDirection = direction / sqrt(direction.x * direction.x + direction.y * direction.y); // ��λ����������
                float speed = min(magnitude, 30.f); // �����������
                balls[15].velocity = normalizedDirection * speed; // �����ٶ�
                if (Mode == Challenge) shots--;
            }
            magnitude = 0.f;
        }
        else if (!touched) {
            waitClock.restart();
            updateCuePosition2(cueSprite, ballPosition, mousePosition);
        }
    }
    if (playWay) {
        Vector2f ballPosition = balls[15].shape.getPosition();//����λ��
        Vector2f pos = ballPosition;//Ӧ�õ�λ��
        pos.x += cos(forAngle.currentValue * M_PI / 180.f);
        pos.y += sin(forAngle.currentValue * M_PI / 180.f);
        if (canShoot && placed) {
            ballBack();
            if (haveShoot) {
                nowplay = !nowplay;
                haveShoot = false;
                ballsBackup();//��¼��ǰ״̬����
            }
            updateCuePosition(cueSprite, ballPosition, pos);//���¸�
            updateAimingLines(ballPosition,pos);//������׼��
        }
        if (placed && canShoot && !isCuePressed) {
            hide = 0;
            magnitude = forMagnitude.currentValue;
        }
        else if (isCuePressed && touched && placed) {
            isCuePressed = 0;
            touched = 0;
            Vector2f mousePos = pos;
            Vector2f cueBallPos = balls[15].shape.getPosition();
            mousePos.x = 2 * cueBallPos.x - mousePos.x;
            mousePos.y = 2 * cueBallPos.y - mousePos.y;
            Vector2f direction = mousePos - cueBallPos;
            if (magnitude > 0.f) {
                haveShoot = 1;
                Vector2f normalizedDirection = direction / sqrt(direction.x * direction.x + direction.y * direction.y); // ��λ����������
                float speed = min(magnitude, 30.f); // �����������
                balls[15].velocity = normalizedDirection * speed; // �����ٶ�
            }
            magnitude = 0.f;
        }
        else if (!touched) {
            waitClock.restart();
            updateCuePosition2(cueSprite, ballPosition, pos);
        }
    }
}
//��ʾ����
void game::showScore(int s1, int s2) {
    //***********
    if (Mode == Challenge) {
        scoreP1.infoText.setString("Remaining");
        scoreP2.infoText.setString("shots: " + std::to_string(s1));
        scoreP1.messageClock.restart();
        scoreP2.messageClock.restart();
        return;
    }
    string s = "", t = "";
    if (s1 >= 100)s += char(s1 / 100 + 48) + char(s1 / 10 % 10 + 48) + char(s1 % 10 + 48);
    if (s1 < 100 && s1 >= 10)s += char(s1 / 10 + 48) + char(s1 % 10 + 48);
    if (s1 < 10)s += char(s1 % 10 + 48);
    if (s2 >= 100)t += char(s2 / 100 + 48) + char(s2 / 10 % 10 + 48) + char(s2 % 10 + 48);
    if (s2 < 100 && s2 >= 10)t += char(s2 / 10 + 48) + char(s2 % 10 + 48);
    if (s2 < 10)t += char(s2 % 10 + 48);
    if (Mode == Snoke) {
        scoreP1.infoText.setString("P1 score: " + s);
        scoreP2.infoText.setString("P2 score: " + t);
    }
    if (Mode == China) {
        scoreP1.infoText.setString("P1 left: " + s);
        scoreP2.infoText.setString("P2 left: " + t);
    }
    scoreP1.messageClock.restart();
    scoreP2.messageClock.restart();
}
//�������ֿ�
void game::updateInfoBox() {
    if (info.messageClock.getElapsedTime().asSeconds() > info.messageDuration) {
        info.currentMessage.clear();
        info.infoText.setString("");//�������
    }
    if (scoreP1.messageClock.getElapsedTime().asSeconds() > scoreP1.messageDuration) {
        scoreP1.currentMessage.clear();
        scoreP1.infoText.setString("");//�������
    }
    if (scoreP2.messageClock.getElapsedTime().asSeconds() > scoreP2.messageDuration) {
        scoreP2.currentMessage.clear();
        scoreP2.infoText.setString("");//�������
    }
}
//������
Ball game::createBall(float x, float y, Color color) {
    Ball ball;
    ball.shape.setRadius(ball_radius * scale); // ��ʼ�뾶
    ball.shape.setOrigin(ball_radius * scale, ball_radius * scale); // Բ�Ķ���
    ball.shape.setPosition(x, y);
    ball.velocity = { 0.f, 0.f }; // ��ʼ��ֹ
    ball.angularVelocity = 2.0f; // ��ʼ���ٶ�
    ball.shape.setFillColor(color); // ���û�����ɫ
    return ball;
}
// ��ײ���(������)
bool game::checkCollision(Ball& b1, Ball& b2) {
    Vector2f delta = b1.shape.getPosition() - b2.shape.getPosition();
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
    return distance <= (b1.shape.getRadius() + b2.shape.getRadius());
}
//������ײ���������Ӿ���
void game::handleCollision(Ball& b1, Ball& b2) {
    Vector2f diff = b1.shape.getPosition() - b2.shape.getPosition();
    float distance = sqrt(diff.x * diff.x + diff.y * diff.y);
    float overlap = b1.shape.getRadius() + b2.shape.getRadius() - distance;
    if (overlap > 0.f) {
        Vector2f correction = diff / distance * (overlap / 2.f);
        b1.shape.setPosition(b1.shape.getPosition() + correction); // ���� ball1 ��λ��
        b2.shape.setPosition(b2.shape.getPosition() + correction); // ���� ball2 ��λ��
    }
    Vector2f normal = diff / distance;
    Vector2f relativeVelocity = b1.velocity - b2.velocity;
    float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;
    if (velocityAlongNormal < 0.f) {
        float restitution = 1.0f; // ��ȫ����
        float impulse = -(1 + restitution) * velocityAlongNormal;
        impulse /= 2;
        Vector2f impulseVector = impulse * normal;
        b1.velocity += impulseVector;
        b2.velocity -= impulseVector;
    }
}
// ��ײ���(����ǽ)
bool game::checkCollision_wall(const CircleShape& ball, const FloatRect& rect) {
    // ��ȡ���λ�úͰ뾶
    Vector2f ballPos = ball.getPosition();

    // ������εı߽�
    float left = rect.left;
    float right = rect.left + rect.width;
    float top = rect.top;
    float bottom = rect.top + rect.height;

    // ��;��ε�����λ��
    float nearestX = max(left, std::min(ballPos.x, right));
    float nearestY = max(top, std::min(ballPos.y, bottom));

    // �������������ĵľ����Ƿ�С����İ뾶
    float dis = distance(ballPos.x, nearestX, ballPos.y, nearestY);
    return dis < ball_radius;
}
//���㷨����
Vector2f game::calculateNormal(const CircleShape& ball, const FloatRect& rect) {
    Vector2f ballPos = ball.getPosition();
    float left = rect.left;
    float right = rect.left + rect.width;
    float top = rect.top;
    float bottom = rect.top + rect.height;

    float nearestX = std::max(left, std::min(ballPos.x, right));
    float nearestY = std::max(top, std::min(ballPos.y, bottom));

    Vector2f normal = ballPos - Vector2f(nearestX, nearestY);
    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    if (length == 0.f) {
        return Vector2f(0.f, 0.f);  // ��������������ʾû����Ч�ķ���
    }
    return normal / length;
}
//������
void game::updateBalls(vector<Ball>& balls, Sprite s[]) {
    FloatRect bounds;
    for (auto& ball : balls) {
        // ����λ��
        ball.shape.move(ball.velocity);
        //��ת
        ball.shape.rotate(ball.angularVelocity);
        for (int i = 1; i <= 6; ++i) {
            bounds = s[i].getGlobalBounds();
            if (checkCollision_wall(ball.shape, bounds)) {
                Vector2f normal = calculateNormal(ball.shape, bounds);
                ball.velocity -= 2.f * (ball.velocity.x * normal.x + ball.velocity.y * normal.y) * normal; // ���乫ʽ
            }
        }
    }
    // ��������ײ
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            if (checkCollision(balls[i], balls[j])) {
                Vector2f delta = balls[i].shape.getPosition() - balls[j].shape.getPosition();
                float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
                Vector2f norm = delta / dist;

                Vector2f relVel = balls[i].velocity - balls[j].velocity;
                float impulse = 2 * (relVel.x * norm.x + relVel.y * norm.y) / 2;

                balls[i].velocity -= impulse * norm;
                balls[j].velocity += impulse * norm;

                float angularImpulse = 0.2f;  // ��ת���ϵ��

                balls[i].angularVelocity += angularImpulse;
                balls[j].angularVelocity += angularImpulse;

                handleCollision(balls[i],balls[j]);
            }
        }
    }

    // ����Ч���������ٶȣ�ģ��Ħ������
    canShoot = 1;
    hide = 0;
    for (auto& ball : balls) {
        ball.velocity *= 0.99f; // ÿ֡�ٶȼ���1%
        ball.angularVelocity *= 0.98f; // ÿ֡���ٶȼ���2%��ģ��Ħ��
        if (abs(ball.velocity.x) > 0.01f || abs(ball.velocity.y) > 0.01f || ball.angularVelocity > 0.01f) {
            canShoot = 0;
            hide = 1;

        }
    }
}
//����� �� ������Ȩ �� �Ʒ�
void game::ballinHole() {
    bool cue = 0;//�����붴���������컬����Ϣ
    if (canShoot) {
        message = "";
    }
    if (Mode == Snoke) {
        for (int i = 0; i < balls.size(); ++i) {
            for (int rh = 1; rh <= 6; ++rh) {
                Vector2f ballCenter = balls[i].shape.getPosition();
                Vector2f rholeCenter = rhole[rh].getPosition();
                float distanceToHole = distance(ballCenter.x, rholeCenter.x, ballCenter.y, rholeCenter.y);
                if (distanceToHole <= rhole[rh].getRadius() + ball_radius) {
                    if (i < 15) cntBall--;
                    if (i <= 14) {
                        message += " redBall";
                        ++red;
                        ++redClear;
                    }
                    if (i == 15)placed = 0, cue = 1;
                    if (i == 16) {
                        message += " greenBall";
                        color += 10;
                    }
                    if (i == 17) {
                        message += " brownBall";
                        color += 100;
                    }
                    if (i == 18) {
                        message += " yellowBall";
                        color += 1;
                    }
                    if (i == 19) {
                        message += " blueBall";
                        color += 1000;
                    }
                    if (i == 20) {
                        message += " pinkBall";
                        color += 10000;
                    }
                    if (i == 21) {
                        message += " blackBall";
                        color += 100000;
                    }
                    ballVisible[i] = 0;
                    balls[i].velocity = Vector2f(0.f, 0.f);
                    if (i != 15)balls[i].shape.setScale(0, 0), balls[i].shape.setPosition(100 * i, 10000.f);
                }
            }
        }
        if (cue) {
            message += "how dare you make cue ball";
            fangui = 1;
        }
        if (canShoot && (red || color)) {//�н�����Ϊ
            haveShoot = 0;
            if (!hitBalltype) {//Ӧ���������
                if (!red || color) {//������
                    fangui = 1;
                }
                if (red) {
                    if (!(nowplay^sente))p1score += red;
                    else p2score += red;
                }
                if (color) {
                    int cnt = 0;
                    while (color) {
                        ++cnt;
                        if (color % 10) {
                            if (!(nowplay^sente))p2score += max(4, cnt);//����
                            else p1score += max(4, cnt);
                        }
                        color /= 10;
                    }
                }
            }
            else
                if (hitBalltype) {//Ӧ���������
                    if (red || !color) {//������Ȩ
                        fangui = 1;
                    }
                    if (red) {
                        if (!(nowplay^sente))p2score += red;
                        else p1score += red;
                    }
                    if (color) {
                        int cnt = 0;
                        while (color) {
                            ++cnt;
                            if (color % 10) {
                                if (!(nowplay^sente))p1score += cnt;//�ӷ�
                                else p2score += cnt;
                            }
                            color /= 10;
                        }
                    }
                }
            if (fangui)nowplay = !nowplay;
            else hitBalltype = !hitBalltype;
            red = 0;
            fangui = 0;
        }
    }
    if (Mode == China) {
        for (int i = 0; i < balls.size(); ++i) {
            for (int rh = 1; rh <= 6; ++rh) {
                Vector2f ballCenter = balls[i].shape.getPosition();
                Vector2f rholeCenter = rhole[rh].getPosition();
                float distanceToHole = distance(ballCenter.x, rholeCenter.x, ballCenter.y, rholeCenter.y);
                if (distanceToHole <= rhole[rh].getRadius() + balls[i].shape.getRadius()) {
                    if (i == 15)placed = 0, cue = 1;
                    //**********
                    if (i != 15)cntBall--;
                    if (balls[i].shape.getFillColor() == Color::Black) hitBlack = 1;

                    if (balls[i].shape.getFillColor() == Color::Green) {
                        ++green;
                        ++greenClear;
                        message += " greenBall";
                    }
                    if (balls[i].shape.getFillColor() == Color::Blue) {
                        ++blue;
                        ++blueClear;
                        message += " blueBall";
                    }
                    ballVisible[i] = 0;
                    balls[i].velocity = Vector2f(0.f, 0.f);
                    if (i != 15)balls[i].shape.setScale(0, 0), balls[i].shape.setPosition(100 * i, 10000.f);
                }
            }
        }
        if (cue) {
            message += "how dare you make cue ball";
            fangui = 1;
        }
        if (canShoot && (green || blue)) {//�н�����Ϊ
            haveShoot = 0;
            if (!(nowplay^sente)) {
                if (blue) {
                    fangui = 1;
                }
            }
            if ((nowplay^sente)) {
                if (green) {
                    fangui = 1;
                }
            }
            if (fangui)nowplay = !nowplay;
            green = 0;
            blue = 0;
            fangui = 0;
        }
    }
    //***********
    if (Mode == Challenge) {
        for (int i = 0; i < balls.size(); ++i) {
            for (int rh = 1; rh <= 6; ++rh) {
                Vector2f ballCenter = balls[i].shape.getPosition();
                Vector2f rholeCenter = rhole[rh].getPosition();
                float distanceToHole = distance(ballCenter.x, rholeCenter.x, ballCenter.y, rholeCenter.y);
                if (distanceToHole <= rhole[rh].getRadius() + balls[i].shape.getRadius()) {
                    if (i != 15) { cntBall--; }
                    if (i == 15) placed = 0, cue = 1;
                    ballVisible[i] = 0;
                    balls[i].velocity = Vector2f(0.f, 0.f);
                    if (i != 15) balls[i].shape.setScale(0, 0), balls[i].shape.setPosition(100 * i, 10000.f);
                }
            }
        }
        if (cue) {
            message += "how dare you make cue ball";
            fangui = 1;
            cntBall = 100, shots = 0;
        }
    }
}
//�����λ
void game::ballBack() {
    if (Mode == Snoke) {
        if (redClear != 15) {
            for (int i = 16; i < balls.size(); ++i) {
                if (!ballVisible[i]) {
                    if (i == 16)balls[i].shape.setPosition(525 * scale, 530 * scale);
                    if (i == 17)balls[i].shape.setPosition(525 * scale, 710 * scale);
                    if (i == 18)balls[i].shape.setPosition(525 * scale, 890 * scale);
                    if (i == 19)balls[i].shape.setPosition(1070 * scale, 710 * scale);
                    if (i == 20)balls[i].shape.setPosition(1469.06 * scale, 710 * scale);
                    if (i == 21)balls[i].shape.setPosition(1820 * scale, 710 * scale);
                    ballVisible[i] = 1;
                    balls[i].shape.setScale(1, 1);
                }
            }
            for (int i = 0; i < balls.size(); ++i) {
                for (int j = 15; j < balls.size(); ++j) {
                    if (i != j) {
                        while (checkCollision(balls[i], balls[j])) {
                            balls[j].shape.setPosition(balls[j].shape.getPosition().x - 10, balls[j].shape.getPosition().y);
                        }
                    }
                }
            }
        }
    }
}
//���뺯��
float game::distance(float x, float y, float z, float w) {
    return sqrt((x - y) * (x - y) + (z - w) * (z - w));
}
float game::distance(Vector2f p1, Vector2f p2) {
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}
//�������Ͱ���ĽǶ�(��ת������)
float game::calculateAngle(const Vector2f& ballPosition, const Vector2f& mousePosition) {
    float dx = mousePosition.x - ballPosition.x;
    float dy = mousePosition.y - ballPosition.y;
    return atan2(dy, dx) * 180.0f / M_PI; // ����ת�Ƕ�
}
//���ø��ӵ��������ͼ
void game::createStick() {
    cueTexture.loadFromFile("resources/stick.jpg");
    cueSprite.setTexture(cueTexture);
    cueSprite.setOrigin(cueTexture.getSize().x/2, 10.f); // ����β����Ϊԭ��
}
//�������λ��(��ת)
void game::updateCuePosition(Sprite& cueSprite, const Vector2f& ballPos,const Vector2f& mousePos) {
    // ����Ƕ�
    float angle = calculateAngle(ballPos, mousePos);
    // ���ø��ӵ���ת
    cueSprite.setRotation(angle-90);
    // ���ݾ������ø��ӵ�λ��
    float offsetX = cos(angle * M_PI / 180.0f) * (ball_radius + 20) * (magnitude * 0.2 < 1 ? 1 : magnitude * 0.2);
    float offsetY = sin(angle * M_PI / 180.0f) * (ball_radius + 20) * (magnitude * 0.2 < 1 ? 1 : magnitude * 0.2);
    cueSprite.setPosition(ballPos.x + offsetX, ballPos.y + offsetY);
}
//�������λ��(����)
void game::updateCuePosition2(Sprite& cueSprite, Vector2f& ballPos, Vector2f& mousePos) {
    // ����Ƕ�
    float angle = calculateAngle(ballPos, mousePos);

    // ���ø��ӵ���ת
    cueSprite.setRotation(angle - 90);

    // ���ݾ������ø��ӵ�λ��
    float offsetX = cos(angle * M_PI / 180.0f) * (ball_radius + 20) * waitClock.getElapsedTime().asSeconds();
    float offsetY = sin(angle * M_PI / 180.0f) * (ball_radius + 20) * waitClock.getElapsedTime().asSeconds();
    cueSprite.setPosition(ballPos.x + offsetX, ballPos.y + offsetY);

    //������
    if (distance(ballPos, cueSprite.getPosition()) <= ball_radius)touched = 1;
}
//������׼��
void game::updateAimingLines(Vector2f ballPos,Vector2f mousePos) {
    aimingLines.clear(); // ����ɵ���׼��
    mousePos = ballPos+ballPos-mousePos;
    Vector2f direction = mousePos - ballPos;
    // ��λ����������
    Vector2f normalizedDirection = direction / distance(ballPos, mousePos);
    // ��׼������
    Vector2f currentPoint = ballPos;
    while (1) {
        // ÿ������һ������
        currentPoint += normalizedDirection * 5.0f;
        // ����Ƿ����������ཻ
        for (int i = 0; i < balls.size(); ++i) {
            if (i == 15)continue;
            if (ballVisible[i] && distance(currentPoint, balls[i].shape.getPosition()) <= balls[i].shape.getRadius()) {
                aimingLines.emplace_back(VertexArray(Lines, 2));
                aimingLines.back()[0].position = ballPos;
                aimingLines.back()[1].position = currentPoint;
                aimingLines.back()[0].color = Color::Black;
                aimingLines.back()[1].color = Color::Black;
                // ���㷴������
                Vector2f hitDirection = - currentPoint + balls[i].shape.getPosition();
                Vector2f normalizedHitDirection = hitDirection / distance(Vector2f(0, 0), hitDirection);
                Vector2f nextPoint = currentPoint + normalizedHitDirection;
                float coefficient = 1.0f;
                while (1) {//�������Ҳ�պ����굽ǽ
                    bool f = 0;
                    coefficient += 1.0f;
                    nextPoint = currentPoint + normalizedHitDirection * coefficient;
                    for (auto& sp : sprite) {
                        FloatRect bounds = sp.getGlobalBounds();
                        float left = bounds.left;
                        float right = bounds.left + bounds.width;
                        float top = bounds.top;
                        float bottom = bounds.top + bounds.height;
                        float nearestX = max(left, min(nextPoint.x, right));
                        float nearestY = max(top, min(nextPoint.y, bottom));
                        float dis = distance(nextPoint.x, nearestX, nextPoint.y, nearestY);
                        if (dis < 1.f)f = 1;
                    }
                    if (f)break;
                }
                aimingLines.emplace_back(VertexArray(Lines, 2));
                aimingLines.back()[0].position = currentPoint;
                aimingLines.back()[1].position = nextPoint;
                aimingLines.back()[0].color = Color::Green;
                aimingLines.back()[1].color = Color::Green;
                return; // ֹͣ��һ������
            }
        }
        // ����Ƿ�ײǽ
        int cnt = 0, cntt = 0;
        for (auto& sp : sprite) {
            ++cnt;
            FloatRect bounds = sp.getGlobalBounds();
            float left = bounds.left;
            float right = bounds.left + bounds.width;
            float top = bounds.top;
            float bottom = bounds.top + bounds.height;
            float nearestX = max(left, min(currentPoint.x, right));
            float nearestY = max(top, min(currentPoint.y, bottom));
            float dis = distance(currentPoint.x, nearestX, currentPoint.y, nearestY);
            if (dis<1.f) {
                aimingLines.emplace_back(VertexArray(Lines, 2));
                aimingLines.back()[0].position = ballPos;
                aimingLines.back()[1].position = currentPoint;
                aimingLines.back()[0].color = Color::Black;
                aimingLines.back()[1].color = Color::Black;
                if(cnt==1||cnt==2||cnt==3||cnt==5||cnt==6)ballPos.x = 2 * currentPoint.x - ballPos.x;
                if(cnt==4||cnt==7)ballPos.y = 2 * currentPoint.y - ballPos.y;
                Vector2f hitDirection = -currentPoint + ballPos;
                Vector2f normalizedHitDirection = hitDirection / distance(Vector2f(0, 0), hitDirection);
                Vector2f nextPoint = currentPoint + normalizedHitDirection;
                float coefficient = 1.0f;
                while (1) {
                    bool f = 0;
                    coefficient += 1.0f;
                    nextPoint = currentPoint + normalizedHitDirection * coefficient;
                    for (auto& sp_ : sprite) {
                        if (++cntt == cnt)continue;
                        FloatRect bounds = sp_.getGlobalBounds();
                        float left = bounds.left;
                        float right = bounds.left + bounds.width;
                        float top = bounds.top;
                        float bottom = bounds.top + bounds.height;
                        float nearestX = max(left, min(nextPoint.x, right));
                        float nearestY = max(top, min(nextPoint.y, bottom));
                        float dis = distance(nextPoint.x, nearestX, nextPoint.y, nearestY);
                        if (dis < 1.f)f = 1;
                    }
                    if (f)break;
                }
                aimingLines.emplace_back(VertexArray(Lines, 2));
                aimingLines.back()[0].position = currentPoint;
                aimingLines.back()[1].position = nextPoint;
                aimingLines.back()[0].color = Color::Cyan;
                aimingLines.back()[1].color = Color::Cyan;
                return;
            }
        }
    }
}
//���ð���
void game::placeCueball(const Vector2f& mousePosition) {
    if (!ballVisible[15]) {
        balls[15].velocity = Vector2f(0.f, 0.f);
        if (leftClicked && mousePosition.x<525.f*scale && mousePosition.x>100.f*scale && mousePosition.y>530.f*scale && mousePosition.y<890.f*scale) {
            balls[15].shape.setPosition(mousePosition+Vector2f(0.1f,0.1f));  // ���ð������λ��
            placed = 1; // ���Ϊ�ѷ���
            ballVisible[15] = 1;  // ����ָ��ɼ�
        }
    }
}
//��Ϣ����
void game::stateAnnouncement() {
    if (Mode == Snoke) {
        switch (state) {
        case 2:info.showMessage("Opponent hits the Redball."); break;
        case 3:info.showMessage("Opponent hits the Colorball."); break;
        case 0:info.showMessage("You hit the Redball."); break;
        case 1:info.showMessage("You hit the Colorball."); break;
        case 4:info.showMessage("You place the cue ball."); break;
        case 5:info.showMessage("Opponent places the cue ball."); break;
        case 6:info.showMessage("You: " + message + " in pockets."); break;
        case 7:info.showMessage("Opponent: " + message + " in pockets."); break;
        }
    }
    if (Mode == China) {
        switch (state) {
        case 0:info.showMessage("You hit the Greenball."); break;
        case 2:info.showMessage("Opponent hits the Blueball."); break;
        case 4:info.showMessage("You place the cue ball."); break;
        case 5:info.showMessage("Opponent places the cue ball."); break;
        case 6:info.showMessage("You: " + message + " in pockets."); break;
        case 7:info.showMessage("Opponent: " + message + " in pockets."); break;
        }
    }
    //***********
    if (Mode == Challenge) {
        switch (state) {
        //case 0:info.showMessage("You hit the Redball."); break;
        case 4:info.showMessage("You place the cue ball."); break;
        default:info.showMessage("Hit all balls into the hole within remaining shots.And don't let cueBall get into the hole.");
        }
    }
}
//��������
void game::drawAll() {
    // �������ݺ͸�������
    window.clear();
    stateAnnouncement();
    if (Mode == Snoke)showScore(p1score, p2score);
    if (Mode == China)showScore(greenClear, blueClear);
    //************
    if (Mode == Challenge) showScore(shots, 0);
    updateInfoBox();
    window.draw(info.textBox);
    if (!info.currentMessage.empty()) {
        window.draw(info.infoText);
    }
    window.draw(scoreP1.textBox);
    window.draw(scoreP1.infoText);
    window.draw(scoreP2.textBox);
    window.draw(scoreP2.infoText);
    window.draw(spriteBackground);
    for (auto& sp : sprite)window.draw(sp);
    for (auto& rh : rhole)window.draw(rh);
    for (int i = 0; i < balls.size(); ++i) {
        if (ballVisible[i]) {
            window.draw(balls[i].shape);
        }
    }
    if(version==totalversion){
        window.draw(cueSprite);
        if (!hide) {
            for (auto& line : aimingLines) {
                window.draw(line);
            }
        }
    }
    window.draw(goLast.shape);
    window.draw(goNext.shape);
    window.draw(hitMethod1.shape);
    window.draw(hitMethod2.shape);
    window.draw(hitBall.shape);
    window.draw(stop.shape);
    window.draw(forMagnitude.background);
    window.draw(forMagnitude.handle);
    window.draw(forAngle.background);
    window.draw(forAngle.handle);
    window.display();
}
//����һ���汾����
void game::ballsBackup() {
    ballsRecord[++version] = balls;
    ++totalversion;
}
//��ȡһ���汾����
void game::ballsGetbackup(int nowVersion) {
    balls = ballsRecord[nowVersion];
}
//����ť�߼�
void game::handleButton(const Event& event, const RenderWindow& window, function<void()> onClick) {
    // �������Ƿ���ͣ�ڰ�ť��
    if (!canShoot)return;
    static Clock t;
    if(goLast.shape.getGlobalBounds().contains(mousePosition)) {
        goLast.shape.setFillColor(goLast.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            goLast.shape.setFillColor(goLast.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && t.getElapsedTime().asSeconds() > 1 && version >1) {
            ballsGetbackup(--version);
            t.restart();
            onClick(); // ִ�лص�����
        }
    }
    else {
        goLast.shape.setFillColor(goLast.defaultColor);
    }
    if (goNext.shape.getGlobalBounds().contains(mousePosition)) {
        goNext.shape.setFillColor(goNext.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            goNext.shape.setFillColor(goNext.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && t.getElapsedTime().asSeconds() > 1 && version < totalversion) {
            ballsGetbackup(++version);
            t.restart();
            onClick(); // ִ�лص�����
        }
    }
    else {
        goNext.shape.setFillColor(goNext.defaultColor);
    }
    if (hitMethod1.shape.getGlobalBounds().contains(mousePosition)) {
        hitMethod1.shape.setFillColor(hitMethod1.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            hitMethod1.shape.setFillColor(hitMethod1.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && t.getElapsedTime().asSeconds() > 1 && version == totalversion) {
            playWay = false;
            t.restart();
            onClick(); // ִ�лص�����
        }
    }
    else {
        hitMethod1.shape.setFillColor(hitMethod1.defaultColor);
    }
    if (hitMethod2.shape.getGlobalBounds().contains(mousePosition)) {
        hitMethod2.shape.setFillColor(hitMethod2.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            hitMethod2.shape.setFillColor(hitMethod2.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && t.getElapsedTime().asSeconds() > 1 && version == totalversion) {
            playWay = true;
            t.restart();
            onClick(); // ִ�лص�����
        }
    }
    else {
        hitMethod2.shape.setFillColor(hitMethod2.defaultColor);
    }
    if (hitBall.shape.getGlobalBounds().contains(mousePosition)) {
        hitBall.shape.setFillColor(hitBall.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            hitBall.shape.setFillColor(hitBall.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && t.getElapsedTime().asSeconds() > 1 && version == totalversion && playWay) {
            isCuePressed = 1;
            t.restart();
            onClick(); // ִ�лص�����
        }
    }
    else {
        hitBall.shape.setFillColor(hitBall.defaultColor);
    }
    if (stop.shape.getGlobalBounds().contains(mousePosition)) {
        stop.shape.setFillColor(stop.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            stop.shape.setFillColor(stop.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && t.getElapsedTime().asSeconds() > 1 && version == totalversion) {
            menu amenu;
            t.restart();
            onClick(); // ִ�лص�����
        }
    }
    else {
        stop.shape.setFillColor(stop.defaultColor);
    }
}
//���������߼�
void game::handleSlider(const Event& event, const RenderWindow& window, function<void()> onClick) {
    FloatRect handleBounds = forMagnitude.handle.getGlobalBounds();
    // ��ʼ�϶�����
    if (leftClicked && handleBounds.contains(mousePosition.x, mousePosition.y)) {
        forMagnitude.isDragging = true;
    }
    // ֹͣ�϶�����
    if (!leftClicked) {
        forMagnitude.isDragging = false;
    }
    // �϶�����
    if (forMagnitude.isDragging) {
        float sliderX = forMagnitude.background.getPosition().x;
        float sliderWidth = forMagnitude.background.getSize().x;
        float newX = mousePosition.x < sliderX ? sliderX : (mousePosition.x > sliderX + sliderWidth ? sliderX + sliderWidth : mousePosition.x);
        forMagnitude.handle.setPosition(newX - forMagnitude.handle.getSize().x / 2, forMagnitude.handle.getPosition().y);
        // ���ݻ���λ�ø��²���ֵ
        forMagnitude.currentValue = forMagnitude.minValue + (newX - sliderX) / sliderWidth * (forMagnitude.maxValue - forMagnitude.minValue);
    }
    handleBounds = forAngle.handle.getGlobalBounds();
    // ��ʼ�϶�����
    if (leftClicked && handleBounds.contains(mousePosition.x, mousePosition.y)) {
        forAngle.isDragging = true;
    }
    // ֹͣ�϶�����
    if (!leftClicked) {
        forAngle.isDragging = false;
    }
    // �϶�����
    if (forAngle.isDragging) {
        float sliderX = forAngle.background.getPosition().x;
        float sliderWidth = forAngle.background.getSize().x;
        float newX = mousePosition.x < sliderX ? sliderX : (mousePosition.x > sliderX + sliderWidth ? sliderX + sliderWidth : mousePosition.x);
        forAngle.handle.setPosition(newX - forAngle.handle.getSize().x / 2, forAngle.handle.getPosition().y);
        // ���ݻ���λ�ø��²���ֵ
        forAngle.currentValue = forAngle.minValue + (newX - sliderX) / sliderWidth * (forAngle.maxValue - forAngle.minValue);
    }
}

//***********
//����������λ����������Ϸ���㻭��
void game::drawSettlement() {

    const float scale_ = 0.714;
    bool isWin = p1score > p2score;

    //���ر���ͼ
    sf::Texture settleTexture;
    if (isWin) settleTexture.loadFromFile("images/You Win.png");
    else settleTexture.loadFromFile("images/You Lose.png");
    sf::Sprite settleSprite;
    settleSprite.setTexture(settleTexture);
    settleSprite.setScale(scale_, scale_);

    //�����û��ֺͽ��
    int getPoints = 0, getCoins = 0;
    if (Mode == Challenge) {
        if (isWin) getPoints = challengeIndex * 29, getCoins = 100;
        else getCoins = 10;
    }
    else {
        if (Track == Casual) { //������
            if (isWin) getCoins = 50, getPoints = 50;
            else getCoins = 20, getPoints = 20;
        }
        else { //��λ��
            int disPoints = 100;
            int magni = min(max(1, abs(disPoints)), 10);
            if (isWin) getCoins = (p1score - p2score) * 10 * magni, getPoints = (p1score - p2score) * magni;
            else getCoins = (p2score - p1score), getPoints = (p1score - p2score) * magni;
        }
    }
    sf::Font font;
    font.loadFromFile("fonts/Bear-hard-candy-2.ttf");
    sf::Text coinsText, pointsText;
    coinsText.setFont(font);
    coinsText.setString(std::to_string(getCoins));
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setCharacterSize(100 * scale_);
    coinsText.setPosition({ 890 * scale_, 560 * scale_ });
    pointsText.setFont(font);
    pointsText.setString(std::to_string(getPoints));
    pointsText.setFillColor(sf::Color::Yellow);
    pointsText.setCharacterSize(100 * scale_);
    pointsText.setPosition({ 890 * scale_, 750 * scale_ });
    
    //����Avatar����
    /*avatar->addCoins(getCoins);
    avatar->addPoints(getPoints);*/

    //���÷��ذ�ť
    button_ backButton({ 620 * scale_, 1000 * scale_ }, { 250 * scale_, 130 * scale_ }, "images/settlement_back.png", window, { 0, 0, 0 });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (backButton.if_contain(mousePosition)) window.close();
        //��Ⱦ
        window.clear();
        window.draw(settleSprite);
        window.draw(coinsText);
        window.draw(pointsText);
        backButton.Draw(window);
        window.display();
    }
}

void game::checkOutcome() {
    if (Mode == Snoke) {
        if (!cntBall) drawSettlement();
    }
    if (Mode == China) {
        if (!cntBall && hitBlack) {
            p1score = greenClear, p2score = blueClear;
            drawSettlement();
        }
        if (cntBall && hitBlack) {
            if (state == 0) p1score = 0, p2score = 100;
            else p1score = 100, p2score = 0;
            drawSettlement();
        }
    }
    if (Mode == Challenge) {
        if (!cntBall && shots >= 0) {
                p1score = challengeIndex * 10;
                p2score = 0;
                drawSettlement();

                //������һ��
                challengeIndex = 1;
            }
        if (cntBall && !shots) {
           p1score = p2score = 0;
           drawSettlement();
        }
    }
    
}
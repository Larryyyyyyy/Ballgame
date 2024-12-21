#include "menu.h"
menu::menu() :stop_window(VideoMode(1296 * scale, 1296 * scale), "Menu") {
    stop_window.setFramerateLimit(60);
    initial();
    while (stop_window.isOpen()) {
        Event event;
        while (stop_window.pollEvent(event)) {
            if (event.type == Event::Closed || go)stop_window.close();
            forIP.checkFocus(Mouse::getPosition(stop_window));
            forIP.handleEvent(event);
            forPort.checkFocus(Mouse::getPosition(stop_window));
            forPort.handleEvent(event);
        }
        forIP.update();
        forPort.update();
        handleButton(event, stop_window, []() {
            });
        drawall();
    }
}
menu::~menu() {}
void menu::initial() {
    picture[0].loadFromFile("resources/background_.png");
    background.setTexture(picture[0]);
    background.setPosition(0, 0);
    background.setScale(1, 1);
    continueGame.initiallizeButton(100, 570, 100, 40, "continueGame", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    picture[1].loadFromFile("resources/continuegame.png");
    continueGame.shape.setTexture(&picture[1]);
    picture[2].loadFromFile("resources/restart.png");
    restartGame.initiallizeButton(250, 570, 100, 40, "restartGame", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    restartGame.shape.setTexture(&picture[2]);
    picture[3].loadFromFile("resources/exitgame.png");
    exitGame.initiallizeButton(400, 570, 100, 40, "exitGame", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    exitGame.shape.setTexture(&picture[3]);
    picture[4].loadFromFile("resources/pvp.png");
    selectPVP.initiallizeButton(200, 320, 100, 100, "selectPVP", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    selectPVP.shape.setTexture(&picture[4]);
    picture[5].loadFromFile("resources/pvpol.png");
    selectPVPOL.initiallizeButton(340, 320, 100, 100, "selectPVPOL", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    selectPVPOL.shape.setTexture(&picture[5]);
    picture[6].loadFromFile("resources/snoke.png");
    selectSnoke.initiallizeButton(160, 170, 100, 100, "selectSnoke", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    selectSnoke.shape.setTexture(&picture[6]);
    picture[7].loadFromFile("resources/china.png");
    selectChina.initiallizeButton(260, 170, 100, 100, "selectChina", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    selectChina.shape.setTexture(&picture[7]);
    picture[8].loadFromFile("resources/challenge.png");
    selectChallenge.initiallizeButton(360, 170, 100, 100, "selectChallenge", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    selectChallenge.shape.setTexture(&picture[8]);
    picture[9].loadFromFile("resources/first.png");
    picture[10].loadFromFile("resources/second.jpg");
    whoFirst.initiallizeButton(500, 300, 70, 50, "whoFirst", scale, Color(255, 255, 255), Color(150, 150, 250), Color(50, 50, 200));
    whoFirst.shape.setTexture(&picture[9]);
    forIP.initial(100, 40, 400, 50);
    forPort.initial(100, 100, 400, 50);
}
void menu::drawall() {
    stop_window.clear();
    stop_window.draw(background);
    stop_window.draw(continueGame.shape);
    stop_window.draw(restartGame.shape);
    stop_window.draw(exitGame.shape);
    stop_window.draw(selectPVP.shape);
    stop_window.draw(selectPVPOL.shape);
    stop_window.draw(selectSnoke.shape);
    stop_window.draw(selectChina.shape);
    stop_window.draw(selectChallenge.shape);
    stop_window.draw(whoFirst.shape);
    stop_window.draw(forIP.background);
    stop_window.draw(forIP.text);
    stop_window.draw(forPort.background);
    stop_window.draw(forPort.text);
    stop_window.display();
}
void menu::handleButton(const Event& event, const RenderWindow& window, function<void()> onClick) {
    static Clock t;
    Vector2f mousePosition = stop_window.mapPixelToCoords(Mouse::getPosition(stop_window));
    if (continueGame.shape.getGlobalBounds().contains(mousePosition)) {
        continueGame.shape.setFillColor(continueGame.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            continueGame.shape.setFillColor(continueGame.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            go = 1;
            onClick();
        }
    }
    else {
        continueGame.shape.setFillColor(continueGame.defaultColor);
    }
    if (restartGame.shape.getGlobalBounds().contains(mousePosition)) {
        restartGame.shape.setFillColor(restartGame.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            restartGame.shape.setFillColor(restartGame.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            go = 2;
            onClick();
        }
    }
    else {
        restartGame.shape.setFillColor(restartGame.defaultColor);
    }
    if (exitGame.shape.getGlobalBounds().contains(mousePosition)) {
        exitGame.shape.setFillColor(exitGame.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            exitGame.shape.setFillColor(exitGame.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            go = 3;
            onClick();
        }
    }
    else {
        exitGame.shape.setFillColor(exitGame.defaultColor);
    }
    if (selectPVP.shape.getGlobalBounds().contains(mousePosition)) {
        selectPVP.shape.setFillColor(selectPVP.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            selectPVP.shape.setFillColor(selectPVP.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            Type = PVP;
            onClick();
        }
    }
    else {
        selectPVP.shape.setFillColor(selectPVP.defaultColor);
    }
    if (selectPVPOL.shape.getGlobalBounds().contains(mousePosition)) {
        selectPVPOL.shape.setFillColor(selectPVPOL.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            selectPVPOL.shape.setFillColor(selectPVPOL.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            Type = PVPOL;
            ip = forIP.getInputText();
            string t = forPort.getInputText();
            port = 0;
            for (int i = 0; i < t.size(); ++i) {
                port = port * 10 + t[i] - 48;
            }
            go = 2;
            onClick();
        }
    }
    else {
        selectPVPOL.shape.setFillColor(selectPVPOL.defaultColor);
    }
    if (selectSnoke.shape.getGlobalBounds().contains(mousePosition)) {
        selectSnoke.shape.setFillColor(selectSnoke.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            selectSnoke.shape.setFillColor(selectSnoke.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            Mode = Snoke;
            onClick();
        }
    }
    else {
        selectSnoke.shape.setFillColor(selectSnoke.defaultColor);
    }
    if (selectChina.shape.getGlobalBounds().contains(mousePosition)) {
        selectChina.shape.setFillColor(selectChina.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            selectChina.shape.setFillColor(selectChina.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            Mode = China;
            onClick();
        }
    }
    else {
        selectChina.shape.setFillColor(selectChina.defaultColor);
    }
    if (selectChallenge.shape.getGlobalBounds().contains(mousePosition)) {
        selectChallenge.shape.setFillColor(selectChallenge.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            selectChallenge.shape.setFillColor(selectChallenge.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            Mode = Challenge;
            onClick();
        }
    }
    else {
        selectChallenge.shape.setFillColor(selectChallenge.defaultColor);
    }
    if (whoFirst.shape.getGlobalBounds().contains(mousePosition)) {
        whoFirst.shape.setFillColor(whoFirst.hoverColor);
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            whoFirst.shape.setFillColor(whoFirst.clickColor);
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && t.getElapsedTime().asSeconds() > 1) {
            if (whoFirst.shape.getTexture() == &picture[9])whoFirst.shape.setTexture(&picture[10]), sente = 1;
            else whoFirst.shape.setTexture(&picture[9]), sente = 0;
            t.restart();
            onClick();
        }
    }
    else {
        whoFirst.shape.setFillColor(whoFirst.defaultColor);
    }
}

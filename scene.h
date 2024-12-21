#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 602;

//�����Ļ���
class Scene {
public:
    virtual ~Scene() = default;
    //���麯�����ȴ�����������дʵ��
    //virtual void handleInput(sf::RenderWindow& window) = 0; //���̰�������
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0; //�����¼������ò�����
    virtual void update() = 0; //�����߼�
    virtual void draw(sf::RenderWindow& windnow) = 0; //��Ⱦ
};

//����һ�����������������ڳ������л�
//������������Ҫ�볡����һһ��Ӧ
class SceneManager {
public:
    void addScene(std::shared_ptr<Scene> scene) { scenes.push_back(scene); } //�����³���

    void setCurrentScene(int index) { //���õ�ǰ����
        if (isLegal(index)) currentSceneIndex = index;
    }

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) { //�¼�����
        if (isLegal(currentSceneIndex))
            scenes[currentSceneIndex]->handleEvent(event, window); //����ǰ����
    }

    void update() { //�߼�����
        if (isLegal(currentSceneIndex))
            scenes[currentSceneIndex]->update();
    }

    void draw(sf::RenderWindow& window) { //��Ⱦ
        if (isLegal(currentSceneIndex))
            scenes[currentSceneIndex]->draw(window);
    }

private:
    std::vector<std::shared_ptr<Scene>> scenes; //�ų�����
    int currentSceneIndex = 0;

    //�жϳ�������Ƿ�Ϸ�
    bool isLegal(const int& index) const { return index >= 0 && index < scenes.size(); }
};

#endif
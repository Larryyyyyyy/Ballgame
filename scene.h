#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 602;

//场景的基类
class Scene {
public:
    virtual ~Scene() = default;
    //纯虚函数，等待派生类来编写实现
    //virtual void handleInput(sf::RenderWindow& window) = 0; //键盘按键输入
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0; //处理事件（引用参数）
    virtual void update() = 0; //更新逻辑
    virtual void draw(sf::RenderWindow& windnow) = 0; //渲染
};

//设置一个场景管理器，用于场景的切换
//场景管理器需要与场景类一一对应
class SceneManager {
public:
    void addScene(std::shared_ptr<Scene> scene) { scenes.push_back(scene); } //加入新场景

    void setCurrentScene(int index) { //设置当前场景
        if (isLegal(index)) currentSceneIndex = index;
    }

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) { //事件处理
        if (isLegal(currentSceneIndex))
            scenes[currentSceneIndex]->handleEvent(event, window); //处理当前场景
    }

    void update() { //逻辑更新
        if (isLegal(currentSceneIndex))
            scenes[currentSceneIndex]->update();
    }

    void draw(sf::RenderWindow& window) { //渲染
        if (isLegal(currentSceneIndex))
            scenes[currentSceneIndex]->draw(window);
    }

private:
    std::vector<std::shared_ptr<Scene>> scenes; //放场景们
    int currentSceneIndex = 0;

    //判断场景编号是否合法
    bool isLegal(const int& index) const { return index >= 0 && index < scenes.size(); }
};

#endif
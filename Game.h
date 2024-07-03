#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;

enum eDirecton 
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class SnakeGame
{

public:
    SnakeGame(int w, int h);
    ~SnakeGame();

    void Setup();
    void Draw();
    void Input();
    void Algorithm();
    void RunGame();
    void SaveInFile(const string& fileName);
    void LoadFromFile(const string& fileName);
    void SetSnakeColor();
private:
    int snakeColor = 7;
    bool gameOver;
    bool isLoadedFromFile;
    int width;
    int height;
    int x, y, fruitX, fruitY, score;
    int* tailX;
    int* tailY;
    int nTail;
    eDirecton dir;
};

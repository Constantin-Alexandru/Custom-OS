#pragma once
#include <stdint.h>
#include "math.h"
#include "BasicRenderer.h"
#include "userinput/keyboard.h"
#include "scheduling/pit/pit.h"
#include "cstr.h"

class SnakeGame
{

public:
    SnakeGame();
    void DrawGameWindow();
    void DrawSnake();

    void PrintScore();

    void PositionFruit();

    bool FatalCollision();

    bool GetsFruit();
    void MoveSnake();
    void PlayGame();

private:
    int width;
    int height;
    int direction;
    bool eatsFruit;
    Point fruit;
    int snake_size;
    int del;
    int score;

    char fruitChar;
    char partChar;
    char edgeChar;
    Point snake[128];
};

extern bool inGame;
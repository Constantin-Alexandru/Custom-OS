#include "snake.h"

bool inGame = false;

unsigned long int next;
int rand() // RAND_MAX assumed to be 32767
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}

SnakeGame::SnakeGame()
{
    partChar = 'x';
    edgeChar = (char)219;
    fruitChar - '-';
    fruit.X = 0;
    fruit.Y = 0;
    score = 0;
    del = 1100;
    eatsFruit = 0;
    direction = 4;
    snake_size = 0;
    width = 100;
    height = 50;

    GlobalRenderer->Clear();

    srand(PIT::TimeSinceBoot);
    PositionFruit();
    DrawGameWindow();
    DrawSnake();
    PrintScore();

    inGame = true;

    PlayGame();
}

void SnakeGame::DrawGameWindow()
{
    for (uint32_t i = 0; i < width; i++)
    {
        GlobalRenderer->CursorPosition = {i * 8, 0};
        GlobalRenderer->PutChar(edgeChar);
    }

    for (uint32_t i = 0; i < width; i++)
    {
        GlobalRenderer->CursorPosition = {i * 8, (height - 1) * 16};
        GlobalRenderer->PutChar(edgeChar);
    }

    for (uint32_t i = 0; i < height; i++)
    {
        GlobalRenderer->CursorPosition = {0, i * 16};
        GlobalRenderer->PutChar(edgeChar);
    }

    for (uint32_t i = 0; i < height; i++)
    {
        GlobalRenderer->CursorPosition = {(width - 1) * 8, i * 16};
        GlobalRenderer->PutChar(edgeChar);
    }
}

void SnakeGame::DrawSnake()
{
    for (uint32_t i = 0; i < 5; i++)
    {
        snake[snake_size++] = {30 + i, 10};
    }

    for (uint32_t i = 0; i < snake_size; i++)
    {
        GlobalRenderer->CursorPosition = {snake[i].X * 8, snake[i].Y * 16};
        GlobalRenderer->PutChar(partChar);
    }
    return;
}

void SnakeGame::PrintScore()
{
    GlobalRenderer->CursorPosition = {0, height * 16 + 16};
    GlobalRenderer->Print("Score: ");
    GlobalRenderer->Print(to_string((uint64_t)score));
    GlobalRenderer->CursorPosition = {0, height * 16 + 32};
    GlobalRenderer->Print("Direction: ");
    GlobalRenderer->Print(to_string((uint64_t)direction));

    return;
}

void SnakeGame::PositionFruit()
{
    while (1)
    {
        uint32_t tmpX = rand() % width + 1;
        uint32_t tmpY = rand() % height + 1;

        for (uint32_t i = 0; i < snake_size; i++)
        {
            if (snake[i].X == tmpX && snake[i].Y == tmpY)
                continue;
        }

        if (tmpX >= width - 2 || tmpY >= height - 3)
        {
            continue;
        }

        fruit.X = tmpX;
        fruit.Y = tmpY;
        break;
    }

    GlobalRenderer->CursorPosition = {fruit.X, fruit.Y};
    GlobalRenderer->PutChar(fruitChar);
}

bool SnakeGame::FatalCollision()
{
    if (snake[0].X == 0 || snake[0].X == width - 1 || snake[0].Y == 0 || snake[0].Y == height - 1)
    {
        return true;
    }

    for (uint32_t i = 2; i < snake_size; i++)
    {
        if (snake[0].X == snake[i].X && snake[0].Y == snake[i].Y)
        {
            return true;
        }
    }
    return false;
}

bool SnakeGame::GetsFruit()
{
    if (snake[0].X == fruit.X && snake[0].Y == fruit.Y)
    {
        PositionFruit();
        score += 10;
        PrintScore();

        if ((score % 100) == 0)
        {
            del -= 10;
        }
        return eatsFruit = true;
    }
    else
    {
        return eatsFruit = false;
    }
    return eatsFruit;
}

void SnakeGame::MoveSnake()
{
    GlobalRenderer->Colour = 0x00ff0000;
    GlobalRenderer->PutChar(lastChar);
    if (lastChar == 'w')
    {
        direction = 1;
    }
    else if (lastChar == 'd')
    {
        direction = 2;
    }
    else if (lastChar == 's')
    {
        direction = 3;
    }
    else if (lastChar == 'a')
    {
        direction = 4;
    }

    if (!eatsFruit)
    {
        GlobalRenderer->CursorPosition = {snake[snake_size - 1].X * 8, snake[snake_size - 1].Y * 16};
        GlobalRenderer->PutChar(' ');
        snake_size--;
    }
}

void SnakeGame::PlayGame()
{
    while (true)
    {

        if (FatalCollision())
        {
            GlobalRenderer->Clear();
            GlobalRenderer->CursorPosition = {GlobalRenderer->TargetFramebuffer->Width / 2 - 5, GlobalRenderer->TargetFramebuffer->Height / 2};
            GlobalRenderer->Print("GAME OVER");
            inGame = false;
            break;
        }

        GetsFruit();
        MoveSnake();

        if (lastChar == 'q')
        {
            inGame = false;
            break;
        }

        PIT::Sleep(del);
    }
}
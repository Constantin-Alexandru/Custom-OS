#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "snake.h"
#include "asciiAnimation.h"

extern "C" void _start(BootInfo *bootInfo)
{

    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    int frame = 0;

    while (true)
    {

        if (lastChar == 's' && !inGame)
        {
            GlobalRenderer->PutChar(lastChar);
            SnakeGame snakeGame = SnakeGame();
        }

        switch (frame)
        {
        case 0:
            GlobalRenderer->Clear();
            GlobalRenderer->CursorPosition = {0, 0};
            for (int i = 0; i < 16; i++)
            {
                GlobalRenderer->Print(lightsFrame1[i]);
                GlobalRenderer->Next();
            }
            frame = 1;
            break;
        case 1:
            GlobalRenderer->Clear();
            GlobalRenderer->CursorPosition = {0, 0};
            for (int i = 0; i < 16; i++)
            {
                GlobalRenderer->Print(lightsFrame2[i]);
                GlobalRenderer->Next();
            }
            frame = 2;
            break;
        case 2:
            GlobalRenderer->Clear();
            GlobalRenderer->CursorPosition = {0, 0};
            for (int i = 0; i < 16; i++)
            {
                GlobalRenderer->Print(lightsFrame3[i]);
                GlobalRenderer->Next();
            }
            frame = 0;
            break;
        }

        PIT::Sleep(20000);

        asm("hlt");
    }
}
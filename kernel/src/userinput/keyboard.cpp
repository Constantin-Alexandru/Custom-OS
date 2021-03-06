#include "keyboard.h"

bool isLeftShiftPressed;
bool isRightShiftPressed;

char lastChar;
void HandleKeyboard(uint8_t scancode)
{

    switch (scancode)
    {
    case LeftShift:
        isLeftShiftPressed = true;
        return;
    case LeftShift + 0x80:
        isLeftShiftPressed = false;
        return;
    case RightShift:
        isRightShiftPressed = true;
        return;
    case RightShift + 0x80:
        isRightShiftPressed = false;
        return;
    case Enter:
        lastChar = 0x0A;
        return;
    case Spacebar:
        lastChar = ' ';
        return;
    case BackSpace:
        GlobalRenderer->ClearChar();
        return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed);

    if (ascii != 0)
    {
        lastChar = ascii;
    }
    else
    {
        lastChar = '\n';
    }
}
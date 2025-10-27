#include "UserInput.h"

int UserInput::GetUserEntry(int menuSize)
{
    while (true)
    {
        int input = _getch() - '0';

        if (input >= 1 && input <= menuSize)
        {
            return input;
        }
    }
}

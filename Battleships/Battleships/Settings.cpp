#include "Settings.h"

Difficulty Settings::gameDifficulty = Difficulty::Easy; 

//sets default window size
void Settings::ResizeConsole(int width, int height)
{
        // Get the current console handle
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

        // Set the new console buffer size
        COORD bufferSize = { width, height };
        SetConsoleScreenBufferSize(hConsole, bufferSize);

        // Set the new console window size
        SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
        SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}


void Settings::SetGameDifficulty(Difficulty difficulty)
{
        gameDifficulty = difficulty;
}


Difficulty Settings::GetGameDifficulty()
{
    return gameDifficulty;
}


std::string Settings::GetDifficultyAsString(Difficulty difficulty)
{
    switch (difficulty)
    {
    case Difficulty::Easy:
        return "EASY";

    case Difficulty::Medium:
        return "MEDIUM";

    case Difficulty::Hard:
        return "HARD";

    }
}

TextColour Settings::GetDifficultyColour(Difficulty difficulty)
{
    switch (difficulty)
    {
    case Difficulty::Easy:
        return TextColour::Green;

    case Difficulty::Medium:
        return TextColour::Yellow;

    case Difficulty::Hard:
        return TextColour::Red;
    }
}



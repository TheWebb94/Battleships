#include <iostream>
#include <Windows.h>
#include "DrawUI.h"
#include "UserInput.h"
#include "Battleships.h"
#include "Game.h"
#include "Settings.h"

// Battleships.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Battleships.h"

int main()
{
    SetDefaultSettings();

    bool inGame = true;

    while (inGame)
    {
        DrawMainMenu();
        

        int userChoice;

        userChoice = UserInput::GetUserEntry(2);

        switch (userChoice)
        {
        case 1:
            Game::LaunchGame();
            break;

        case 2:
            inGame = false;
            break;

        }
    }
}

void SetDefaultSettings()
{
    Settings::ResizeConsole(500, 500);
    Settings::SetGameDifficulty(Difficulty::Easy);
}

void DrawMainMenu()
{
    system("cls");
    DrawUI::DrawGamePanel(UIPanels::Options);
    DrawUI::TitleMenu();
    DrawUI::DrawTitleLogo();
}



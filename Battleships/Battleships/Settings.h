#pragma once
#include <iostream>
#include <Windows.h>
#include "DrawUI.h"
#include "UserInput.h"
#include "Battleships.h"

enum Difficulty
{
	Easy,
	Medium,
	Hard
};

class Settings
{
	static Difficulty gameDifficulty;

public:
	static void ResizeConsole(int width, int height);

	static void SetGameDifficulty(Difficulty difficulty);

	static Difficulty GetGameDifficulty();

	static std::string GetDifficultyAsString(Difficulty difficulty);

	static TextColour GetDifficultyColour(Difficulty difficulty);
};


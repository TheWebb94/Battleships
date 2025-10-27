#pragma once

#include <iostream>
#include <Windows.h>
#include <fcntl.h> // for using the unicode chars
#include <io.h>
#include <string>
#include <vector>
#include "Ship.h"


enum TextColour
{
	Green,
	White,
	Red,
	Blue,
	Yellow
};

enum UIPanels
{
	MainPanel,
	Options,
	GameMenu,
	GridCell,
};

//unicode chars got from https://www.w3.org/TR/xml-entity-names/025.html
const static std::wstring horizontalLine = L"\u2500";;
const static std::wstring verticalLine = L"\u2502";
const static std::wstring topLeftCorner = L"\u250C";
const static std::wstring topRightCorner = L"\u2510";
const static std::wstring bottomRightCorner = L"\u2518";
const static std::wstring bottomLeftCorner = L"\u2514";
const static std::wstring topTLine = L"\u252c";
const static std::wstring leftTLine = L"\u251c";
const static std::wstring rightTLine = L"\u2524";
const static std::wstring bottomTLine = L"\u2534";
const static std::wstring crossIntersectionLine = L"\u253c";
const static std::wstring symbol = L"\u25A0";


class DrawUI {
private:
	//Start position for text in options menu
	const static int gameMenuOffsetY = 4;
	const static int gameMenuOffsetX = 1;
	const static int xPos = 2;
	const static int yPos = 19;


	static void GetPanelDimensions(UIPanels panel, int& panelWidth, int& panelHeight, int& panelPositionX, int& panelPositionY);

public:


	static void SetCursorPosition(int x, int y);

	static void SetTextColour(TextColour colour);

	static void DrawGamePanel(UIPanels panel);

	static void ClearGamePanel(UIPanels panel);

	static void TitleMenu();

	static void GameOptionsMenu();

	static void SetDifficultyMenu();

	static void ChooseShipToPlaceMenu(const std::vector<Ship*>& ships);

	static void ShipOrientationMenu();

	static void ChooseCoordPlacementMenu();

	static void ChooseCoordAttackMenu();

	static void ThrowErrorMessage(std::string message, int duration);

	static void ThrowMessage(std::string message1, TextColour colour1, std::string message2, TextColour colour2, std::string message3, TextColour colour3, int duration);

	static void RandomShipPlacementMenu();

	static void DrawTitleLogo();

};
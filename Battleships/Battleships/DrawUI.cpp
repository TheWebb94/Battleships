#include "DrawUI.h"


/// <summary>
/// Sets the dimensions of the panel being drawn to the panel enum given
/// </summary>
/// <param name="panel"></param>
/// <param name="panelWidth"></param>
/// <param name="panelHeight"></param>
/// <param name="panelPositionX"></param>
/// <param name="panelPositionY"></param>
void DrawUI::GetPanelDimensions(UIPanels panel, int& panelWidth, int& panelHeight, int& panelPositionX, int& panelPositionY)
{
	switch (panel)
	{
	case MainPanel:
		//set parameters for each case - needs testing of screen sizes on console run
		panelWidth = 93;
		panelHeight = 18;
		panelPositionX = 0;
		panelPositionY = 0;
		break;

	case Options:
		panelWidth = 93;
		panelHeight = 7;
		panelPositionX = 0;
		panelPositionY = 18;
		break;

	case GameMenu:
        panelWidth = 90;
        panelHeight = 8;
        panelPositionX = 2;
        panelPositionY = 22;
		break;

	case GridCell:
        break;
	}

		


}

/// <summary>
/// Sets the cursor position to the given x,y coord
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void DrawUI::SetCursorPosition(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}


/// <summary>
/// Sets the text colour to the colour associated with the enum given
/// </summary>
/// <param name="colour"></param>
void DrawUI::SetTextColour(TextColour colour)
{
	switch (colour)
	{
	case TextColour::Green:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		break;

	case TextColour::White:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;

	case TextColour::Red:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		break;

	case TextColour::Blue:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		break;

	case TextColour::Yellow:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		break;


	default: //white
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	}

}

/// <summary>
/// pass in the panel you want drawn and it outputs it to the console
/// </summary>
/// <param name="panel"></param>
void DrawUI::DrawGamePanel(UIPanels panel)
{
	//Sets output mode to handle wcout
	_setmode(_fileno(stdout), _O_U16TEXT);


	int panelWidth = 0;
	int panelHeight = 0;
	int panelPositionX = 0;
	int panelPositionY = 0;


	GetPanelDimensions(panel, panelWidth, panelHeight, panelPositionX, panelPositionY);

	SetTextColour(TextColour::Green);

	for (int x = panelPositionX + 1; x < (panelPositionX + panelWidth); x++)
	{
		//Draw top horizontal line of box
		SetCursorPosition(x, panelPositionY);
		std::wcout << horizontalLine;

		//Draw bottom horizontal line 
		SetCursorPosition(x, panelPositionY + panelHeight - 1);
		std::wcout << horizontalLine;

	}

	for (int y = panelPositionY + 1; y < (panelPositionY + panelHeight - 1); y++)
	{
		//Draw left vertical line
		SetCursorPosition(panelPositionX, y);
		std::wcout << verticalLine;

		//Draw right vertical line
		SetCursorPosition(panelPositionX + panelWidth, y);
		std::wcout << verticalLine;

	}

	//Draw corners
	SetCursorPosition(panelPositionX, panelPositionY); //top left
	std::wcout << topLeftCorner;

	SetCursorPosition(panelPositionX + panelWidth, panelPositionY); //top right
	std::wcout << topRightCorner;

	SetCursorPosition(panelPositionX, panelPositionY + panelHeight - 1); //bottom left
	std::wcout << bottomLeftCorner;

	SetCursorPosition(panelPositionX + panelWidth, panelPositionY + panelHeight - 1); //bottom right
	std::wcout << bottomRightCorner;

	//Resets output mode to handle cout
	_setmode(_fileno(stdout), _O_TEXT);

	SetTextColour(TextColour::White);

}

/// <summary>
/// clears the contents of the given panel
/// </summary>
/// <param name="panel"></param>
void DrawUI::ClearGamePanel(UIPanels panel)
{
	int panelWidth = 0;
	int panelHeight = 0;
	int panelPositionX = 0;
	int panelPositionY = 0;

	GetPanelDimensions(panel, panelWidth, panelHeight, panelPositionX, panelPositionY);

	//Clear box interiors
	for (int x = panelPositionX + 1; x < panelPositionX + panelWidth - 1; x++)
	{
		for (int y = panelPositionY + 1; y < panelPositionY + panelHeight - 1; y++)
		{
			SetCursorPosition(x, y);
			std::wcout << " ";
		}
	}

}

//menu options for the title menu
void DrawUI::TitleMenu()
{

	SetCursorPosition(xPos, yPos);
	std::cout << "1. Play Game";
	SetCursorPosition(xPos, yPos + 1);
	std::cout << "2. Exit";

}

//menu options for pre-game menu
void DrawUI::GameOptionsMenu()
{
  
        SetCursorPosition(xPos + gameMenuOffsetX, yPos+gameMenuOffsetY);
        std::cout << "1. Set Difficulty";
        SetCursorPosition(xPos + gameMenuOffsetX, yPos + 1 + gameMenuOffsetY);
        std::cout << "2. Place Ships";
        SetCursorPosition(xPos + gameMenuOffsetX, yPos + 2 + gameMenuOffsetY);
        std::cout << "3. Begin Game";
        SetCursorPosition(xPos + gameMenuOffsetX, yPos + 3 + gameMenuOffsetY);
        std::cout << "4. Exit";

}

//menu options for the settings menu
void DrawUI::SetDifficultyMenu()
{

    SetCursorPosition(xPos + gameMenuOffsetX, yPos + gameMenuOffsetY);
    std::cout << "1. Easy";
    SetCursorPosition(xPos + gameMenuOffsetX, yPos + 1 + gameMenuOffsetY);
    std::cout << "2. Medium";
    SetCursorPosition(xPos + gameMenuOffsetX, yPos + 2 + gameMenuOffsetY);
    std::cout << "3. Hard";
    SetCursorPosition(xPos + gameMenuOffsetX, yPos + 3 + gameMenuOffsetY);
    std::cout << "4. Exit";



}

//menu options for the ship placement menu, this also shows which ships are placed already
void DrawUI::ChooseShipToPlaceMenu(const std::vector<Ship*>& ships)
{

	int placedOffset = 50;
	// For each ship, check if it is placed and append " - Placed" to the ship name
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + gameMenuOffsetY);
	std::cout << "1. Carrier";
	if (ships[0]->GetIsShipPlaced()) {
		SetCursorPosition(xPos + gameMenuOffsetX + placedOffset, yPos + gameMenuOffsetY);
		std::cout << "- Placed";
	}

	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 1 + gameMenuOffsetY);
	std::cout << "2. Battleship";
	if (ships[1]->GetIsShipPlaced()) {
		SetCursorPosition(xPos + gameMenuOffsetX + placedOffset, yPos + 1 + gameMenuOffsetY);
		std::cout << "- Placed";
	}

	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 2 + gameMenuOffsetY);
	std::cout << "3. Cruiser";
	if (ships[2]->GetIsShipPlaced()) {
		SetCursorPosition(xPos + gameMenuOffsetX + placedOffset, yPos + 2 + gameMenuOffsetY);
		std::cout << "- Placed";
	}

	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 3 + gameMenuOffsetY);
	std::cout << "4. Submarine";
	if (ships[3]->GetIsShipPlaced()) {
		SetCursorPosition(xPos + gameMenuOffsetX + placedOffset, yPos + 3 + gameMenuOffsetY);
		std::cout << "- Placed";
	}

	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 4 + gameMenuOffsetY);
	std::cout << "5. Destroyer";
	if (ships[4]->GetIsShipPlaced()) {
		SetCursorPosition(xPos + gameMenuOffsetX + placedOffset, yPos + 4 + gameMenuOffsetY);
		std::cout << "- Placed";
	}

	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 5 + gameMenuOffsetY);
	std::cout << "6. Exit";
}
void DrawUI::ShipOrientationMenu()
{
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + gameMenuOffsetY);
	std::cout << "1. Horizontal";
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 1 + gameMenuOffsetY);
	std::cout << "2. Vertical";
}

//menu option for choosing coordinates when placing the ships
void DrawUI::ChooseCoordPlacementMenu()
{
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + gameMenuOffsetY);
	std::cout << "Enter letter of column to place ship:\t";
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 1 + gameMenuOffsetY);
	std::cout << "Enter number of row to place ship:\t";

}

//menu options for when choosing coords to attack
void DrawUI::ChooseCoordAttackMenu()
{
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + gameMenuOffsetY);
	std::cout << "Enter letter of column to attack:\t";
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 1 + gameMenuOffsetY);
	std::cout << "Enter number of row to attack:\t";

}

//custom error throwing method to output specific messages in a predetermined location
void DrawUI::ThrowErrorMessage(std::string message, int duration)
{

	DrawUI::ClearGamePanel(GameMenu);
	DrawUI::SetCursorPosition(3, 23);
	DrawUI::SetTextColour(Red);
	std::cout << "Error: " + message;
	Sleep(duration * 1000);
	DrawUI::SetTextColour(White);
	DrawUI::ClearGamePanel(GameMenu);
	return;
}

//custom notification method to output messages to a predetermined location. allows colouring of differentr parts of the message
void DrawUI::ThrowMessage(std::string message1, TextColour colour1, std::string message2, TextColour colour2, std::string message3, TextColour colour3, int duration)
{
	DrawUI::ClearGamePanel(GameMenu);
	DrawUI::SetCursorPosition(3, 23);
	DrawUI::SetTextColour(TextColour::Blue);
	std::cout << "Message: ";
	DrawUI::SetTextColour(colour1);
	std::cout << message1;
	DrawUI::SetTextColour(colour2);
	std::cout << message2;
	DrawUI::SetTextColour(colour3);
	std::cout << message3;
	Sleep(duration	* 1000);
	DrawUI::ClearGamePanel(GameMenu);
	return;

}

//menu options for random ship placement menu
void DrawUI::RandomShipPlacementMenu()
{
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + gameMenuOffsetY);
	std::cout << "Would you like your unplaced ships to be placed randomly?";
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 1 + gameMenuOffsetY);
	std::cout << "1. Yes";
	SetCursorPosition(xPos + gameMenuOffsetX, yPos + 2 + gameMenuOffsetY);
	std::cout << "2. No";


}

//draws the title logo/message
void DrawUI::DrawTitleLogo()
{
	int logoXPos = 2;
	int logoYPos = 2;
	DrawUI::SetCursorPosition(logoXPos, logoYPos);
	DrawUI::SetTextColour(TextColour::Green);

	std::cout << "  ____        _   _   _           _     _           ";
	DrawUI::SetCursorPosition(logoXPos, logoYPos+1);
	std::cout << " |  _ \\      | | | | | |         | |   (_)          ";
	DrawUI::SetCursorPosition(logoXPos, logoYPos+2);
	std::cout << " | |_) | __ _| |_| |_| | ___  ___| |__  _ _ __  ___ ";
	DrawUI::SetCursorPosition(logoXPos, logoYPos+3);
	std::cout << " |  _ < / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\/ __|";
	DrawUI::SetCursorPosition(logoXPos, logoYPos+4);
	std::cout << " | |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) \\__ \\";
	DrawUI::SetCursorPosition(logoXPos, logoYPos+5);
	std::cout << " |____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/|___/";
	DrawUI::SetCursorPosition(logoXPos, logoYPos+6);
	std::cout << "                                         | |        ";
	DrawUI::SetCursorPosition(logoXPos, logoYPos+7);
	std::cout << "                                         |_|        ";

	DrawUI::SetTextColour(TextColour::White);
}


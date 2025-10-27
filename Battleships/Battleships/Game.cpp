#include "Game.h"

	Grid playerGrid(true);
	Grid enemyGrid(false);

	Ship playerCarrier(ShipName::Carrier, 5, false, true);
	Ship playerBattleship(ShipName::Battleship, 4, false, true);
	Ship playerCruiser(ShipName::Cruiser, 3, false, true);
	Ship playerSubmarine(ShipName::Submarine, 3, false, true);
	Ship playerDestroyer(ShipName::Destroyer, 2, false, true);

	Ship EnemyCarrier(ShipName::Carrier, 5, false, true);
	Ship EnemyBattleship(ShipName::Battleship, 4, false, true);
	Ship EnemyCruiser(ShipName::Cruiser, 3, false, true);
	Ship EnemySubmarine(ShipName::Submarine, 3, false, true);
	Ship EnemyDestroyer(ShipName::Destroyer, 2, false, true);

	std::vector<Ship*> ships = {
	&playerCarrier,
	&playerBattleship,
	&playerCruiser,
	&playerSubmarine,
	&playerDestroyer
	};

	std::vector<std::pair<int, int>> Game::hitCells;
	std::vector<std::pair<int, int>> Game::huntTargets;




void Game::LaunchGame()
{
	std::system("cls");

	DrawGrids();
	DrawUI::DrawGamePanel(GameMenu);
	DrawUI::GameOptionsMenu();
	
	bool inGame = true;

	while (inGame) 
	{
		DrawUI::GameOptionsMenu();
		playerGrid.DrawAllShips();

		int userInput = UserInput::GetUserEntry(4);

		switch (userInput)
		{
		case 1:
			SetDifficultySequence();
			break;

		case 2:
			PlacePlayerShipsSequence();
			break;

		case 3:
			if (AreAllShipsArePlaced())
			{
				BeginGame();
			}
			break;

		case 4:
			inGame = false;
			break;

		}
	}
}

//the sequence of options for setting the difficulty of the game
void Game::SetDifficultySequence()
{
	DrawUI::ClearGamePanel(GameMenu);
	DrawUI::SetDifficultyMenu();
	

	bool inDifficultyMenu = true;

	while (inDifficultyMenu)
	{
		int userInput = UserInput::GetUserEntry(4);

		switch (userInput)
		{
		case 1:
			Settings::SetGameDifficulty(Difficulty::Easy);

			break;
		case 2:
			Settings::SetGameDifficulty(Difficulty::Medium);

			break;
		case 3:
			Settings::SetGameDifficulty(Difficulty::Hard);

			break;
		case 4:
			inDifficultyMenu = false;

		}
			DrawUI::ThrowMessage("Difficulty set to ", TextColour::White, Settings::GetDifficultyAsString(Settings::GetGameDifficulty()), Settings::GetDifficultyColour(Settings::GetGameDifficulty()), ".", TextColour::White, 2.5);

		DrawUI::ClearGamePanel(GameMenu);
		inDifficultyMenu = false;
	}
}


//the  sequence of options for placing of the player ships
void Game::PlacePlayerShipsSequence()
{
	bool isPlacingShips = true;

	while (isPlacingShips)
	{
		std::vector<Ship*> placedShips;

		for (int i = 0; i < ships.size(); i++)
		{
			Ship* selectedShip = nullptr;
			bool validSelection = false;

			while (!validSelection)
			{
				DrawUI::ClearGamePanel(GameMenu);
				DrawUI::ChooseShipToPlaceMenu(ships);
				playerGrid.DrawAllShips();

				int userInput = UserInput::GetUserEntry(6);  

				if (userInput == 6) 
				{
					DrawUI::ClearGamePanel(GameMenu);
					isPlacingShips = false;
					break;  
				}

				if (!userInput < 1 || userInput > 5)
				{
					selectedShip = ships[userInput - 1];

					if (std::find(placedShips.begin(), placedShips.end(), selectedShip) != placedShips.end())
					{
						DrawUI::ClearGamePanel(GameMenu);
						DrawUI::SetCursorPosition(3, 23);
						DrawUI::SetTextColour(Red);
						std::cout << "This ship has already been placed. Choose another.";
						Sleep(1000);
						DrawUI::ClearGamePanel(GameMenu);
						DrawUI::SetTextColour(White);
					}
					else
					{
						validSelection = true;
					}
				}
			}

			if (!isPlacingShips)
			{
				break;  
			}

			bool placedSuccessfully = false;
			while (!placedSuccessfully)
			{
				ChooseOrientationOfShip(selectedShip);
				std::pair<int, int> startCoords = ChooseCoords(true);

				DrawUI::ClearGamePanel(GameMenu);

				if (playerGrid.PlaceShip(*selectedShip, startCoords.first, startCoords.second))
				{
					placedShips.push_back(selectedShip);
					placedSuccessfully = true;
				}
				else
				{
					DrawUI::ClearGamePanel(GameMenu);
					DrawUI::SetCursorPosition(3, 23);
					DrawUI::SetTextColour(Red);
					std::cout << "Invalid ship placement, please try again.";
					Sleep(1000);
					DrawUI::ClearGamePanel(GameMenu);
					DrawUI::SetTextColour(White);
				}
			}
		}
	}
}


void Game::DrawGrids()
{
	playerGrid.DrawGameGrid(true);
	enemyGrid.DrawGameGrid(false);
}

//gets user input for orientation of the player ship being placed
void Game::ChooseOrientationOfShip(Ship* ship)
{
	DrawUI::ClearGamePanel(GameMenu);
	DrawUI::ShipOrientationMenu();

	int orientationInput = UserInput::GetUserEntry(2); // 1 = Horizontal, 2 = Vertical
	
	ship->SetOrientationOfShip(orientationInput);

	DrawUI::ClearGamePanel(GameMenu);
}

//gets coords from the user, with error handling to make sure it is in bounds
std::pair<int, int> Game::ChooseCoords(bool isPlacingShipMenu)
{
	char rowLetter;
	int startX = -1, startY = -1, colNumber;
	bool validCoords = false;

	while (!validCoords)
	{
		DrawUI::ClearGamePanel(GameMenu);
		if (isPlacingShipMenu)
		{
			DrawUI::ChooseCoordPlacementMenu();
		}
		else
		{
			DrawUI::ChooseCoordAttackMenu();
		}
		DrawUI::SetCursorPosition(50, 23);
		std::cin >> rowLetter;

		DrawUI::SetCursorPosition(50, 24);
		std::cin >> colNumber;

		
		if (std::cin.fail())
		{
			std::cin.clear(); 
			std::cin.ignore(10000, '\n');
			DrawUI::ThrowErrorMessage("Invalid input! Try again.", 2.5);
			continue;
		}

		// Convert the row letter to an index (A=0, B=1, ...)
		startX = std::toupper(rowLetter) - 'A';
		startY = colNumber - 1;

		// Check if coordinates are valid (within grid bounds)
		if (startX >= 0 && startX < 10 && startY >= 0 && startY < 10)
		{
			validCoords = true;
		}
		else
		{
			DrawUI::ThrowErrorMessage("Invalid coordinates! Try again.", 2.5);
		}
	}

	return { startX, startY };
}

//gameplay loop
void Game::BeginGame()
{
	bool gameRunning = true;

	PlaceEnemyShips();
	
	while (gameRunning)
	{
		PlayerTurn();

		
		if (AreAllShipsSunk(enemyGrid))
		{
			GameVictory();
			break; 
		}

		EnemyTurn();

		
		if (AreAllShipsSunk(playerGrid))
		{
			GameLose();
			break;
		}
	}
}


//checks all player ships are placed before allowing game to start
bool Game::AreAllShipsArePlaced()
{
	for (auto& ship : ships)
	{
		if (!ship->GetIsShipPlaced())
		{
			DrawUI::ThrowErrorMessage("Not all ships are placed, place all ships before starting!", 2.5);

			DrawUI::RandomShipPlacementMenu();

			int input = UserInput::GetUserEntry(2);

			switch (input)
			{
			case 1:
				RandomlyPlacePlayerShips();
				playerGrid.DrawAllShips();
				return true;

			case 2:
				DrawUI::ClearGamePanel(GameMenu);
				return false;
			}

		}
	}
	return true;
}

//places the enemy ships into their grid
bool Game::PlaceEnemyShips()
{
	std::vector<Ship*> enemyShips = {
		&EnemyCarrier,
		&EnemyBattleship,
		&EnemyCruiser,
		&EnemySubmarine,
		&EnemyDestroyer
	};

	for (auto& ship : enemyShips)
	{
		bool placedSuccessfully = false;

		while (!placedSuccessfully)
		{
			// Randomly choose orientation (1 = Horizontal, 2 = Vertical)
			int orientation = (rand() % 2) + 1;
			ship->SetOrientationOfShip(orientation);

			// Randomly select starting position
			int startX = rand() % enemyGrid.numberOfCellsX;
			int startY = rand() % enemyGrid.numberOfCellsY;

			// Check if placement is valid (does not overlap)
			if (CanPlaceShip(ship, startX, startY, orientation))
			{
				enemyGrid.PlaceShip(*ship, startX, startY);
				placedSuccessfully = true;
			}
		}
	}
	return true; // Successfully placed all enemy ships
}

//checks whether a ship can be placed in the given location
bool Game::CanPlaceShip(Ship* ship, int startX, int startY, int orientation)
{
	int shipSize = ship->GetShipSize();

	for (int i = 0; i < shipSize; i++)
	{
		int x = startX;
		int y = startY;

		if (orientation == 1) // Horizontal
		{
			x += i;
		}
		else // Vertical
		{
			y += i;
		}

		// Check if out of bounds
		if (x >= enemyGrid.numberOfCellsX || y >= enemyGrid.numberOfCellsY)
		{
			return false;
		}

		// Check if cell already contains a ship
		if (enemyGrid.GetCell(x, y).containsShip)
		{
			return false;
		}
	}
	return true; // Ship can be placed here
}

//logic for the player taking their turn
void Game::PlayerTurn()
{
	bool isPlayerTurn = true;

	while (isPlayerTurn)
	{

		std::pair<int, int> targetCoords;

		bool validTarget = false;

		while (!validTarget)
		{
			targetCoords = ChooseCoords(false);

			if (!enemyGrid.GetCell(targetCoords.first, targetCoords.second).isHit)
			{
				validTarget = true;
			}
		}
		if (!enemyGrid.AttackCell(targetCoords.first, targetCoords.second, true))
		{
			isPlayerTurn = false;
		}

	}
}

//allows the player to randomly place their ships
void Game::RandomlyPlacePlayerShips()
{	
	for (auto& ship : ships)
	{
		if (!ship->GetIsShipPlaced())
		{
			bool placedSuccessfully = false;

			while (!placedSuccessfully)
			{
				int orientation = (rand() % 2) + 1;
				ship->SetOrientationOfShip(orientation);

				srand(static_cast<unsigned>(time(0)));

				int startX = rand() % playerGrid.numberOfCellsX;
				int startY = rand() % playerGrid.numberOfCellsY;

				if (playerGrid.PlaceShip(*ship, startX, startY))
				{
					placedSuccessfully = true;
				}
			}
		}
	}
}

//logic for the enemy turn
void Game::EnemyTurn()
{
	srand(static_cast<unsigned>(time(0)));

	bool isEnemyTurn = true;
	while (isEnemyTurn)
	{
		std::pair<int, int> targetCoords = EnemyChooseTarget();

		// Attack the selected cell
		if (!playerGrid.AttackCell(targetCoords.first, targetCoords.second, false))
		{
			isEnemyTurn = false; // Missed, turn ends
		}
		else
		{
			playerGrid.GetCell(targetCoords.first, targetCoords.second).isHit = true;
			hitCells.push_back(targetCoords); // Store the hit for tracking
		}
	}
}

//
std::pair<int, int> Game::EnemyChooseTarget()
{

	if (Settings::GetGameDifficulty() == Difficulty::Easy) // Easy - Random shot
	{
		return GetRandomTarget();
	}
	else if (Settings::GetGameDifficulty() == Difficulty::Medium) // Medium - Hunt Mode
	{
		return GetHuntTarget();
	}
	else if (Settings::GetGameDifficulty() == Difficulty::Hard) // Hard - Strategic AI
	{
		return GetSmartTarget();
	}
	return GetRandomTarget();
}

std::pair<int, int> Game::GetRandomTarget()
{
	int x, y;
	do
	{
		x = rand() % playerGrid.numberOfCellsX;
		y = rand() % playerGrid.numberOfCellsY;
	} while (playerGrid.GetCell(x, y).isHit);

	return { x, y };
}

std::pair<int, int> Game::GetHuntTarget()
{
	if (!huntTargets.empty())
	{
		std::pair<int, int> target = huntTargets.back();
		huntTargets.pop_back(); // Remove from list
		return target;
	}

	// If huntTargets is empty, re-enter hunt mode based on hitCells history
	if (!hitCells.empty())
	{
		std::pair<int, int> lastHit = hitCells.back();
		AddHuntTargets(lastHit.first, lastHit.second);
	}

	return GetRandomTarget();
}

void Game::AddHuntTargets(int x, int y)
{
	// Reset hunt targets for a new ship if this is the first hit
	if (huntTargets.empty())
	{
		hitCells.clear();
	}

	hitCells.push_back({ x, y }); // Store all hit cells of the current ship

	// Add new hunt targets only if the cell is a ship
	if (playerGrid.GetCell(x, y).containsShip)
	{
		std::vector<std::pair<int, int>> newTargets;

		// Identify hunt direction from past hits
		if (hitCells.size() > 1)
		{
			int dx = hitCells[1].first - hitCells[0].first;
			int dy = hitCells[1].second - hitCells[0].second;

			int nx = x + dx;
			int ny = y + dy;

			if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && !playerGrid.GetCell(nx, ny).isHit)
			{
				newTargets.push_back({ nx, ny }); // Continue in the same direction
			}
		}
		else
		{
			// Add standard hunt targets
			if (x > 0 && !playerGrid.GetCell(x - 1, y).isHit) newTargets.push_back({ x - 1, y });
			if (x < 9 && !playerGrid.GetCell(x + 1, y).isHit) newTargets.push_back({ x + 1, y });
			if (y > 0 && !playerGrid.GetCell(x, y - 1).isHit) newTargets.push_back({ x, y - 1 });
			if (y < 9 && !playerGrid.GetCell(x, y + 1).isHit) newTargets.push_back({ x, y + 1 });
		}

		// Add newly determined hunt targets
		huntTargets.insert(huntTargets.end(), newTargets.begin(), newTargets.end());
	}
}

std::pair<int, int> Game::GetSmartTarget()
{
	if (!huntTargets.empty())
	{
		return GetHuntTarget();
	}

	std::vector<std::pair<int, int>> highProbabilityCells;
	int maxProbability = -1;

	for (int x = 0; x < playerGrid.numberOfCellsX; x++)
	{
		for (int y = 0; y < playerGrid.numberOfCellsY; y++)
		{
			if (!playerGrid.GetCell(x, y).isHit)
			{
				int probability = CalculatePlacementProbability(x, y);

				if (probability > maxProbability)
				{
					maxProbability = probability;
					highProbabilityCells.clear();
					highProbabilityCells.push_back({ x, y });
				}
				else if (probability == maxProbability)
				{
					highProbabilityCells.push_back({ x, y });
				}
			}
		}
	}

	// Pick a random cell from the highest probability list
	if (!highProbabilityCells.empty())
	{
		int index = rand() % highProbabilityCells.size();
		return highProbabilityCells[index];
	}

	return GetRandomTarget(); // Fallback
}


int Game::CalculatePlacementProbability(int x, int y)
{
    int probability = 0;

    // Check surrounding cells for potential ship placement
    if (x > 0 && !playerGrid.GetCell(x - 1, y).isHit) probability++;
    if (x < 9 && !playerGrid.GetCell(x + 1, y).isHit) probability++;
    if (y > 0 && !playerGrid.GetCell(x, y - 1).isHit) probability++;
    if (y < 9 && !playerGrid.GetCell(x, y + 1).isHit) probability++;

    return probability;
}

bool Game::AreAllShipsSunk(Grid grid)
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (grid.GetCell(x, y).containsShip && !grid.GetCell(x, y).isHit)
			{
				return false;
			}
		}
	}
	
	return true;
}

void Game::GameVictory()
{
	DrawUI::ThrowMessage("VICTORY!", TextColour::Green, "", TextColour::White, "", TextColour::White,10);
}

void Game::GameLose()
{
	DrawUI::ThrowMessage("You have lost all your battleships!", TextColour::Red, "", TextColour::White, "", TextColour::White, 10);

}


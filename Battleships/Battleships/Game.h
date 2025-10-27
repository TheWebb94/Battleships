#pragma once
#include <Windows.h>
#include <io.h>
#include <iostream>
#include "DrawUI.h"
#include "UserInput.h"
#include "Settings.h"
#include "Ship.h"
#include "Grid.h"
#include <vector>
#include "Cell.h"
#include <iomanip>
#include <limits>
#include <ctime>


class Game
{

	static std::vector<std::pair<int, int>> hitCells; // Stores successful hits
	static std::vector<std::pair<int, int>> huntTargets; // Stores adjacent cells for follow-up shots

public:
	static void LaunchGame();
	static void SetDifficultySequence();
	static void PlacePlayerShipsSequence();
	static void DrawGrids();
	static void ChooseOrientationOfShip(Ship*);
	static std::pair<int, int> ChooseCoords(bool isPlacingShipMenu);
	static void BeginGame();
	static bool AreAllShipsArePlaced();
	static bool PlaceEnemyShips();
	static bool CanPlaceShip(Ship* ship, int startX, int startY, int orientation);
	static void PlayerTurn();
	static void RandomlyPlacePlayerShips();
	static void EnemyTurn();
	static std::pair<int, int> EnemyChooseTarget( );
	static std::pair<int, int> GetRandomTarget();
	static std::pair<int, int> GetHuntTarget();
	static void AddHuntTargets(int x, int y);
	static std::pair<int, int> GetSmartTarget();
	static int CalculatePlacementProbability(int x, int y);
	static bool AreAllShipsSunk(Grid grid);
	static void GameVictory();
	static void GameLose();
};


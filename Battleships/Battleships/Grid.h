#pragma once
#include "DrawUI.h"
#include <vector>
#include "Cell.h"
#include "Ship.h"

class Grid
{
public:
    int cellWidth;
    int cellHeight;
    int startPosX;
    int startPosY;
    int numberOfCellsX;
    int numberOfCellsY;
    int distanceBetweenGrids = 10;
    int offsetX = 0; 

    std::vector <Cell> cells;

    Grid(bool isPlayerGrid = true);

    void DrawGameGrid(bool drawPlayerGrid);

    Cell& GetCell(int x, int y);

    bool PlaceShip(Ship& ship, int startX, int startY);

    void DrawAllShips();

    bool HasAttackedHereBefore(int x, int y);

    bool AttackCell(int x, int y, bool isPlayerAttack);

    void DrawAttackMarker(int x, int y, TextColour colour);
};

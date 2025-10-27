#include "Grid.h"


Grid::Grid(bool isPlayerGrid)
{
    cellWidth = 4;
    cellHeight = 2;
    startPosX = 2;
    startPosY = 1;
    numberOfCellsX = 10;
    numberOfCellsY = 10;

    cells.resize(numberOfCellsX * numberOfCellsY);

    if (!isPlayerGrid)
    {
        offsetX = numberOfCellsX * cellWidth + distanceBetweenGrids;
    }
}

//procedurally draws the game grids
void Grid::DrawGameGrid(bool drawPlayerGrid = true)
{
    int gridWidth = numberOfCellsX * cellWidth;
    int gridHeight = numberOfCellsY * cellHeight;
    int originalStartPosX = 2; //for resetting of startPosX at the end of the method

    if (!drawPlayerGrid)
    {
        DrawUI::SetTextColour(TextColour::Red);
        startPosX = startPosX + gridWidth + 10;
    }
    else
    {
        DrawUI::SetTextColour(TextColour::Green);
    }

    _setmode(_fileno(stdout), _O_U16TEXT);


    // Top left corner
    DrawUI::SetCursorPosition(startPosX, startPosY);
    std::wcout << topLeftCorner;

    // Top right corner
    DrawUI::SetCursorPosition(startPosX + gridWidth, startPosY);
    std::wcout << topRightCorner;

    // Top horizontal line
    for (int i = startPosX + 1; i < startPosX + gridWidth; i++)
    {
        DrawUI::SetCursorPosition(i, startPosY);
        if ((i - startPosX) % cellWidth == 0)
        {
            std::wcout << topTLine;
        }
        else
        {
            std::wcout << horizontalLine;
        }
    }

    // Bottom horizontal line
    for (int i = startPosX + 1; i < startPosX + gridWidth; i++)
    {
        DrawUI::SetCursorPosition(i, startPosY + gridHeight); 
        if ((i - startPosX) % cellWidth == 0)
        {
            std::wcout << bottomTLine;
        }
        else
        {
            std::wcout << horizontalLine;
        }
    }

    // Left vertical line
    for (int i = startPosY + 1; i < startPosY + gridHeight; i++)
    {
        DrawUI::SetCursorPosition(startPosX, i);
        if ((i - startPosY) % cellHeight == 0)
        {
            std::wcout << leftTLine;
        }
        else
        {
            std::wcout << verticalLine;
        }
    }

    // Right vertical line
    for (int i = startPosY + 1; i < startPosY + gridHeight; i++)
    {
        DrawUI::SetCursorPosition(startPosX + gridWidth, i);
        if ((i - startPosY) % cellHeight == 0)
        {
            std::wcout << rightTLine;
        }
        else
        {
            std::wcout << verticalLine;
        }
    }

    // Bottom left corner
    DrawUI::SetCursorPosition(startPosX, startPosY + gridHeight);
    std::wcout << bottomLeftCorner;

    // Bottom right corner
    DrawUI::SetCursorPosition(startPosX + gridWidth, startPosY + gridHeight);
    std::wcout << bottomRightCorner;

    // Grid interior
    for (int x = startPosX + 1; x < startPosX + gridWidth; x++)
    {
        for (int y = startPosY + 1; y < startPosY + gridHeight; y++)
        {
            // Check for intersections
            if ((x - startPosX) % cellWidth == 0 && (y - startPosY) % cellHeight == 0)
            {
                DrawUI::SetCursorPosition(x, y);
                std::wcout << crossIntersectionLine;
            }
            // Vertical lines inside the grid (cell borders on x)
            else if ((x - startPosX) % cellWidth == 0)
            {
                DrawUI::SetCursorPosition(x, y);
                std::wcout << verticalLine;
            }
            // Horizontal lines inside the grid (cell borders on y)
            else if ((y - startPosY) % cellHeight == 0)
            {
                DrawUI::SetCursorPosition(x, y);
                std::wcout << horizontalLine;
            }
            // Empty spaces in the grid cells
            else
            {
                DrawUI::SetCursorPosition(x, y);
                std::wcout << " ";
            }
        }
    }

    //Draw grid numbers for indexing
    for (int n = 1; n <= numberOfCellsY; n++)
    {
        DrawUI::SetCursorPosition(startPosX - 2, startPosY + (cellHeight * n) - 1);
        std::wcout << n;
    }

    //Draw grid letters for indexing
    for (int l = 1; l <= numberOfCellsX; l++)
    {
        DrawUI::SetCursorPosition(startPosX + (cellWidth * l) - 2, startPosY - 1);
        std::wcout << (char)(l + 64);
    }

    startPosX = originalStartPosX;
    _setmode(_fileno(stdout), _O_TEXT);
    DrawUI::SetCursorPosition(40, 20);
}

Cell& Grid::GetCell(int x, int y)
{
    return cells[y * numberOfCellsX + x];
}


bool Grid::PlaceShip(Ship& ship, int startX, int startY)
{
    if (startX < 0 || startX >= numberOfCellsX || startY < 0 || startY >= numberOfCellsY)
    {
        return false;
    } // bounds checking for given x,y

    if (ship.GetOrientation() == true)
    {
        if (startX + ship.GetShipSize() > numberOfCellsX)
        {
            return false;
        }
    }
    else
    {
        if (startY + ship.GetShipSize() > numberOfCellsY)
        {
            return false;
        }
    } // bounds checking for ship place at given x,y

    for (int i = 0; i < ship.GetShipSize(); i++)
    {
        int x = startX;
        int y = startY;

        if (ship.GetOrientation() == true)
        {
            x = startX + i;
        }
        else
        {
            y = startY + i;
        }

        if (GetCell(x, y).containsShip)
        {
            return false;
        }
    } // checks if ship is blocking placement of this ship

    
    for (int i = 0; i < ship.GetShipSize(); i++)
    {
        int x = startX;
        int y = startY;

        if (ship.GetOrientation() == true)
        {
            x = startX + i;
        }
        else
        {
            y = startY + i;
        }

        GetCell(x, y).containsShip = true;
    }

    ship.SetShipPlaced();

    return true;
}


//draws the ships to the grid
void Grid::DrawAllShips()
{
    _setmode(_fileno(stdout), _O_U16TEXT);  

    for (int y = 0; y < numberOfCellsY; ++y)
    {
        for (int x = 0; x < numberOfCellsX; ++x)
        {
            if (GetCell(x, y).containsShip)
            {
                int drawPosX = offsetX + startPosX + x * cellWidth + (cellWidth / 2);
                int drawPosY = startPosY + y * cellHeight + (cellHeight / 2);

                DrawUI::SetCursorPosition(drawPosX, drawPosY);

                std::wcout << symbol; 
            }
        }
    }
    _setmode(_fileno(stdout), _O_TEXT);  
}

//checks if the cell was attacked
bool Grid::HasAttackedHereBefore(int x, int y)
{
    Cell& targetCell = GetCell(x, y);

    if (targetCell.isHit)
    {
        return true;
    }


}

//makes an attack on a cell
bool Grid::AttackCell(int x, int y, bool isPlayerAttack)
{
    Cell& targetCell = GetCell(x, y);

    targetCell.isHit = true;
    char xChar = 'A' + x;

    std::string attacker;

    if (isPlayerAttack)
    {
        attacker = "You";
    }
    else
    {
        attacker = "The Enemy";
    }

    if (targetCell.containsShip)
    {
        DrawAttackMarker(x, y, TextColour::Red);
        DrawUI::ThrowMessage(attacker + " ", TextColour::White, "HIT ", TextColour::Red, "a ship on " + std::string(1, xChar) + std::to_string(y + 1), TextColour::White, 2);
        return true;
    }
    else
    {
        DrawAttackMarker(x, y, TextColour::Blue);
        DrawUI::ThrowMessage(attacker + " ", TextColour::White, "MISSED ", TextColour::Blue, "a ship on " + std::string(1, xChar) + std::to_string(y + 1), TextColour::White, 2);
        return false;
    }
}

//marks the cell with the attack marker when atttacekd
void Grid::DrawAttackMarker(int x, int y, TextColour colour)
{

    int drawPosX = startPosX + offsetX + x * cellWidth + (cellWidth / 2);
    int drawPosY = startPosY +  y * cellHeight + (cellHeight / 2);

    DrawUI::SetCursorPosition(drawPosX, drawPosY);

    DrawUI::SetTextColour(colour);

    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wcout << symbol;

    _setmode(_fileno(stdout), _O_TEXT);

    DrawUI::SetTextColour(White);
}


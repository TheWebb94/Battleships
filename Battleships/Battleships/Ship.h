#pragma once
#include <string>

enum ShipName
{
	Carrier,
	Battleship,
	Cruiser,
	Submarine,
	Destroyer
};

class Ship
{
	std::string shipName;
	int shipSize;
	bool isHorizontal;


public:

	bool isShipPlaced;

	Ship(ShipName shipName, int shipSize, bool isShipPlaced, bool isHorizontal);

	int GetShipSize() const;

	bool GetOrientation();

	std::string GetShipName() const;

	void SetOrientationOfShip(int orientationCode);

	void SetShipPlaced();

	bool GetIsShipPlaced();
};


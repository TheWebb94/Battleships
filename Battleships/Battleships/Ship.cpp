#include "Ship.h"

Ship::Ship(ShipName shipName, int shipSize,  bool isShipPlaced, bool isHorizontal)
{
	this->shipSize = shipSize;
	this->isShipPlaced = isShipPlaced;
	this->isHorizontal = isHorizontal;

	switch (shipName)
	{
		case Carrier:
			this->shipName = "Carrier";
			break;
		case Battleship:
			this->shipName = "Battleship";
			break;
		case Cruiser:
			this->shipName = "Cruiser";
			break;
		case Submarine:
			this->shipName = "Submarine";
			break;
		case Destroyer:
			this->shipName = "Destroyer";
			break;

	}
}

int Ship::GetShipSize() const
{
	return shipSize;
}

std::string Ship::GetShipName() const
{
	return shipName;
}

bool Ship::GetOrientation()
{
	return isHorizontal;
}

void Ship::SetOrientationOfShip(int orientationCode)
{
	if (orientationCode == 1)
	{
		isHorizontal = true;
	}
	else
	{
		isHorizontal = false;
	}
}

void Ship::SetShipPlaced()
{
	isShipPlaced = true;
}

bool Ship::GetIsShipPlaced()
{
	return isShipPlaced;
}


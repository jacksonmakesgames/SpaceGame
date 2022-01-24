#pragma once
#include <Ship.h>

#define SHIPTHRUSTTEXTUREPATH "textures/ShipThrust.png"
class Player : public Ship{
public:
	Player();
private:
	void update() override;
	void getInput();

};
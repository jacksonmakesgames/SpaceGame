#pragma once
#include <Watty/gameobjects/GameObject.h>
#include <Watty/graphics/sprite.h>
#include <Watty/graphics/textures/SpriteSheetAnimation.h>

#define THRUSTTEXTUREPATH "textures/ShipThrust.png"



using namespace letc;

class Ship : public GameObject
{
private:
	GameObject* thrustFire;
public:
	Ship();
	~Ship();

	

private:

};

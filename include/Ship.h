#pragma once
#include <Watty/gameobjects/GameObject.h>
#include <Watty/graphics/sprite.h>
#include <Watty/graphics/textures/SpriteSheetAnimation.h>
#include <input/Input.h>
#include <utils/timer.h>
#include <Projectile.h>
#include <vector>

#define THRUSTTEXTUREPATH "textures/ShipThrust.png"

using namespace watty;

class Ship : public GameObject
{
protected:
	float fireRate = 2.0f;
	float nextFireTime;
	float moveSpeed = 2.0f;
	float maxVelocity = 7.0f;
	std::vector<Transform2D*> thrusters;
	bool inertialDamp = true;
	
private:
	GameObject* thrustFire;
	float fireRate_INV;
	short health;

public:
	Ship();
	~Ship();

	virtual void update() override;
	void limitVelocity();
protected:
	void fire();
};

#pragma once
#include <Watty/gameobjects/Instantiate.h>
#include <Watty/graphics/sprite.h>
#include <Watty/graphics/textures/SpriteSheetAnimation.h>
#include <input/Input.h>
#include <utils/timer.h>
#include <Projectile.h>
#define THRUSTTEXTUREPATH "textures/ShipThrust.png"

using namespace letc;

class Ship : public GameObject
{
protected:
	float fireRate = 2.0f;
	float nextFireTime;
	float moveSpeed = 2.0f;
	float maxVelocity = 7.0f;
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

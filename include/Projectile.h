#pragma once
#include <SpaceUtil.h>
#include <Watty/gameobjects/GameObject.h>
#include <Watty/graphics/sprite.h>

#include <glm.hpp>
#include <limits>
#include <imgui.h>

using namespace watty;
using namespace graphics;
using namespace physics;

class Projectile : public GameObject{
private:
	static float defaultForce;
	float lifetime = 2.0f;
	float destroyTime = 99999999999;
public:
	void onSensorEnter(b2Contact* contact) override;
	Projectile(glm::vec2 position, glm::vec2 size);
	~Projectile();
	void update() override;
	void init(glm::vec2 dir, float force);

};
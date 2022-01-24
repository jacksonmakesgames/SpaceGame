#include "Projectile.h"

float Projectile::defaultForce = 10.0f;

void Projectile::onSensorEnter(b2Contact* contact)
{
	std::cout << "on sensor" << std::endl;
}

Projectile::Projectile(glm::vec2 position, glm::vec2 size) : GameObject(position,size, new Sprite(new Texture("textures/projectile.png")))
{
	destroyTime = Timer::elapsed() + lifetime;
}

Projectile::~Projectile()
{
	GameObject::~GameObject();
}

void Projectile::update()
{
	
	GameObject::update();
	Util::checkAreaBounds(this);
	if (Timer::elapsed() > destroyTime) {
		Destroy(this);
	}
}

void Projectile::init(glm::vec2 dir, float force){
	PhysicsBody2DParams params = PhysicsBody2DParams(BodyShapes::box, transform->getPosition(), transform->getSize(), b2BodyType::b2_dynamicBody);
	params.isSensor = true;
	addComponent(new PhysicsBody2D(params));
	getPhysicsBody2D()->addForce(dir, force);
	getPhysicsBody2D()->getBody()->SetLinearDamping(0.0f);
}


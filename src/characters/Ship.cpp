#include "Ship.h"

Ship::Ship()
{
	thrustFire = new GameObject();
	thrustFire->transform->setPosition(glm::vec3(.25, -.25, 0));
	thrustFire->transform->setSize(glm::vec2(.5, .5));
	thrustFire->addComponent(new graphics::Sprite(new graphics::Texture(THRUSTTEXTUREPATH)));
	thrustFire->addAnimator();
	graphics::SpriteSheetAnimInfo info = graphics::SpriteSheetAnimInfo();
	info.loop = true;
	info.name = "Fire";
	info.playbackRate = 5.0f;
	info.numberOfCols = 2;
	info.numberOfRows = 1;
	thrustFire->getAnimator()->addAnimation(new graphics::SpriteSheetAnimation(info));
	thrustFire->getAnimator()->play("Fire");

	transform->addChild(thrustFire->transform);
	thrusters.push_back(thrustFire->transform);
	
	fireRate_INV = 1.0f / fireRate;
	nextFireTime = Timer::elapsed() + fireRate_INV;

}

Ship::~Ship()
{
}

void Ship::update(){
	Util::checkAreaBounds(this);
	limitVelocity();
	GameObject::update();

}

void Ship::limitVelocity() {
	b2Vec2 vel = getPhysicsBody2D()->getBody()->GetLinearVelocity();
	float speed = vel.Normalize();//normalizes vector and returns length
	if (speed > maxVelocity)
		getPhysicsBody2D()->getBody()->SetLinearVelocity(maxVelocity * vel);
}


void Ship::fire(){
	if (nextFireTime < Timer::elapsed()) {
		nextFireTime = Timer::elapsed() + fireRate_INV;
		Projectile* p = Instantiate<Projectile>(transform->getPosition() + glm::vec2(0, .5f), {.3,.3},"Main Layer");
		glm::vec3 dir = {0,1,0};
		glm::quat q = glm::quat(glm::vec3(0,0,transform->getRotation()));
		dir = q * dir;
		p->init(dir, 80.0f);
		p->getPhysicsBody2D()->getBody()->SetTransform(b2Vec2(transform->getPosition().x, transform->getPosition().y) + b2Vec2(dir.x*.5f, dir.y*.5f),transform->getRotation());
	}
}





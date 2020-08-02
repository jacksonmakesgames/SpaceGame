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
}

Ship::~Ship()
{
}

#include "Player.h"

Player::Player() : Ship()
{
	transform->setPosition(glm::vec3(0, 0, 0));
	glm::vec2 playerSize = glm::vec2(1, 1);
	transform->setSize(playerSize);
	addComponent(new graphics::Sprite(new graphics::Texture("textures/player_ship.png")));
	PhysicsBody2DParams params = PhysicsBody2DParams(
		physics::BodyShapes::box,
		transform->getPosition(),
		playerSize,
		b2_dynamicBody);

	addComponent(new physics::PhysicsBody2D(params));

	getPhysicsBody2D()->getBody()->SetAngularDamping(.3f);

}

void Player::update()
{
	Ship::update();
	getInput();

}

void Player::getInput() {
	if (Input::keyIsDown(GLFW_KEY_SPACE)) {
		fire();
	}
	if (Input::keyWasReleased(GLFW_KEY_Z)) {
		inertialDamp = !inertialDamp;
	}
	
	float rotation = -.01 * (float)(Input::keyIsDown(GLFW_KEY_A) || Input::keyIsDown(GLFW_KEY_LEFT)) + .01f * (float)(Input::keyIsDown(GLFW_KEY_D) || Input::keyIsDown(GLFW_KEY_RIGHT));
	float vertical = -1 * (float)(Input::keyIsDown(GLFW_KEY_W) || Input::keyIsDown(GLFW_KEY_UP));

	if (inertialDamp and rotation==0){
		getPhysicsBody2D()->getBody()->SetAngularDamping(1.0f);
	}
	else {
		getPhysicsBody2D()->getBody()->SetAngularDamping(0);
	}
	if (inertialDamp and vertical == 0) {
		getPhysicsBody2D()->getBody()->SetLinearDamping(1.0f);
	}
	else {
		getPhysicsBody2D()->getBody()->SetLinearDamping(0);
	}
	

	glm::vec2 thrust = glm::vec2();
	thrust.x = sin(getPhysicsBody2D()->getBody()->GetAngle());
	thrust.y = -cos(getPhysicsBody2D()->getBody()->GetAngle());

	getPhysicsBody2D()->getBody()->ApplyAngularImpulse(-rotation, true);
	getPhysicsBody2D()->addImpulse(thrust, vertical * moveSpeed * Timer::delta);

	if (vertical > 0.1f || vertical < -0.1f)
		thrusters[0]->setSize(glm::vec2(.5, .5));
	else
		thrusters[0]->setSize(glm::vec2());

}

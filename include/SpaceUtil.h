#pragma once
#include <glm.hpp>
#include <gameobjects/GameObject.h>
#include <gameobjects/Transform2D.h>
#include <Watty/graphics/Camera.h>
using namespace watty;

static class Util {
public:
	static void checkAreaBounds(GameObject* go)
	{
		Transform2D* transform = go->transform;
		glm::vec2 bounds = graphics::Camera::allCameras[graphics::Camera::allCameras.size()-1]->getViewportSize();
		bounds.x = bounds.x / 2.0f;
		bounds.y = bounds.y / 2.0f;

		glm::vec2 pos = transform->getPosition();

		if (pos.x > bounds.x) {
			transform->setPosition({ -bounds.x, pos.y });
		}
		else if (pos.x < -bounds.x) {
			transform->setPosition({ bounds.x, pos.y });
		}if (pos.y > bounds.y) {
			transform->setPosition({ pos.x, -bounds.y });
		}
		else if (pos.y < -bounds.y) {
			transform->setPosition({ pos.x, bounds.y });
		}
	}
};

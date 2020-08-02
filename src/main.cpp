
#include <Watty.h>
#include "characters/Ship.h"
#include "renderer/SpaceRenderer.h"
#include <res.h>
#include <math.h>
#include <cmath>


#define SHIPTEXTUREPATH "textures/Ship.png"
#define SHIPTHRUSTTEXTUREPATH "textures/ShipThrust.png"
#define BACKGROUNDTEXTUREPATH "textures/Background.png"
#define VERTPATH "shaders/basic.vert"
#define FRAGLITPATH "shaders/basic_lit.frag"
#define FRAGUNLITPATH "shaders/basic_unlit.frag"

#include <random>

using namespace letc;
using namespace graphics;
using namespace math;
using namespace physics;


namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, 0.0f));

	}
}



constexpr uint32_t g_starColours[8] =
{
	0xFFFFFFFF, 0xFFD9FFFF, 0xFFA3FFFF, 0xFFFFC8C8,
	0xFFFFCB9D, 0xFF9F9FFF, 0xFF415EFF, 0xFF28199D
};


struct sPlanet
{
	double distance = 0.0;
	double diameter = 0.0;
	double foliage = 0.0;
	double minerals = 0.0;
	double water = 0.0;
	double gases = 0.0;
	double temperature = 0.0;
	double population = 0.0;
	bool ring = false;
	std::vector<double> vMoons;
};

class cStarSystem
{
public:
	cStarSystem(uint32_t x, uint32_t y, bool bGenerateFullSystem = false)
	{
		// Set seed based on location of star system
		nProcGen = (x & 0xFFFF) << 16 | (y & 0xFFFF);

		// Not all locations contain a system
		starExists = (rndInt(0, 20) == 1);
		if (!starExists) return;

		// Generate Star
		starDiameter = rndDouble(10.0, 40.0);
		starColour = g_starColours[rndInt(0, 8)];
		

		}
	

	~cStarSystem()
	{

	}

public:
	std::vector<sPlanet> vPlanets;

public:
	bool		 starExists = false;
	double		 starDiameter = 0.0f;
	WattyColor starColour = Color::white;

private:
	uint32_t nProcGen = 0;

	double rndDouble(double min, double max)
	{
		return ((double)rnd() / (double)(0x7FFFFFFF)) * (max - min) + min;
	}

	int rndInt(int min, int max)
	{
		return (rnd() % (max - min)) + min;
	}

	uint32_t rnd()
	{
		nProcGen += 0xe120fc15;
		uint64_t tmp;
		tmp = (uint64_t)nProcGen * 0x4a39b70d;
		uint32_t m1 = (tmp >> 32) ^ tmp;
		tmp = (uint64_t)m1 * 0x12fad5c9;
		uint32_t m2 = (tmp >> 32) ^ tmp;
		return m2;
	}
};




class SpaceGameApplication : public LETC
{
	private:
		Window* m_window;
		Ship* player;

		float playerSpeed = 2.0f;

		Camera* sceneCamera;


		glm::vec2 vGalaxyOffset = { 0,0 };
		bool bStarSelected = false;
		uint32_t nSelectedStarSeed1 = 0;
		uint32_t nSelectedStarSeed2 = 0;

	public:
		SpaceGameApplication() {}
		~SpaceGameApplication() {}

	private:

		virtual void init() override
		{
			RawResources::Init();
			RawWattyResources::fonts_arial_ttf;
			glm::vec2 screenSize(1600,900);
			m_window = createWindow("Space", screenSize.x, screenSize.y, false, false);
			m_window->setVSync(true);



			glClearColor(0.001f, 0.001f, 0.04f, 1);
			std::vector<bool> stars = std::vector<bool>(); // TODO no
			//Layer* backgroundLayer = new Layer("Background Layer",new SpaceRenderer(stars,screenSize), new Shader());
			Layer* backgroundLayer = new Layer("Background Layer");
			Layer* mainLayer = new Layer("Main Layer");
			layers.push_back(backgroundLayer);
			layers.push_back(mainLayer);

			GameObject* background = new GameObject(glm::vec3(-150.0f,-150.0f,0.0f), glm::vec2(300, 300), new Sprite(new Texture(BACKGROUNDTEXTUREPATH)));
			backgroundLayer->add(background);
			player = new Ship();
			player->transform->setPosition(glm::vec3(0,0,0));
			glm::vec2 playerSize = glm::vec2(1, 1);
			player->transform->setSize(playerSize);
			player->addComponent(new Sprite(new Texture(SHIPTEXTUREPATH)));
			player->addComponent(new PhysicsBody2D(BodyShapes::box,
				{ player->transform->getPosition().x, player->transform->getPosition().y },
				playerSize.x,playerSize.y,
				b2_dynamicBody));

			mainLayer->add(player);

			//sceneCamera = new Camera(&layers, { player->transform->getPosition().x,player->transform->getPosition().y,0 }, glm::vec2(32, 18), 20, CameraMode::orthographic);
			sceneCamera = new Camera(&layers, { player->transform->getPosition().x,player->transform->getPosition().y,0 }, glm::vec2(32, 18), 20, CameraMode::orthographic);
		}

		void update() override {
			getInput();
			PhysicsWorld2D::step(gameTimer->delta);
			LETC::update();
			moveCamera();


			//if (m_window->keyIsDown(GLFW_KEY_W)) vGalaxyOffset.y -= 50.0f * gameTimer->elapsed();
			//if (m_window->keyIsDown(GLFW_KEY_A)) vGalaxyOffset.y += 50.0f * gameTimer->elapsed();
			//if (m_window->keyIsDown(GLFW_KEY_S)) vGalaxyOffset.x -= 50.0f * gameTimer->elapsed();
			//if (m_window->keyIsDown(GLFW_KEY_D)) vGalaxyOffset.x += 50.0f * gameTimer->elapsed();

		}

		void render() override {

			int nSectorsX = m_window->getWidth() / 16;
			int nSectorsY = m_window->getHeight() / 16;
			double mouseX, mouseY;

			m_window->getMousePos(mouseX, mouseY);

			glm::vec2 mouse = glm::vec2(mouseX / 16, mouseY / 16);
			glm::vec2 galaxy_mouse = mouse + vGalaxyOffset;
			glm::vec2 screen_sector = { 0,0 };

			

			for (screen_sector.x = -nSectorsX/2; screen_sector.x < nSectorsX/2; screen_sector.x++)
				for (screen_sector.y = -nSectorsY/2; screen_sector.y < nSectorsY/2; screen_sector.y++)
				{
				//	uint32_t seed1 = (uint32_t)vGalaxyOffset.x + (uint32_t)screen_sector.x;
				//	uint32_t seed2 = (uint32_t)vGalaxyOffset.y + (uint32_t)screen_sector.y;
					uint32_t seed1 = (uint32_t)(sceneCamera->position.x*2.0f)+ (uint32_t)screen_sector.x;
					uint32_t seed2 = (uint32_t)(sceneCamera->position.y*2.0f) + (uint32_t)screen_sector.y;

					cStarSystem star(seed1, seed2);
					if (star.starExists)
					{
						glColor4ubv((GLubyte*)&star.starColour);

						//if (mouse.x == screen_sector.x && mouse.y == screen_sector.y) {
						//	//DrawCircle(screen_sector.x * 16 + 8, screen_sector.y * 16 + 8, 12, olc::YELLOW);
						//	glColor3f(1, 0, 1);
						//}
						glPointSize((int)star.starDiameter / 8);
						glBegin(GL_POINTS);
						float f = (screen_sector.x * 16 + 8 - 0);
						float newX = 2 * ((screen_sector.x * 16 + 8 - 0) / 264) - 1;
						float newY = 2 * ((screen_sector.y * 16 + 8 - 0) / 264) - 1;
						glVertex2f(newX, newY);

						glEnd();

					}
				}

			LETC::render();
		}

		void tick() override {
			LETC::tick();
		}

		void moveCamera() {
			glm::vec3 difference = glm::vec3(
				sceneCamera->position.x - player->transform->getPosition().x,
				sceneCamera->position.y - player->transform->getPosition().y,
				sceneCamera->position.z);

			float distance = sqrt(
				pow(difference.x, 2.0f) +
				pow(difference.y, 2.0f) +
				pow(difference.z, 2.0f));

			//if (distance > 20) {
			//	sceneCamera->position.x = player->position.x + difference.x;
			//	sceneCamera->position.y = player->position.y + difference.y;
			//}
			//else if (distance > 12) {
			//	sceneCamera->position.x = lerp(sceneCamera->position.x, player->position.x, gameTimer->delta * distance*distance);
			//	sceneCamera->position.y = lerp(sceneCamera->position.y, player->position.y, gameTimer->delta * distance*distance);

			//}else if (distance > 5) {
			//sceneCamera->position.x = lerp(sceneCamera->position.x, player->position.x, gameTimer->delta * 1.0f);
			//sceneCamera->position.y = lerp(sceneCamera->position.y, player->position.y, gameTimer->delta * 1.0f);
			//	
			//}else {
			//sceneCamera->position.x = lerp(sceneCamera->position.x, player->position.x, gameTimer->delta * 0.3f);
			//sceneCamera->position.y = lerp(sceneCamera->position.y, player->position.y, gameTimer->delta * 0.3f);
			//	
			//}

			sceneCamera->position.x = lerp(sceneCamera->position.x, player->transform->getPosition().x, gameTimer->delta * distance*distance);
			sceneCamera->position.y = lerp(sceneCamera->position.y, player->transform->getPosition().y, gameTimer->delta * distance*distance);
		}

		void getInput() {
			// PLAYER
			float rotation = -.01 * (float)(m_window->keyIsDown(GLFW_KEY_A) || m_window->keyIsDown(GLFW_KEY_LEFT)) + .01f*(float)(m_window->keyIsDown(GLFW_KEY_D) || m_window->keyIsDown(GLFW_KEY_RIGHT));
			float vertical = -1 *(float)(m_window->keyIsDown(GLFW_KEY_W) || m_window->keyIsDown(GLFW_KEY_UP));
		
			glm::vec2 thrust = glm::vec2();
			thrust.x = sin(player->getPhysicsBody2D()->getBody()->GetAngle());
			thrust.y = -cos(player->getPhysicsBody2D()->getBody()->GetAngle());

			player->getPhysicsBody2D()->getBody()->ApplyAngularImpulse(-rotation, true);
			player->getPhysicsBody2D()->addImpulse(thrust, vertical * playerSpeed * gameTimer->delta);

			if (vertical > 0.1f || vertical < -0.1f)
				player->transform->getChild(0)->setSize(glm::vec2(.5,.5));
			else
				player->transform->getChild(0)->setSize(glm::vec2());

		}

		float lerp(float a, float b, float f)
		{
			return a + f * (b - a);
		}


};


int main() {
	SpaceGameApplication app;
	app.start();
	return 0;
}

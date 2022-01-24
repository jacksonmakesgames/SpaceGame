
#include <Watty.h>
//#include <Ship.h>
#include <Player.h>
#include <Projectile.h>
#include <SpaceRenderer.h>
#include <res.h>
#include <math.h>
#include <cmath>


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


class SpaceGameApplication : public LETC
{
	private:
		Player* player;
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
			glm::vec2 screenSize(1600,900);

			window->setTitle("Space");
			window->setSize(screenSize);
			window->setVSync(true);

			glClearColor(0.001f, 0.001f, 0.04f, 1);

			Layer* backgroundLayer = new Layer("Background Layer");
			Layer* mainLayer = new Layer("Main Layer");
			
			GameObject* background = new GameObject(glm::vec2(0.0f), glm::vec2(100,100), new Sprite(new Texture(BACKGROUNDTEXTUREPATH)));
			backgroundLayer->add(background);
			
			player = new Player();
			mainLayer->add(player);

			sceneCamera = new Camera(&Layer::allLayers, { player->transform->getPosition().x,player->transform->getPosition().y,0 }, glm::vec2(32, 18), 20, CameraMode::orthographic);
		}

		void update() override {
			PhysicsWorld2D::step(Timer::delta);
			LETC::update();
			//moveCamera();
		}


		void OnGui() override{
			ImGui::Begin("Debug info");
			b2Vec2 velocity = player->getPhysicsBody2D()->getBody()->GetLinearVelocity();
			ImGui::LabelText("u/s", "%f, %f | %f",velocity.x, velocity.y, velocity.Length());
			ImGui::End();
		}

		void render() override {
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

	
			sceneCamera->position.x = lerp(sceneCamera->position.x, player->transform->getPosition().x, Timer::delta * distance*distance);
			sceneCamera->position.y = lerp(sceneCamera->position.y, player->transform->getPosition().y, Timer::delta * distance*distance);
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

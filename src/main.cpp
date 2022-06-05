
#include <Watty.h>
#include <audio/audiomanager.h>
//#include <Ship.h>
#include <Player.h>
#include <Projectile.h>
#include <SpaceRenderer.h>
#include <res.h>
#include <math.h>
#include <cmath>

#define BACKGROUND_TEXTURE_PATH "textures/Background.png"
#define VERT_PATH "shaders/basic.vert"
#define FRAG_LIT_PATH "shaders/basic_lit.frag"
#define FRAG_UNLIT_PATH "shaders/basic_unlit.frag"
#define STARS_VERT_PATH "shaders/stars.vert"
#define STARS_FRAG_PATH "shaders/stars.frag"
#define MUSIC_PATH "sounds/sci_fi.ogg"

#include <random>

using namespace watty;
using namespace graphics;
using namespace math;
using namespace physics;
using namespace audio;


namespace watty {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, 0.0f));

	}
}


class SpaceGameApplication : public WattyEngine
{
	private:
		Player* player;
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
			RawResources::Init(); // TODO 

			glm::vec2 screenSize(1600,900);
			window->setTitle("Space");
			window->setSize(screenSize);
			window->setVSync(true);

			float arenaSize = 30.0f;

			new graphics::GridLayer(*sceneCamera, *window);

			sceneCamera->setClearColor(WattyColor(0.001f, 0.001f, 0.04f, 1));

			Shader* starShader = new Shader(STARS_VERT_PATH, STARS_FRAG_PATH);
			BatchRenderer2D* starRenderer = new BatchRenderer2D(starShader);
			starRenderer->init(); // TODO I hate this

			Layer* backgroundLayer = new Layer("Background Layer", starRenderer);
			Layer* mainLayer = new Layer("Main Layer");

			Camera* backgroundCamera = new Camera(new std::vector<Layer*>{backgroundLayer}, glm::vec3(0.0f,0.0f,0.0f), arenaSize, 20.0f, CameraMode::orthographic, WattyColor(0.001f, 0.001f, 0.04f, 1));
			Camera* mainCamera = new Camera(new std::vector<Layer*>{mainLayer}, glm::vec3(0.0f,0.0f,0.0f), arenaSize, 20.0f, CameraMode::orthographic, WattyColor(0.001f, 0.001f, 0.04f, 1));
			
			GameObject* background = new GameObject(glm::vec2(0.0f), glm::vec2(arenaSize,arenaSize), new Sprite(new Texture(BACKGROUND_TEXTURE_PATH)));
			backgroundLayer->add(background);
			
			player = new Player();
			mainLayer->add(player);

			// Sound
			AudioManager::addClip("main", MUSIC_PATH);
			AudioManager::getClip("main")->play(true);
			
		}

		void update() override {
			PhysicsWorld2D::step(Timer::delta);
			WattyEngine::update();
			moveCamera();
		}


		void OnGui() override{
			ImGui::Begin("Debug info");
			b2Vec2 velocity = player->getPhysicsBody2D()->getBody()->GetLinearVelocity();
			ImGui::LabelText("u/s", "%f, %f | %f",velocity.x, velocity.y, velocity.Length());
			ImGui::End();
		}

		void render() override {
			WattyEngine::render();
		}

		void tick() override {
			WattyEngine::tick();
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

	
			sceneCamera->position.x = lerp(sceneCamera->position.x, player->transform->getPosition().x, Timer::delta * distance * distance);
			sceneCamera->position.y = lerp(sceneCamera->position.y, player->transform->getPosition().y, Timer::delta * distance * distance);
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

#include "Test.h"
#include "Utils.h"
#include "VectorDrawer.h"

using namespace BGE;

Test::Test(void)
{
	theta = 0;
}

bool Test::Initialise()
{
	horseFactory = make_shared<HorseFactory>(dynamicsWorld);

	physicsFactory->CreateGroundPhysics();
	dynamicsWorld->setGravity(GLToBtVector(gravity));

	horse = horseFactory->CreateHorse(glm::vec3(0, 0, 0), glm::angleAxis(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));

	//cylinder = physicsFactory->CreateCylinder(5.0f, 2.0f, glm::vec3(0, 0, 0), glm::quat(), false, true);

	physicsFactory->CreateWall(glm::vec3(-50.0f, 0, -20.0f), 20.0f, 3.0f, 5.0f, 5.0f, 5.0f);


	Game::Initialise();

	//camera->transform->position = glm::vec3(-100.0f, 20.0f, 0);
	//camera->transform->Yaw(-90.0f);

	//physicsFactory->CreateCameraPhysics();

	UpdateCamera();

	return true;
}

void Test::Update(float timeDelta)
{
	const Uint8 * keyState = Game::Instance()->GetKeyState();
	
	if (keyState[SDL_SCANCODE_UP])
	{
		horse->push();
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		horse->pull();
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		horse->getBody()->rigidBody->applyTorque(GLToBtVector(horse->getBody()->transform->look * -10000.0f));;
	}

	if (keyState[SDL_SCANCODE_RIGHT])
	{
		horse->getBody()->rigidBody->applyTorque(GLToBtVector(horse->getBody()->transform->look * 10000.0f));;
	}

	if (keyState[SDL_SCANCODE_SPACE])
	{
		horse->getBody()->rigidBody->applyForce(GLToBtVector(glm::vec3(0.0f, 1.0f, 0.0f) * 10000.0f), GLToBtVector(glm::vec3(0, 5.0f, 0)));
	}

	if (keyState[SDL_SCANCODE_PAGEUP])
	{
		horse->rotateLeft();
	}

	if (keyState[SDL_SCANCODE_PAGEDOWN])
	{
		horse->rotateRight();
	}

	if (keyState[SDL_SCANCODE_R]) {
		isWalk = true;
	}

	if (keyState[SDL_SCANCODE_P]) {
		isWalk = false;
	}

	if (isWalk) {
		theta += timeDelta * 5;
		horse->Walk(theta);
		horse->getBody()->rigidBody->applyForce(GLToBtVector(horse->getBody()->transform->up * 2000.0f), GLToBtVector(glm::vec3(0, 0, 0)));

		if (glm::sin(theta) > 0) {
			horse->pull();
		}

		else if (glm::sin(theta) < 0) {
			//horse->push();
		}
	}


	//box->rigidBody->applyForce(GLToBtVector(box_force), btVector3(0.0f, 0.0f, 0.0f));

	//cylinder->rigidBody->applyTorque(GLToBtVector(cylinder->transform->up * 100.0f));

	//UpdateCamera();

	Game::Update(timeDelta);

}

void Test::UpdateCamera() {
	camera->transform->position = horse->getBody()->transform->position + horse->getBody()->transform->look * (-80.0f) + glm::vec3(0, 5.0f, 0);
	camera->transform->orientation = horse->getBody()->transform->orientation;
}
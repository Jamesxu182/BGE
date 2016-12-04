#include "Test.h"
#include "Utils.h"
#include "VectorDrawer.h"

using namespace BGE;

Test::Test(void)
{
	;
}

bool Test::Initialise()
{
	physicsFactory->CreateGroundPhysics();
	dynamicsWorld->setGravity(GLToBtVector(glm::vec3(0, -9.8f, 0)));

	box = physicsFactory->CreateBox(5.0f, 5.0f, 5.0f, glm::vec3(0, 2.5f, 0), glm::quat(), true, true);
	box->Attach(make_shared<VectorDrawer>());

	box->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(box->transform->orientation * glm::angleAxis(- 90.0f, box->transform->up))), GLToBtVector(box->transform->position)));

	physicsFactory->CreateWall(glm::vec3(50.0f, 0, 0.0f), 30.0f, 5.0f, 5.0f, 5.0f, 5.0f);

	Game::Initialise();

	//camera->transform->position = glm::vec3(-20.0f, 20.0f, 0);
	//camera->transform->Yaw(-90.0f);

	UpdateCamera();

	return true;
}

void Test::Update(float timeDelta)
{
	const Uint8 * keyState = Game::Instance()->GetKeyState();
	
	if (keyState[SDL_SCANCODE_UP])
	{
		box->motionState->setWorldTransform(btTransform(GLToBtQuat(box->transform->orientation), GLToBtVector(box->transform->position + timeDelta * box->transform->look * 10.0f)));
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		box->motionState->setWorldTransform(btTransform(GLToBtQuat(box->transform->orientation), GLToBtVector(box->transform->position - timeDelta * box->transform->look * 10.0f)));
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		box->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(box->transform->orientation * glm::angleAxis(timeDelta * 100.0f, box->transform->up))), GLToBtVector(box->transform->position)));
	}

	if (keyState[SDL_SCANCODE_RIGHT])
	{
		box->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(box->transform->orientation * glm::angleAxis(-timeDelta * 100.0f, box->transform->up))), GLToBtVector(box->transform->position)));
	}

	UpdateCamera();

	Game::Update(timeDelta);
}

void Test::UpdateCamera() {
	camera->transform->position = box->transform->position + box->transform->look * (-20.0f) + glm::vec3(0, 5.0f, 0);
	camera->transform->orientation = box->transform->orientation;
}

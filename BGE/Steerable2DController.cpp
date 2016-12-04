#include "Steerable2DController.h"

using namespace std;
using namespace BGE;

BGE::Steerable2DController::Steerable2DController()
{
	mass = 0;
	frictionRate = 0.3f;
}

BGE::Steerable2DController::Steerable2DController(float mass)
{
	this->mass = mass;
	frictionRate = 0.3f;
}

void BGE::Steerable2DController::Update(float timeDelta)
{
	const Uint8 * keyState = Game::Instance()->GetKeyState();

	if (keyState[SDL_SCANCODE_UP]) {
		addForce(5.0f * transform->look);
	}

	if (keyState[SDL_SCANCODE_DOWN]) {
		addForce(5.0f * (-1.0f) * transform->look);
	}

	if (keyState[SDL_SCANCODE_LEFT]) {
		addForce(5.0f * (-1.0f) * transform->right);
	}

	if (keyState[SDL_SCANCODE_RIGHT]) {
		addForce(5.0f * transform->right);
	}
	
	// calculate the friction
	if (glm::length(transform->velocity) == 0) {
		friction = glm::vec3(0, 0, 0);
	}

	else {
		friction = frictionRate * mass * glm::normalize(transform->velocity) * (-1.0f);
	}

	addForce(friction);

	acceleration = force * mass;
	transform->position += transform->velocity * timeDelta + 0.5f * acceleration * glm::pow(timeDelta, 2.0f);
	transform->velocity += acceleration * timeDelta;

	//reset
	force = glm::vec3(0, 0, 0);

	GameComponent::Update(timeDelta);
}

void BGE::Steerable2DController::addForce(glm::vec3 force)
{
	this->force += force;
}

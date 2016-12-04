#include "GravityController.h"

using namespace std;
using namespace BGE;

GravityController::GravityController() : GameComponent() {
	gravity = glm::vec3(0, -9.8f, 0);
}

void GravityController::Update(float timeDelta) {
	if (transform->position.y > 5) {
		transform->position += transform->velocity * timeDelta + 0.5f * gravity * glm::pow(timeDelta, 2.0f);
		transform->velocity += timeDelta * gravity;
	}

	else {
		transform->position.y = 5.0f;
		transform->velocity.y = (-0.5f) * transform->velocity.y;
		transform->position += transform->velocity * timeDelta + 0.5f * gravity * glm::pow(timeDelta, 2.0f);
		transform->velocity += timeDelta * gravity;
	}

}
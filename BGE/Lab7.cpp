#include "Lab7.h"
#include "Sphere.h"
#include "Box.h"
#include "GravityController.h"

bool BGE::Lab7::Initialise()
{
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);

	sphere = make_shared<Sphere>(5);
	sphere->transform->position = glm::vec3(10, 40, 10);
	sphere->Attach(make_shared<GravityController>());
	Attach(sphere);

	box = make_shared<Box>(5, 5, 5);
	box->transform->position = glm::vec3(20, 40, 20);
	box->Attach(make_shared<GravityController>());
	Attach(box);

	Game::Initialise();

	camera->transform->position = glm::vec3(0, 4, 20);

	return true;
}

void BGE::Lab7::Update(float timeDelta)
{
	Game::Update(timeDelta);
}

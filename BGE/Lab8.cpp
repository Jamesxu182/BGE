#include "Lab8.h"
#include "Sphere.h"
#include "Box.h"
#include "GravityController.h"
#include "Steerable2DController.h"
#include "Steerable3DController.h"
#include "Model.h"
#include "Content.h"


bool BGE::Lab8::Initialise()
{
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);

	box = make_shared<Box>(5, 5, 5);
	box->transform->position = glm::vec3(0, 10, 0);
	box->Attach(make_shared<GravityController>());
	//box->Attach(make_shared<Steerable2DController>(10));
	//box->Attach(make_shared<Steerable3DController>(Content::LoadModel("python")));
	Attach(box);

	Game::Initialise();

	camera->transform->position = glm::vec3(0, 4, 20);


	return true;
}

void BGE::Lab8::Update(float timeDelta)
{
	Game::Update(timeDelta);

	PrintFloat("Velocity: ", box->transform->velocity.y);
	PrintFloat("Height: ", box->transform->position.y);
}

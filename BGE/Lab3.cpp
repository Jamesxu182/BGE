#include "Lab3.h"
#include "Content.h"
#include "VectorDrawer.h"
#include "LazerBeam.h"

using namespace BGE;

Lab3::Lab3(void)
{
	elapsed = 10000;
}


bool Lab3::Initialise()
{
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);	

	ship1 = make_shared<GameComponent>(true);
	ship1->Attach(Content::LoadModel("cobramk3", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0,1,0))));
	ship1->Attach(make_shared<VectorDrawer>(glm::vec3(5,5,5)));
	ship1->transform->position = glm::vec3(-10, 2, -10);
	Attach(ship1);

	ship2 = make_shared<GameComponent>(true);
	ship2->Attach(Content::LoadModel("python", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0,1,0))));
	ship2->Attach(make_shared<VectorDrawer>(glm::vec3(5,5,5)));
	ship2->transform->position = glm::vec3(10, 2, -10);
	Attach(ship2);
	Game::Initialise();

	camera->transform->position = glm::vec3(0, 4, 20);
	return true;
}

void Lab3::Update(float timeDelta)
{
	static float timeToFire = 1.0f / 2.0f;

	// Movement of ship2
	if (keyState[SDL_SCANCODE_UP])
	{
		ship2->transform->position += ship2->transform->look * speed * timeDelta;
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		ship2->transform->position -= ship2->transform->look * speed * timeDelta;
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		ship2->transform->Yaw(1);
	}

	if (keyState[SDL_SCANCODE_RIGHT])
	{
		ship2->transform->Yaw(-1);
	}

	// Movement of ship1
	if (keyState[SDL_SCANCODE_U])
	{
		ship1->transform->position += ship1->transform->look * speed * timeDelta;
	}

	if (keyState[SDL_SCANCODE_J])
	{
		ship1->transform->position -= ship1->transform->look * speed * timeDelta;
	}

	if (keyState[SDL_SCANCODE_H])
	{
		ship1->transform->Yaw(1);
	}

	if (keyState[SDL_SCANCODE_K])
	{
		ship1->transform->Yaw(-1);
	}

	if (glm::distance(ship1->transform->position, ship2->transform->position) < 5)
	{
		PrintText("In Range");
	}

	else
	{
		PrintText("Not in range");
	}

	if (glm::degrees(glm::dot(ship1->transform->look, ship2->transform->position - ship1->transform->position)) > 0)
	{
		PrintText("In front");
	}

	else
	{
		PrintText("Behind");
	}

	if (glm::degrees(glm::acos(glm::dot(ship1->transform->look, ship2->transform->position - ship1->transform->position) / glm::length(ship2->transform->position - ship1->transform->position))) < 22.5)
	{
		PrintText("Inside FOV");

		if (elapsed >= timeToFire)
		{
			shared_ptr<LazerBeam> lazer = make_shared<LazerBeam>();
			lazer->transform->look = (ship2->transform->position - ship1->transform->position) / glm::distance(ship2->transform->position, ship1->transform->position);
			lazer->transform->position = ship1->transform->position;
			Attach(lazer);

			cout << "Lazer" << endl;

			elapsed = 0;
		}

	}

	else
	{
		PrintText("Outsides FOV");
	}

	elapsed += timeDelta;

	PrintFloat("Elapsed: ", elapsed);


	Game::Update(timeDelta);
}

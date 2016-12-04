#include "Lab4.h"
#include "Content.h"
#include "VectorDrawer.h"
#include "LazerBeam.h"
#include "FountainEffect.h"

using namespace BGE;

Lab4::Lab4(void)
{
	elapsed = 0;
}

bool Lab4::Initialise()
{
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);

	ship1 = make_shared<GameComponent>(true);
	ship1->Attach(Content::LoadModel("cobramk3", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0, 1, 0))));
	ship1->transform->position = glm::vec3(-10, 2, -10);
	ship1->Attach(make_shared<VectorDrawer>());
	Attach(ship1);

	ship2 = make_shared<GameComponent>(true);
	ship2->Attach(Content::LoadModel("ferdelance", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0, 1, 0))));
	ship2->Attach(make_shared<VectorDrawer>());
	ship2->transform->diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
	ship2->transform->specular  = glm::vec3(1.2f, 1.2f, 1.2f);

	ship2->transform->position = glm::vec3(10, 2, -10);
	Attach(ship2);

	// 500 in the constructor indicates the number of particles in the effect. 
	// You may need to compile in release mode or reduce the number of particles to get an acceptable framerate
	shared_ptr<FountainEffect> centFountain = make_shared<FountainEffect>(500, true);
	centFountain->transform->position.x = centFountain->transform->position.y = 0;
	centFountain->transform->position.y = FOUNTAIN_HEIGHT;
	centFountain->transform->diffuse = glm::vec3(1, 1, 0); // Sets the colour of the fountain

	Attach(centFountain);

	// make a circle of fountains

	fountainTheta = 0.0f;
	float fountainDelta = 2 * glm::pi<float>() / NUM_FOUNTAINS;
	float radius = 30;

	for (int i = 0; i < NUM_FOUNTAINS; i++)
	{
		shared_ptr<FountainEffect> fountain = make_shared<FountainEffect>(500, true);

		fountain->transform->position.x = ship1->transform->position.x + radius * glm::cos(fountainTheta);
		fountain->transform->position.y = FOUNTAIN_HEIGHT;
		fountain->transform->position.z = ship1->transform->position.y + radius * glm::sin(fountainTheta);

		if (i % 2 == 0)
		{	
			fountain->transform->diffuse = glm::vec3(1, 0, 0);
		}
		
		else
		{
			fountain->transform->diffuse = glm::vec3(0, 1, 0);
		}

		Attach(fountain);
		fountains.push_back(fountain);

		fountainTheta += fountainDelta;
	}

	Game::Initialise();

	camera->transform->position = glm::vec3(0, 4, 20);
	return true;
}

void Lab4::Update(float timeDelta)
{
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
		ship2->transform->Yaw(timeDelta * speed * speed);
	}
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		ship2->transform->Yaw(-timeDelta * speed * speed);
	}

	// Put code in here to control the height of the fountains....
	// Use fountainTheta

	for (int i = 0; i < fountains.size(); i++)
	{
		if (i % 2 == 0)
		{
			fountains[i]->transform->position.y = 0.5f * FOUNTAIN_HEIGHT + 0.5f * FOUNTAIN_HEIGHT * glm::sin(elapsed);
		}

		else
		{
			fountains[i]->transform->position.y = 0.5f * FOUNTAIN_HEIGHT - 0.5f * FOUNTAIN_HEIGHT * glm::sin(elapsed);
		}
	}

	fountainTheta += timeDelta;
	if (fountainTheta >= glm::pi<float>() * 2.0f)
	{
		fountainTheta = 0.0f;
	}

	Game::Update(timeDelta);

	// Put your code here to calculate the world transform matrix for ship1
	// You need to include the rotation bit
	ship1->transform->world = glm::translate(glm::mat4(1), ship1->transform->position);

	float theta = 0.0f;
	theta = glm::acos(glm::dot(glm::normalize(ship2->transform->position - ship1->transform->position), ship1->transform->look));

	PrintFloat("Theta: ", theta);


	//PrintFloat("Length: ", glm::length(glm::normalize(glm::cross(ship2->transform->position - ship1->transform->position, ship1->transform->look)) + ship1->transform->up));
	if (glm::cross(ship2->transform->position - ship1->transform->position, ship1->transform->look).y > 0)
	{
		theta = -theta;
	}

	glm::mat4 ship1_translation_mat = glm::translate(glm::mat4(1), ship1->transform->position);
	glm::mat4 ship1_rotation_mat = glm::rotate(glm::mat4(1), glm::degrees(theta), ship1->transform->up);

	ship1->transform->world = ship1_translation_mat * ship1_rotation_mat;

	PrintVector("Look: ", ship1->transform->look);

	elapsed += timeDelta;

	PrintFloat("Elapsed: ", elapsed);

}

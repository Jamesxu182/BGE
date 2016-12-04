#include "Lab6.h"
#include "Content.h"
#include "VectorDrawer.h"
#include "LazerBeam.h"
#include "FountainEffect.h"
#include "Utils.h"



using namespace BGE;

Lab6::Lab6(void)
{
	elapsed = 10000;
	turnRate = glm::half_pi<float>(); // Turn half_pi radians per second
	j_elapsed = 0.0f
		;
}


Lab6::~Lab6(void)
{
}

bool Lab6::Initialise()
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
	ship2->transform->specular = glm::vec3(1.2f, 1.2f, 1.2f);

	ship2->transform->position = glm::vec3(10, 2, -10);
	Attach(ship2);

	slerping = true;

	/***********************************/
	glm::vec3 vec2ship2 = glm::normalize(ship2->transform->position - ship1->transform->position);
	startQuaternion = ship1->transform->orientation;
	float cos = glm::dot(ship1->transform->look, vec2ship2);
	if (cos < -1)
	{
		cos = -1;
	}
	else if (cos > 1){
		cos = 1;
	}
	float degree = glm::degrees(glm::acos(cos));
	glm::vec3 axis = glm::normalize(glm::cross(ship1->transform->look, vec2ship2));
	glm::quat rotation = glm::angleAxis(degree, axis);
	endQuaternion = glm::normalize(rotation * ship1->transform->orientation);
	/***********************************/

	/***********************************/
	/* 10 degree pre second */
	turnRate = 50;
	/***********************************/

	time = degree / turnRate;

	t = 0.0f;

	Game::Initialise();

	camera->transform->position = glm::vec3(0, 4, 20);
	return true;
}

void Lab6::Update(float deltaTime)
{

	// Movement of ship2
	if (keyState[SDL_SCANCODE_UP])
	{
		ship2->transform->Walk(speed * deltaTime);
	}
	if (keyState[SDL_SCANCODE_DOWN])
	{
		ship2->transform->Walk(-speed * deltaTime);
	}
	if (keyState[SDL_SCANCODE_LEFT])
	{
		ship2->transform->Yaw(deltaTime * speed * speed);
	}
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		ship2->transform->Yaw(-deltaTime * speed * speed);
	}

	if (keyState[SDL_SCANCODE_O])
	{
		ship2->transform->Fly(deltaTime * speed);
	}

	if (keyState[SDL_SCANCODE_L])
	{
		ship2->transform->Fly(-deltaTime * speed);
	}

	// Your code goes here...

	if (keyState[SDL_SCANCODE_J])
	{
		j_elapsed += deltaTime;
		ship2->transform->Jump(10, deltaTime, j_elapsed);
	}

	// continue uncomplete 
	else if (j_elapsed != 0.0f) {
		j_elapsed += deltaTime;
		ship2->transform->Jump(10, deltaTime, j_elapsed);
	}

	if (keyState[SDL_SCANCODE_SPACE]) {
		glm::vec3 vec2ship2 = glm::normalize(ship2->transform->position - ship1->transform->position);
		startQuaternion = ship1->transform->orientation;
		float cos = glm::dot(ship1->transform->look, vec2ship2);
		if (cos < -1)
		{
			cos = -1;
		}
		else if (cos > 1) {
			cos = 1;
		}
		float degree = glm::degrees(glm::acos(cos));
		glm::vec3 axis = glm::normalize(glm::cross(ship1->transform->look, vec2ship2));
		glm::quat rotation = glm::angleAxis(degree, axis);
		endQuaternion = glm::normalize(rotation * ship1->transform->orientation);
		time = degree / turnRate;

		t = 0.0f;

		slerping = true;

	}

	if (slerping == true) {
		t += deltaTime / time;
	}

	if (t > 1.0f && slerping == true) {
		slerping = false;
		t = 1.0f; 
	}

	glm::quat orientation = glm::normalize(glm::mix(startQuaternion, endQuaternion, t));
	ship1->transform->orientation = orientation;

	PrintFloat("Time: ", time);

	Game::Update(deltaTime);

}

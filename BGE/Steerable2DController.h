#pragma once
#include "GameComponent.h"
#include "Model.h"

using namespace std;
namespace BGE {
	class Steerable2DController :
		public GameComponent
	{
	private:
	public :
		Steerable2DController();
		Steerable2DController(float mass);

		void Update(float timeDelta);
		void addForce(glm::vec3 force);

		float mass;
		float frictionRate;

		glm::vec3 friction;
		glm::vec3 velocity;
		glm::vec3 force;
		glm::vec3 acceleration;
	};
}
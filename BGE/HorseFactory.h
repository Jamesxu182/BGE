#pragma once
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include "GameComponent.h"
#include "Horse.h"

using namespace std;

namespace BGE {

	class HorseFactory
	{
	public:
		HorseFactory(btDiscreteDynamicsWorld * dynamicsWorld);
		~HorseFactory();

		shared_ptr<Horse> CreateHorse(glm::vec3 position, glm::quat orientation);

		shared_ptr<PhysicsController> CreateHorseBody(glm::vec3 position, glm::quat orientation);
		void CreateHorseFrontLegs(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation);
		void CreateHorseTailLegs(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation);

	private:
		//Horse horse;
		btDiscreteDynamicsWorld * dynamicsWorld;
		shared_ptr<PhysicsFactory> physicsFactory;

		shared_ptr<Horse> horse;
	};
}


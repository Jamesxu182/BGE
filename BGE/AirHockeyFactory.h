#pragma once
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include "GameComponent.h"

using namespace std;

namespace BGE
{
	class AirHockeyFactory
	{
	public:
		AirHockeyFactory(btDiscreteDynamicsWorld * dynamicsWorld);
		~AirHockeyFactory(void);

		shared_ptr<PhysicsController> CreateMallet(glm::vec3 position, glm::quat orientation, shared_ptr<PhysicsController> & box, shared_ptr<PhysicsController> & cylinder);
		shared_ptr<PhysicsController> CreatePuck(float radius, float height, glm::vec3 pos, glm::quat quat, bool kinematic, bool attachToGame);
		void CreateWall();

	private:
		btDiscreteDynamicsWorld * dynamicsWorld;
		shared_ptr<PhysicsFactory> physicsFactory;

	};
}


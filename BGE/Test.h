#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "HorseFactory.h"

using namespace std;

namespace BGE {
	class Test :
		public Game
	{
	public:
		Test(void);

		bool Initialise();
		void Update(float timeDelta);

		void UpdateCamera();

	private:
		shared_ptr<HorseFactory> horseFactory;
		shared_ptr<PhysicsController> box;

		glm::vec3 box_force = glm::vec3(0.0f, 0.0f, 0.0f);

		shared_ptr<Horse> horse;

		shared_ptr<PhysicsController> cylinder;

		const glm::vec3 gravity = glm::vec3(0, -50.0f, 0);

		bool isWalk = true;

		float theta;
	};
}
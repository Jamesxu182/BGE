#pragma once
#include "Game.h"
#include "GameComponent.h"

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
		shared_ptr<PhysicsController> box;
	};
}
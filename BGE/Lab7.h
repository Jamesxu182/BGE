#pragma once
#include "Game.h"

using namespace std;
namespace BGE {
	class Lab7 :
		public Game
	{
	public:
		shared_ptr<GameComponent> sphere;
		shared_ptr<GameComponent> box;

		bool Initialise();
		void Update(float timeDelta);
	};
}

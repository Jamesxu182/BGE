#pragma once
#include "Game.h"

using namespace std;
namespace BGE {
	class Lab8 :
		public Game
	{
	public:
		shared_ptr<GameComponent> box;

		bool Initialise();
		void Update(float timeDelta);
	};
}
#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "FountainEffect.h"

using namespace std;

namespace BGE
{
	class Lab6 :
		public Game
	{
	public:
		Lab6(void);
		~Lab6(void);

		shared_ptr<GameComponent> ship1;
		shared_ptr<GameComponent> ship2;
		float turnRate;
		float toRotate;
		float elapsed;
		bool Initialise();
		void Update(float deltaTime);
		bool slerping;
		glm::quat startQuaternion;
		glm::quat endQuaternion;
		float t;
		float time;

		float j_elapsed;
	};
}
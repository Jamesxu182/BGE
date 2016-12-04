#pragma once
#include "GameComponent.h"

using namespace std;
namespace BGE {
	class GravityController :
		public GameComponent
	{
	private:
	public:
		GravityController();

		void Update(float timeDelta);

		glm::vec3 gravity;

	};
}
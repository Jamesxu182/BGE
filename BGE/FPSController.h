#pragma once
#include "GameComponent.h"

namespace BGE
{
	class FPSController:public GameComponent
	{

	private:
		const float gravity = 9.8f;
	public:
		FPSController(void);
		~FPSController(void);
		void Update(float timeDelta);
		bool FPSController::Initialise();
	};
}

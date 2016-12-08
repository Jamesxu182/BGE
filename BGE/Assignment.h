#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "AirHockeyFactory.h"

using namespace std;

namespace BGE {
	class Assignment :
		public Game
	{
	public:
		Assignment(void);

		bool Initialise();
		void Update(float timeDelta);

		void UpdateCamera();
		void ResetGame();

	private: 
		shared_ptr<PhysicsController> mallet1_box;
		shared_ptr<PhysicsController> mallet2_box;
		shared_ptr<PhysicsController> mallet1_cylinder;
		shared_ptr<PhysicsController> mallet2_cylinder;

		shared_ptr<PhysicsController> puck;

		shared_ptr<AirHockeyFactory> airHockeyFactory;

		glm::quat player1_init_orientation;
		glm::quat player2_init_orientation;

		const float speed = 40.0f;
		const float turnRate = 200.0f;
		
		const glm::vec3 grivity = glm::vec3(0, -200.0f, 0);

		btTransform mallet1_box_trans;
		btTransform mallet1_cylinder_trans;
		btTransform mallet2_box_trans;
		btTransform mallet2_cylinder_trans;
	};
}
#pragma once
#include "PhysicsController.h"

using namespace std;

namespace BGE {

	class Horse
	{
	public:
		Horse();

		void setFrontLeftThigh(shared_ptr<PhysicsController> front_left_thigh);
		void setFrontRightThigh(shared_ptr<PhysicsController> front_right_thigh);

		void setTailLeftThigh(shared_ptr<PhysicsController> tail_left_thigh);
		void setTailRightThigh(shared_ptr<PhysicsController> tail_right_thigh);

		void setFrontLeftLeg(shared_ptr<PhysicsController> front_left_leg);
		void setFrontRightLeg(shared_ptr<PhysicsController> front_right_leg);

		void setTailLeftLeg(shared_ptr<PhysicsController> tail_left_leg);
		void setTailRightLeg(shared_ptr<PhysicsController> tail_right_leg);

		void setBody(shared_ptr<PhysicsController> body);

		shared_ptr<PhysicsController> getBody();

		void push();
		void pull();

		void rotateLeft();
		void rotateRight();

		void Walk(float theta);

		~Horse();

	private:
		shared_ptr<PhysicsController> front_left_thigh;
		shared_ptr<PhysicsController> front_left_leg;

		shared_ptr<PhysicsController> front_right_thigh;
		shared_ptr<PhysicsController> front_right_leg;

		shared_ptr<PhysicsController> tail_left_thigh;
		shared_ptr<PhysicsController> tail_left_leg;

		shared_ptr<PhysicsController> tail_right_thigh;
		shared_ptr<PhysicsController> tail_right_leg;

		shared_ptr<PhysicsController> body;
	};
}


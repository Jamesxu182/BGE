#include "Assignment.h"
#include "Cylinder.h"
#include "Box.h"
#include "VectorDrawer.h"
#include "Utils.h"

using namespace BGE;

Assignment::Assignment(void) {
	;
}

bool Assignment::Initialise() {
	// Create Ground
	physicsFactory->CreateGroundPhysics();

	//set gravity
	dynamicsWorld->setGravity(GLToBtVector(grivity));

	// Create air hockey factory
	airHockeyFactory = make_shared<AirHockeyFactory>(dynamicsWorld);

	// create two mallets
	shared_ptr<PhysicsController> player_1 = airHockeyFactory->CreateMallet(glm::vec3(-50.0f, 0.0f, 0), glm::angleAxis(-90.0f, glm::vec3(0, 1, 0)), mallet1_box, mallet1_cylinder);
	shared_ptr<PhysicsController> player_2 = airHockeyFactory->CreateMallet(glm::vec3(50.0f, 0.0f, 0), glm::angleAxis(90.0f, glm::vec3(0, 1, 0)), mallet2_box, mallet2_cylinder);
	
	// get two player
	player_1->rigidBody->getMotionState()->getWorldTransform(mallet1_box_trans);
	player_2->rigidBody->getMotionState()->getWorldTransform(mallet2_box_trans);

	//player1_init_orientation = player_1->transform->orientation * glm::angleAxis(-90.0f, glm::vec3(0, 1, 0));
	//player2_init_orientation = player_2->transform->orientation * glm::angleAxis(90.0f, glm::vec3(0, 1, 0));

	// get init orientation
	player1_init_orientation = BtToGLQuat(mallet1_box_trans.getRotation());;
	player2_init_orientation = BtToGLQuat(mallet2_box_trans.getRotation());;

	// create wall
	airHockeyFactory->CreateWall();

	puck = airHockeyFactory->CreatePuck(7.0f, 2.0f, glm::vec3(0, 0, 0), glm::quat(), false, true);
	
	Game::Initialise();

	// Init camera
	camera->transform->position = glm::vec3(0, 150, 0);
	camera->transform->Pitch(-89.99f);

	//UpdateCamera();

	return true;
}

void Assignment::Update(float timeDelta) {
	
	// Get world transform from player1 and player2
	mallet1_box->rigidBody->getMotionState()->getWorldTransform(mallet1_box_trans);
	mallet1_cylinder->rigidBody->getMotionState()->getWorldTransform(mallet1_cylinder_trans);
	mallet2_box->rigidBody->getMotionState()->getWorldTransform(mallet2_box_trans);
	mallet2_cylinder->rigidBody->getMotionState()->getWorldTransform(mallet2_cylinder_trans);

	// Get orientation and position from world transform
	glm::quat mallet1_box_orientation = BtToGLQuat(mallet1_box_trans.getRotation());
	glm::vec3 mallet1_box_position = BtToGLVector(mallet1_box_trans.getOrigin());

	glm::quat mallet1_cylinder_orientation = BtToGLQuat(mallet1_cylinder_trans.getRotation());
	glm::vec3 mallet1_cylinder_position = BtToGLVector(mallet1_cylinder_trans.getOrigin());

	glm::quat mallet2_box_orientation = BtToGLQuat(mallet2_box_trans.getRotation());
	glm::vec3 mallet2_box_position = BtToGLVector(mallet2_box_trans.getOrigin());

	glm::quat mallet2_cylinder_orientation = BtToGLQuat(mallet2_cylinder_trans.getRotation());
	glm::vec3 mallet2_cylinder_position = BtToGLVector(mallet2_cylinder_trans.getOrigin());

	const Uint8 * keyState = Game::Instance()->GetKeyState();

	// Player1 Controller
	if (keyState[SDL_SCANCODE_UP])
	{
		//mallet1_box->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet1_box->transform->orientation), GLToBtVector(mallet1_box->transform->position + timeDelta * mallet1_box->transform->look * speed)));
		//mallet1_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet1_box->transform->orientation), GLToBtVector(mallet1_cylinder->transform->position + timeDelta * mallet1_box->transform->look * speed)));
		mallet1_box_position += timeDelta * mallet1_box->transform->look * speed;
		mallet1_cylinder_position += timeDelta * mallet1_cylinder->transform->look * speed;
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		//mallet1_box->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet1_box->transform->orientation), GLToBtVector(mallet1_box->transform->position - timeDelta * mallet1_box->transform->look * speed)));
		//mallet1_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet1_box->transform->orientation), GLToBtVector(mallet1_cylinder->transform->position - timeDelta * mallet1_box->transform->look * speed)));
		mallet1_box_position -= timeDelta * mallet1_box->transform->look * speed;
		mallet1_cylinder_position -= timeDelta * mallet1_cylinder->transform->look * speed;
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		//mallet1_box->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(mallet1_box->transform->orientation * glm::angleAxis(timeDelta * 100.0f, mallet1_box->transform->up))), GLToBtVector(mallet1_box->transform->position)));
		//mallet1_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(mallet1_cylinder->transform->orientation * glm::angleAxis(timeDelta * 100.0f, mallet1_cylinder->transform->up))), GLToBtVector(mallet1_cylinder->transform->position)));
		mallet1_box_orientation = glm::normalize(mallet1_box_orientation * glm::angleAxis(timeDelta * turnRate, mallet1_cylinder->transform->up));
		mallet1_cylinder_orientation = glm::normalize(mallet1_cylinder_orientation * glm::angleAxis(timeDelta * turnRate, mallet1_cylinder->transform->up));
	}

	if (keyState[SDL_SCANCODE_RIGHT])
	{
		//mallet1_box->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(mallet1_box->transform->orientation * glm::angleAxis(-timeDelta * 100.0f, mallet1_box->transform->up))), GLToBtVector(mallet1_box->transform->position)));
		//mallet1_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(mallet1_cylinder->transform->orientation * glm::angleAxis(-timeDelta * 100.0f, mallet1_cylinder->transform->up))), GLToBtVector(mallet1_cylinder->transform->position)));
		mallet1_box_orientation = glm::normalize(mallet1_box_orientation * glm::angleAxis(-timeDelta * turnRate, mallet1_cylinder->transform->up));
		mallet1_cylinder_orientation = glm::normalize(mallet1_cylinder_orientation * glm::angleAxis(-timeDelta * turnRate, mallet1_cylinder->transform->up));
	}

	// Update player 1 world transform
	mallet1_box->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet1_box_orientation), GLToBtVector(mallet1_box_position)));
	mallet1_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet1_cylinder_orientation), GLToBtVector(mallet1_cylinder_position)));

	// Player2 Controller
	if (keyState[SDL_SCANCODE_U])
	{
		//mallet2_box->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet2_box->transform->orientation), GLToBtVector(mallet2_box->transform->position + timeDelta * mallet2_box->transform->look * speed)));
		//mallet2_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet2_box->transform->orientation), GLToBtVector(mallet2_cylinder->transform->position + timeDelta * mallet2_box->transform->look * speed)));
		mallet2_box_position += timeDelta * mallet2_box->transform->look * speed;
		mallet2_cylinder_position += timeDelta * mallet2_cylinder->transform->look * speed;
	}

	if (keyState[SDL_SCANCODE_J])
	{
		//mallet2_box->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet2_box->transform->orientation), GLToBtVector(mallet2_box->transform->position - timeDelta * mallet2_box->transform->look * speed)));
		//mallet2_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet2_box->transform->orientation), GLToBtVector(mallet2_cylinder->transform->position - timeDelta * mallet2_box->transform->look * speed)));
		mallet2_box_position -= timeDelta * mallet2_box->transform->look * speed;
		mallet2_cylinder_position -= timeDelta * mallet2_cylinder->transform->look * speed;
	}

	if (keyState[SDL_SCANCODE_H])
	{
		//mallet2_box->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(mallet2_box->transform->orientation * glm::angleAxis(timeDelta * 100.0f, mallet2_box->transform->up))), GLToBtVector(mallet2_box->transform->position)));
		//mallet2_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(mallet2_cylinder->transform->orientation * glm::angleAxis(timeDelta * 100.0f, mallet2_cylinder->transform->up))), GLToBtVector(mallet2_cylinder->transform->position)));
		mallet2_box_orientation = glm::normalize(mallet2_box_orientation * glm::angleAxis(timeDelta * turnRate, mallet2_cylinder->transform->up));
		mallet2_cylinder_orientation = glm::normalize(mallet2_cylinder_orientation * glm::angleAxis(timeDelta * turnRate, mallet2_cylinder->transform->up));
	}

	if (keyState[SDL_SCANCODE_K])
	{
		//mallet2_box->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(mallet2_box->transform->orientation * glm::angleAxis(-timeDelta * 100.0f, mallet2_box->transform->up))), GLToBtVector(mallet2_box->transform->position)));
		//mallet2_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(glm::normalize(mallet2_cylinder->transform->orientation * glm::angleAxis(-timeDelta * 100.0f, mallet2_cylinder->transform->up))), GLToBtVector(mallet2_cylinder->transform->position)));
		mallet2_box_orientation = glm::normalize(mallet2_box_orientation * glm::angleAxis(-timeDelta * turnRate, mallet2_cylinder->transform->up));
		mallet2_cylinder_orientation = glm::normalize(mallet2_cylinder_orientation * glm::angleAxis(-timeDelta * turnRate, mallet2_cylinder->transform->up));
	}

	// Update player21 world transform
	mallet2_box->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet2_box_orientation), GLToBtVector(mallet2_box_position)));
	mallet2_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(mallet2_cylinder_orientation), GLToBtVector(mallet2_cylinder_position)));

	// If out of border, the game will be resetted
	if (puck->transform->position.x > 75 || puck->transform->position.x < -75 || puck->transform->position.z > 50 || puck->transform->position.z < -50) {
		ResetGame();
	}

	// Press R to restart game
	if (keyState[SDL_SCANCODE_R])
	{
		ResetGame();
	}

	//PrintVector("Velocity: ", puck->transform->velocity);

	//UpdateCamera();
	Game::Update(timeDelta);
}

void Assignment::UpdateCamera() {
	camera->transform->position = mallet1_box->transform->position + mallet1_box->transform->look * (-40.0f) + glm::vec3(0, 5.0f, 0);
	camera->transform->orientation = mallet1_box->transform->orientation;
}

void Assignment::ResetGame() {
	// reset puck position to the center of table
	PrintText("Reset Game.");

	// reset puck
	puck->rigidBody->setWorldTransform(btTransform(GLToBtQuat(puck->transform->orientation), GLToBtVector(glm::vec3(0.0f, 0.0f, 0.0f))));
	puck->rigidBody->clearForces();
	puck->rigidBody->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));

	// reset players
	mallet1_box->motionState->setWorldTransform(btTransform(GLToBtQuat(player1_init_orientation), GLToBtVector(glm::vec3(-50.0f, 4.0f, 0.0f))));
	mallet1_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(player1_init_orientation), GLToBtVector(glm::vec3(-50.0f, 0.0f, 0.0f))));

	mallet2_box->motionState->setWorldTransform(btTransform(GLToBtQuat(player2_init_orientation), GLToBtVector(glm::vec3(50.0f, 4.0f, 0.0f))));
	mallet2_cylinder->motionState->setWorldTransform(btTransform(GLToBtQuat(player2_init_orientation), GLToBtVector(glm::vec3(50.0f, 0.0f, 0.0f))));

	puck->Cleanup();
}



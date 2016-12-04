#include "AirHockeyFactory.h"
#include "VectorDrawer.h"
#include "Game.h"
#include "Cylinder.h"
#include "Utils.h"

using namespace BGE;

AirHockeyFactory::AirHockeyFactory(btDiscreteDynamicsWorld * dynamicsWorld)
{
	this->dynamicsWorld = dynamicsWorld;
	physicsFactory = make_shared<PhysicsFactory>(dynamicsWorld);
}


AirHockeyFactory::~AirHockeyFactory()
{
	;
}

shared_ptr<PhysicsController> AirHockeyFactory::CreateMallet(glm::vec3 position, glm::quat orientation, shared_ptr<PhysicsController> & box, shared_ptr<PhysicsController> & cylinder)
{
	box = physicsFactory->CreateBox(5.0f, 5.0f, 5.0f, position + glm::vec3(0, 4.0f, 0), orientation, true, true);
	cylinder = physicsFactory->CreateCylinder(7.0f, 3.0f, position, orientation, true, true);
	btHingeConstraint * hinge = new btHingeConstraint(*box->rigidBody, *cylinder->rigidBody, btVector3(0, -2.5f, 0), btVector3(0, 1.0f, 0), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
	dynamicsWorld->addConstraint(hinge);

	box->Attach(make_shared<VectorDrawer>());
	cylinder->Attach(make_shared<VectorDrawer>());

	return box;
}

shared_ptr<PhysicsController> AirHockeyFactory::CreatePuck(float radius, float height, glm::vec3 pos, glm::quat quat, bool kinematic, bool attachToGame)
{
	shared_ptr<PhysicsController> puck = physicsFactory->CreateCylinder(radius, height, pos, quat, kinematic, attachToGame);

	puck->rigidBody->setFriction(0);

	return puck;
}

void AirHockeyFactory::CreateWall() {
	physicsFactory->CreateBox(150.0f, 10.0f, 5.0f, glm::vec3(0.0f, 2.5f, -50.0f), glm::quat(), true, true);
	physicsFactory->CreateBox(150.0f, 10.0f, 5.0f, glm::vec3(0.0f, 2.5f, 50.0f), glm::quat(), true, true);

	physicsFactory->CreateBox(5.0f, 10.0f, 35.0f, glm::vec3(75.0f, 2.5f, 30.0f), glm::quat(), true, true);
	physicsFactory->CreateBox(5.0f, 10.0f, 35.0f, glm::vec3(75.0f, 2.5f, -30.0f), glm::quat(), true, true);

	physicsFactory->CreateBox(5.0f, 10.0f, 35.0f, glm::vec3(-75.0f, 2.5f, 30.0f), glm::quat(), true, true);
	physicsFactory->CreateBox(5.0f, 10.0f, 35.0f, glm::vec3(-75.0f, 2.5f, -30.0f), glm::quat(), true, true);
}

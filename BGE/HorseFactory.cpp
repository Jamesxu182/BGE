#include "HorseFactory.h"
#include "VectorDrawer.h"
#include "Utils.h"

using namespace BGE;

HorseFactory::HorseFactory(btDiscreteDynamicsWorld * dynamicsWorld)
{
	this->dynamicsWorld = dynamicsWorld;
	physicsFactory = make_shared<PhysicsFactory>(dynamicsWorld);

	horse = make_shared<Horse>();
}


HorseFactory::~HorseFactory()
{
	;
}

shared_ptr<Horse>  HorseFactory::CreateHorse(glm::vec3 position, glm::quat orientation)
{
	shared_ptr<PhysicsController> body = CreateHorseBody(position, orientation);

	CreateHorseFrontLegs(body, position, orientation);
	CreateHorseTailLegs(body, position, orientation);

	return horse;
}

shared_ptr<PhysicsController> HorseFactory::CreateHorseBody(glm::vec3 position, glm::quat orientation)
{
	shared_ptr<PhysicsController> body = physicsFactory->CreateCylinder(5.0f, 20.0f, position + glm::vec3(0.0f, 10.0f, 0.0f), orientation, false, true);
	shared_ptr<PhysicsController> head = physicsFactory->CreateSphere(5.0f, position + glm::vec3(0.0f, 21.0f, -10.0f), glm::quat(), false, true);

	btPoint2PointConstraint * left_thigh_to_joint = new btPoint2PointConstraint(*body->rigidBody, *head->rigidBody, btVector3(0.0f, 10.0f, 0.0f), btVector3(0.0f, 0.0f, 5.0f));
	dynamicsWorld->addConstraint(left_thigh_to_joint);

	body->Attach(make_shared<VectorDrawer>());

	horse->setBody(body);

	return body;
}

void HorseFactory::CreateHorseFrontLegs(shared_ptr<PhysicsController>body, glm::vec3 position, glm::quat orientation)
{
	shared_ptr<PhysicsController> left_thigh = physicsFactory->CreateBox(2.0f, 4.0f, 2.0f, position + glm::vec3(-6.0f, 10.0f, -7.0f), glm::quat(), false, true);
	shared_ptr<PhysicsController> left_joint = physicsFactory->CreateSphere(1.0f, position + glm::vec3(-6.0f, 7.0f, -7.0f), glm::quat(), false, true);
	shared_ptr<PhysicsController> left_leg = physicsFactory->CreateBox(2.0f, 6.0f, 2.0f, position + glm::vec3(-6.0f, 3.0f, -7.0f), glm::quat(), false, true);
	
	btHingeConstraint * left_mid_hinge = new btHingeConstraint(*left_thigh->rigidBody, *left_leg->rigidBody, btVector3(0, -3.0f, 0), btVector3(0, 4.0f, 0), GLToBtVector(left_thigh->transform->right), GLToBtVector(left_leg->transform->right), true);
	left_mid_hinge->setLimit(0.0f, 0.5f);
	dynamicsWorld->addConstraint(left_mid_hinge);

	btPoint2PointConstraint * left_thigh_to_joint = new btPoint2PointConstraint(*left_thigh->rigidBody, *left_joint->rigidBody, btVector3(0, -2.0f, 0), btVector3(0, 1.0f, 0));
	dynamicsWorld->addConstraint(left_thigh_to_joint);

	btHingeConstraint * left_top_hinge = new btHingeConstraint(*body->rigidBody, *left_thigh->rigidBody, btVector3(-5.0f, 7.0f, 0), btVector3(1.0f, 2.0f, 0), GLToBtVector(left_thigh->transform->right), GLToBtVector(left_thigh->transform->right), true);
	left_top_hinge->setLimit(1.8f, 2.0f);
	dynamicsWorld->addConstraint(left_top_hinge);

	shared_ptr<PhysicsController> right_thigh = physicsFactory->CreateBox(2.0f, 4.0f, 2.0f, position + glm::vec3(6.0f, 10.0f, -7.0f), glm::quat(), false, true);
	shared_ptr<PhysicsController> right_joint = physicsFactory->CreateSphere(1.0f, position + glm::vec3(6.0f, 7.0f, -7.0f), glm::quat(), false, true);
	shared_ptr<PhysicsController> right_leg = physicsFactory->CreateBox(2.0f, 6.0f, 2.0f, position + glm::vec3(6.0f, 3.0f, -7.0f), glm::quat(), false, true);

	btHingeConstraint * right_mid_hinge = new btHingeConstraint(*right_thigh->rigidBody, *right_leg->rigidBody, btVector3(0, -3.0f, 0), btVector3(0, 4.0f, 0), GLToBtVector(right_thigh->transform->right), GLToBtVector(right_leg->transform->right), true);
	right_mid_hinge->setLimit(0.0f, 0.5f);
	dynamicsWorld->addConstraint(right_mid_hinge);

	btPoint2PointConstraint * right_thigh_to_joint = new btPoint2PointConstraint(*right_thigh->rigidBody, *right_joint->rigidBody, btVector3(0, -2.0f, 0), btVector3(0, 1.0f, 0));
	dynamicsWorld->addConstraint(right_thigh_to_joint);

	btHingeConstraint * right_top_hinge = new btHingeConstraint(*body->rigidBody, *right_thigh->rigidBody, btVector3(5.0f, 7.0f, 0), btVector3(-1.0f, 2.0f, 0), GLToBtVector(right_thigh->transform->right), GLToBtVector(right_thigh->transform->right), true);
	right_top_hinge->setLimit(1.8f, 2.0f);
	dynamicsWorld->addConstraint(right_top_hinge);

	//shared_ptr<PhysicsController> right_thigh = physicsFactory->CreateBox(2.0f, 2.0f, 10.0f, position + glm::vec3(2.5f, 0.0f, -7.0f), orientation, false, true);

	//left_thigh->Attach(make_shared<VectorDrawer>());
	left_leg->Attach(make_shared<VectorDrawer>());

	//right_thigh->Attach(make_shared<VectorDrawer>());

	horse->setFrontLeftThigh(left_thigh);
	horse->setFrontLeftLeg(left_leg);
	horse->setFrontRightThigh(right_thigh);
	horse->setFrontRightLeg(right_leg);

}

void BGE::HorseFactory::CreateHorseTailLegs(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation)
{
	shared_ptr<PhysicsController> left_thigh = physicsFactory->CreateBox(2.0f, 4.0f, 4.0f, position + glm::vec3(-6.0f, 10.0f, 8.0f), glm::quat(), false, true);
	shared_ptr<PhysicsController> left_joint = physicsFactory->CreateSphere(2.0f, position + glm::vec3(-6.0f, 6.0f, 8.0f), glm::quat(), false, true); 
	shared_ptr<PhysicsController> left_leg = physicsFactory->CreateBox(2.0f, 4.0f, 2.0f, position + glm::vec3(-6.0f, 2.0f, 8.0f), glm::quat(), false, true);

	btHingeConstraint * left_mid_hinge = new btHingeConstraint(*left_thigh->rigidBody, *left_leg->rigidBody, btVector3(0, -4.0f, 0), btVector3(0, 4.0f, 0), GLToBtVector(left_thigh->transform->right), GLToBtVector(left_leg->transform->right), true);
	left_mid_hinge->setLimit(0, 1.0f);
	dynamicsWorld->addConstraint(left_mid_hinge);

	btPoint2PointConstraint * left_thigh_to_joint = new btPoint2PointConstraint(*left_thigh->rigidBody, *left_joint->rigidBody, btVector3(0, -2.0f, 0), btVector3(0, 2.0f, 0));
	dynamicsWorld->addConstraint(left_thigh_to_joint);

	btHingeConstraint * left_top_hinge = new btHingeConstraint(*body->rigidBody, *left_thigh->rigidBody, btVector3(-5.0f, -8.0f, 0), btVector3(1.0f, 2.0f, 0), GLToBtVector(left_thigh->transform->right), GLToBtVector(left_thigh->transform->right), true);
	left_top_hinge->setLimit(1.0f, 1.57f);
	dynamicsWorld->addConstraint(left_top_hinge);

	shared_ptr<PhysicsController> right_thigh = physicsFactory->CreateBox(2.0f, 4.0f, 4.0f, position + glm::vec3(6.0f, 10.0f, 8.0f), glm::quat(), false, true);
	shared_ptr<PhysicsController> right_joint = physicsFactory->CreateSphere(2.0f, position + glm::vec3(6.0f, 6.0f, 8.0f), glm::quat(), false, true);
	shared_ptr<PhysicsController> right_leg = physicsFactory->CreateBox(2.0f, 4.0f, 2.0f, position + glm::vec3(6.0f, 2.0f, 8.0f), glm::quat(), false, true);

	btHingeConstraint * right_mid_hinge = new btHingeConstraint(*right_thigh->rigidBody, *right_leg->rigidBody, btVector3(0, -4.0f, 0), btVector3(0, 4.0f, 0), GLToBtVector(right_thigh->transform->right), GLToBtVector(left_leg->transform->right), true);
	right_mid_hinge->setLimit(0, 1.0f);
	dynamicsWorld->addConstraint(right_mid_hinge);


	btPoint2PointConstraint * right_thigh_to_joint = new btPoint2PointConstraint(*right_thigh->rigidBody, *right_joint->rigidBody, btVector3(0, -2.0f, 0), btVector3(0, 2.0f, 0));
	dynamicsWorld->addConstraint(right_thigh_to_joint);

	btHingeConstraint * right_top_hinge = new btHingeConstraint(*body->rigidBody, *right_thigh->rigidBody, btVector3(5.0f, -8.0f, 0), btVector3(-1.0f, 2.0f, 0), GLToBtVector(right_thigh->transform->right), GLToBtVector(right_thigh->transform->right), true);
	right_top_hinge->setLimit(1.0f, 1.57f);
	dynamicsWorld->addConstraint(right_top_hinge);

	horse->setTailLeftThigh(left_leg);
	horse->setTailLeftLeg(left_leg);
	horse->setTailRightThigh(right_thigh);
	horse->setTailRightLeg(right_leg);
}
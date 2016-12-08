#include "Horse.h"
#include "Utils.h"

using namespace BGE;

Horse::Horse()
{
	;
}

void BGE::Horse::setFrontLeftThigh(shared_ptr<PhysicsController> front_left_thigh)
{
	this->front_left_thigh = front_left_thigh;
}

void BGE::Horse::setFrontRightThigh(shared_ptr<PhysicsController> front_right_thigh)
{
	this->front_right_thigh = front_right_thigh;
}

void BGE::Horse::setTailLeftThigh(shared_ptr<PhysicsController> tail_left_thigh)
{
	this->tail_left_thigh = tail_left_thigh;
}

void BGE::Horse::setTailRightThigh(shared_ptr<PhysicsController> tail_right_thigh)
{
	this->tail_right_thigh = tail_right_thigh;
}

void BGE::Horse::setFrontLeftLeg(shared_ptr<PhysicsController> front_left_leg)
{
	this->front_left_leg = front_left_leg;
}

void BGE::Horse::setFrontRightLeg(shared_ptr<PhysicsController> front_right_leg)
{
	this->front_right_leg = front_right_leg;
}

void BGE::Horse::setTailLeftLeg(shared_ptr<PhysicsController> tail_left_leg)
{
	this->tail_left_leg = tail_left_leg;
}

void BGE::Horse::setTailRightLeg(shared_ptr<PhysicsController> tail_right_leg)
{
	this->tail_right_leg = tail_right_leg;
}

void BGE::Horse::setBody(shared_ptr<PhysicsController> body)
{
	this->body = body;
}

shared_ptr<PhysicsController> BGE::Horse::getBody()
{
	return body;
}

void BGE::Horse::push() {
	//body->rigidBody->applyForce(GLToBtVector(glm::vec3(0, 1.0f, 0) * 4000.0f), GLToBtVector(glm::vec3(0, 0, 0)));
	//body->rigidBody->applyTorque(GLToBtVector(body->transform->look * 100.0f));
	body->rigidBody->applyTorque(GLToBtVector(body->transform->right * -10000.0f));

}

void BGE::Horse::pull() {
	//body->rigidBody->applyForce(GLToBtVector(glm::vec3(0, 1.0f, 0) * -4000.0f), GLToBtVector(glm::vec3(0, 0, 0)));
	body->rigidBody->applyTorque(GLToBtVector(body->transform->right * 10000.0f));
}

void BGE::Horse::rotateLeft()
{
	body->rigidBody->applyTorque(GLToBtVector(body->transform->up * -40000.0f));
}

void BGE::Horse::rotateRight()
{
	body->rigidBody->applyTorque(GLToBtVector(body->transform->up * 40000.0f));
}

void BGE::Horse::Walk(float theta) {
	front_left_thigh->rigidBody->applyTorque(GLToBtVector(front_left_thigh->transform->right * 30000.0f * sin(theta)));
	front_right_thigh->rigidBody->applyTorque(GLToBtVector(front_right_thigh->transform->right * 30000.0f * sin(theta)));

	tail_left_thigh->rigidBody->applyTorque(GLToBtVector(tail_left_thigh->transform->right * -20000.0f * sin(theta)));
	tail_right_thigh->rigidBody->applyTorque(GLToBtVector(tail_right_thigh->transform->right * -20000.0f * sin(theta)));

}


Horse::~Horse()
{
}

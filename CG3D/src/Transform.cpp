#include "Transform.h"

// Defines
#define GLM_ENABLE_EXPERIMENTAL

// Additional includes
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtx\euler_angles.hpp>

// Namespaces
using namespace cg3d;

glm::mat4 Transform::getModelMatrix()
{
	//create a identity matrix
	glm::mat4 ret = glm::mat4(1);

	//translate the model matrix
	ret = glm::translate(ret, _position);

	//rotate the model matrix
	ret *= glm::eulerAngleXYZ(_rotation.x, _rotation.y, _rotation.z);

	//scale the model matrix
	ret = glm::scale(ret, _scale);

	return ret;
}

glm::vec3 Transform::getPosition()
{
	return _position;
}

void Transform::setPosition(glm::vec3 position)
{
	_position = position;
}

glm::vec3 Transform::getRotation()
{
	return _rotation;
}

void Transform::setRotation(glm::vec3 rotation)
{
	_rotation = rotation;
}

glm::vec3 Transform::getScale()
{
	return _scale;
}

void Transform::setScale(glm::vec3 scale)
{
	_scale = scale;
}
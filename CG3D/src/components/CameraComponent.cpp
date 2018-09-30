#include "components\CameraComponent.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "entities\Entity.h"
#include <GLM\gtc\matrix_transform.hpp>


CameraComponent::CameraComponent()
	: _up({ 0.0f, 1.0f, 0.0f })
	, _front({ 0.0f, 0.0f, 1.0f })
	, _left({ 1.0f, 0.0f, 0.0f })
	, _target({ 0.0f, 0.0f, 0.0f })

	, _fov(-1)
	, _zNear(-1)
	, _zFar(-1)

	, _windowSize(0.0f)
	, _view(1.0f)
	, _proj(1.0f)
	, _frustrumType(FrustrumType::Invalid)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::initialize()
{	
}	 
	 
void CameraComponent::update()
{
	glm::vec3 position = _owner->getTransform()->getPosition();
	_view = glm::lookAt(position, position - _front, _up);
}
	 
void CameraComponent::finalize()
{	 
}	 
	 
void CameraComponent::setProjectionProperties(float fov, float zNear, float zFar, FrustrumType type)
{
	setFov(fov);
	setZNear(zNear);
	setZFar(zFar);
	setFrustrumType(type);
}

void CameraComponent::setFov(float fov)
{
	_fov = fov;
}

float CameraComponent::getFov() const
{
	return _fov;
}

void CameraComponent::setZNear(float zNear)
{
	_zNear = zNear;
}

float CameraComponent::getZNear() const
{
	return _zNear;
}

void CameraComponent::setZFar(float zFar)
{
	_zFar = zFar;
}

float CameraComponent::getZFar() const
{
	return _zFar;
}

void CameraComponent::setWindowSize(glm::vec2 windowSize)
{
	_windowSize = windowSize;
	changeFrustrum();
}

void CameraComponent::setFrustrumType(FrustrumType type)
{
	_frustrumType = type;
	changeFrustrum();
}

FrustrumType CameraComponent::getFrustrumType() const
{
	return _frustrumType;
}

void CameraComponent::changeFrustrum()
{
	if (_frustrumType == FrustrumType::Invalid
		|| glm::length(_windowSize) == 0.0f)
		return;

	if (_frustrumType == FrustrumType::Projection)
	{
		_proj = glm::perspective(glm::radians(_fov), _windowSize.x / _windowSize.y, _zNear, _zFar);
	}
	else
	{
		_proj = glm::ortho(0.0f, _windowSize.x, _windowSize.y, 0.0f, _zNear, _zFar);
	}
}

glm::mat4 CameraComponent::getViewMatrix()
{
	return _view;
}

glm::mat4 CameraComponent::getProjectionMatrix()
{
	return _proj;
}
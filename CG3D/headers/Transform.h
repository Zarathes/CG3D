#pragma once

namespace cg3d
{
	class Transform
	{
	public:
		//create a model matrix from the transform
		//heavier operation than the other ones
		glm::mat4 getModelMatrix();

		//get transform position
		glm::vec3 getPosition();

		//set transform position
		void setPosition(glm::vec3 position);

		//get transform rotation
		glm::vec3 getRotation();

		//set transform rotation
		void setRotation(glm::vec3 rotation);

		//get transform scale
		glm::vec3 getScale();

		//set transform scale
		void setScale(glm::vec3 scale);

	private:
		glm::vec3 _position = { 0.f,0.f,0.f };
		glm::vec3 _rotation = { 0.f,0.f,0.f };
		glm::vec3 _scale = { 1.f,1.f,1.f };
	};
}
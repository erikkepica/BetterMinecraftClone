#include"Transform.h"
#include <glm/gtc/matrix_transform.hpp>

void Transform::AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win)
{
	win.push_back(std::make_unique<DragFloat3ElementInf>(&position[0], "Pos"));
	win.push_back(std::make_unique<DragFloat3ElementRange>(&rotation[0], "Rot", 0, 360));
	win.push_back(std::make_unique<DragFloat3ElementInf>(&scale[0], "Scale"));
}

glm::mat4 Transform::GetModel()
{

	glm::mat4 model(1);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);
	
	return model;
}

glm::mat4 Transform::GetView(glm::vec3 camPos, glm::vec3 camRot)
{
	float yaw = camRot.y - 90.0f; // subtract 90 to fix rotation offset

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(camRot.x));
	direction.y = sin(glm::radians(camRot.x));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(camRot.x));

	return glm::lookAt(camPos, camPos + glm::normalize(direction), glm::vec3(0, 1, 0));
}

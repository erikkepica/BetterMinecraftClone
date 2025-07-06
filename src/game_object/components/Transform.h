#pragma once
#include<glm/glm.hpp>
#include"UIManager.h"
#include<memory>
#include"Component.h"

class Transform : public Component
{
public:
	glm::vec3 position = glm::vec3(0, 0, -5);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	virtual void AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win) override;
	static std::string ID() { return "TRANSFORM"; }
	virtual std::string GetID() override { return ID(); }

	glm::mat4 GetModel();
	glm::mat4 GetView(glm::vec3 camPos, glm::vec3 camRot);
	virtual std::string GetPass() override { return "UPDATE"; }
};
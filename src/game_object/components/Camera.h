#pragma once
#include"Component.h"
#include"Transform.h"
#include<memory>
#include"Application/DataStructs.h"

class Camera : public Component
{
private:
	std::shared_ptr<Transform> m_Transform;
	WindowData m_WinData;
public:
	enum ProjectionType
	{
		perspective,
		ortographic
	};

	ProjectionType projection = ProjectionType::perspective;
	float fov = 70;
	float nearPlane = 0.01f;
	float farPlane = 100.0f;


	Camera(){}
	Camera(std::shared_ptr<Transform> transform, WindowData data);

	void UpdateWindowData(WindowData winData);

	glm::mat4 GetProjection();

	virtual void AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win) override;
	static std::string ID() { return "CAMERA"; }
	virtual std::string GetID() override { return ID(); }
	virtual std::string GetPass() override { return "UPDATE"; }
};
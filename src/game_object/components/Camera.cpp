#include"Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include"Logging.h"

Camera::Camera(std::shared_ptr<Transform> transform, WindowData winData)
	:m_Transform(transform), m_WinData(winData)
{
}

void Camera::UpdateWindowData(WindowData winData)
{
	m_WinData = winData;
}

glm::mat4 Camera::GetProjection()
{
	return	(projection == ProjectionType::perspective) ?
			glm::perspective(fov, (float)m_WinData.width/ (float)m_WinData.height, nearPlane, farPlane) :
			(projection == ProjectionType::ortographic) ?
			glm::ortho(0.0f, (float)m_WinData.width, 0.0f, (float)m_WinData.height,nearPlane, farPlane) :
			glm::mat4(1.0f);
}

void Camera::AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win)
{
	win.push_back(std::make_unique<DragFloat1ElementInf>(&nearPlane, "Near Plane"));
	win.push_back(std::make_unique<DragFloat1ElementInf>(&farPlane, "Far Plane"));

	std::string name("Perspective");
	win.push_back(std::make_unique<DropdownElement>(&projection, name, std::vector<const char*>{"Perspective", "Orthographic"}, (int*)&projection));

	if (projection == ProjectionType::perspective)
	{
		LOG_INFO("Perspective");
		win.push_back(std::make_unique<DragFloat1ElementRange>(&fov, "Fov", 0.01f, 360.0f));
	}
	else if(projection == ProjectionType::ortographic)
	{
		LOG_INFO("Orthographic");
	}
}

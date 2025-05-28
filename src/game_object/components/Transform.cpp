#include"Transform.h"

void Transform::AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win)
{
	win.push_back(std::make_unique<DragFloat3ElementInf>(&position[0], "Pos"));
	win.push_back(std::make_unique<DragFloat3ElementRange>(&rotation[0], "Rot", 0, 360));
	win.push_back(std::make_unique<DragFloat3ElementInf>(&scale[0], "Scale"));
}
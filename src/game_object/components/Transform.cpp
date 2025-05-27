#include"Transform.h"

void Transform::AddDebugToWindow(DebugWindow& win)
{
	win.Push(std::make_unique<DragFloat3ElementInf>(&position[0], "Pos"));
	win.Push(std::make_unique<DragFloat3ElementRange>(&rotation[0], "Rot", 0, 360));
	win.Push(std::make_unique<DragFloat3ElementInf>(&scale[0], "Scale"));
}
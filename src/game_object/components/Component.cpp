#include "Component.h"
#include"Logging.h"

void Component::Update()
{
}

void Component::Start()
{
	LOG_INFO(GetID() << " created!");
}

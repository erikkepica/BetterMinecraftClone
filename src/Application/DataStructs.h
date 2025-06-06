#pragma once
#include<string>

struct WindowData
{
	std::string title;

	int width;
	int height;
};

struct ApplicationData
{
	std::string name;
	WindowData windowData;
};
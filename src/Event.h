#pragma once

class Event
{
public:
	Event()
		:m_Happend(false), m_Inducer(nullptr)
	{}

	void Induce(void* inducer);
	bool Poll();

	void* GetInducer();
private:
	bool m_Happend;
	void* m_Inducer;
};
#include"Event.h"
#include"Logging.h"

void Event::Induce(void* inducer)
{
	m_Happend = true;
	m_Inducer = inducer;
}

bool Event::Poll()
{
	if (m_Happend)
	{
		m_Happend = false;
		return true;
	}
	return false;
}

void* Event::GetInducer()
{
	return m_Inducer;
}

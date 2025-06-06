#include"Model.h"

std::vector<float> Model::GetVertices()
{
	return m_Vertices;
}

std::vector<unsigned int> Model::GetIndices()
{
	return m_Indices;
}

VertexBufferLayout Model::GetAttributes()
{
	return m_Attributes;
}

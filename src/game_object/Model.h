#pragma	 once
#include<vector>
#include"graphics/VertexArrayObject.h"

class Model
{
	Model();

public:
	std::vector<float> GetVertices();
	std::vector<unsigned int> GetIndices();
	VertexBufferLayout GetAttributes();
private:
	std::vector<float> m_Vertices; 
	std::vector<unsigned int> m_Indices;
	VertexBufferLayout m_Attributes;
};
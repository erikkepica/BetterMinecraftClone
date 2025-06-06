#include"Model.h"
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<array>

#include"Logging.h"


Model::Model(VertexBufferLayout attribs)
	:m_Attributes(attribs)
{
}

void Model::LoadOBJ(const char* path)
{
    m_Vertices.clear();
    m_Indices.clear();

    struct Vertex {
        glm::vec3 pos;
        glm::vec2 uv;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec3 bitangent;

        Vertex() = default;
        Vertex(const glm::vec3& pos, const glm::vec2& uv, const glm::vec3& normal)
            : pos(pos), uv(uv), normal(normal),
            tangent(glm::vec3(0.0f)), bitangent(glm::vec3(0.0f)) {}
    };

    auto ParseOBJIndices = [](const std::string& str)->std::array<int, 3> {
        std::array<int, 3> idx = { 0, 0, 0 };
        std::stringstream ss(str);
        std::string val;
        int i = 0;
        while (std::getline(ss, val, '/')) {
            if (!val.empty()) idx[i] = std::stoi(val) - 1; // OBJ is 1-based
            i++;
        }
        return idx;
    };

    std::ifstream file(path);
    if (!file.is_open()) {
        LOG_WARNING("MODEL: Failed to open the specified path: " << path);
        return;
    }

    std::string line;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<std::vector<std::string>> faces;

    std::vector<Vertex> vertexVec;
    std::vector<unsigned int> indices;

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string type;
        stream >> type;

        if (type == "v") {
            float x, y, z;
            stream >> x >> y >> z;
            positions.emplace_back(x, y, z);
        }
        else if (type == "vt") {
            float u, v;
            stream >> u >> v;
            uvs.emplace_back(u, v);
        }
        else if (type == "vn") {
            float x, y, z;
            stream >> x >> y >> z;
            normals.emplace_back(x, y, z);
        }
        else if (type == "f") {
            std::vector<std::string> faceElements;
            std::string token;
            while (stream >> token) {
                faceElements.push_back(token);
            }
            if (faceElements.size() < 3) continue;
            faces.push_back(faceElements);
        }
    }
    unsigned int counter = 0;
    for (const auto& face : faces) {
        std::vector<std::array<int, 3>> idxList;

        if (face.size() == 3) {
            idxList = {
                ParseOBJIndices(face[0]),
                ParseOBJIndices(face[1]),
                ParseOBJIndices(face[2])
            };
        }
        else if (face.size() == 4) {
            idxList = {
                ParseOBJIndices(face[0]),
                ParseOBJIndices(face[1]),
                ParseOBJIndices(face[2]),

                ParseOBJIndices(face[0]),
                ParseOBJIndices(face[2]),
                ParseOBJIndices(face[3])
            };
        }
        else {
            std::cerr << "Warning: Face with " << face.size() << " vertices not supported.\n";
            continue;
        }

        for (size_t i = 0; i < idxList.size(); i += 3) {
            const auto& i0 = idxList[i];
            const auto& i1 = idxList[i + 1];
            const auto& i2 = idxList[i + 2];

            const glm::vec3& pos1 = positions[i0[0]];
            const glm::vec3& pos2 = positions[i1[0]];
            const glm::vec3& pos3 = positions[i2[0]];

            const glm::vec2& uv1 = uvs[i0[1]];
            const glm::vec2& uv2 = uvs[i1[1]];
            const glm::vec2& uv3 = uvs[i2[1]];

            const glm::vec3& norm1 = normals[i0[2]];
            const glm::vec3& norm2 = normals[i1[2]];
            const glm::vec3& norm3 = normals[i2[2]];

            // Calculate tangent and bitangent
            glm::vec3 edge1 = pos2 - pos1;
            glm::vec3 edge2 = pos3 - pos1;
            glm::vec2 deltaUV1 = uv2 - uv1;
            glm::vec2 deltaUV2 = uv3 - uv1;

            float f = (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
            f = (f == 0.0f) ? 1.0f : 1.0f / f;

            glm::vec3 tangent = f * (deltaUV2.y * edge1 - deltaUV1.y * edge2);
            glm::vec3 bitangent = f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2);

            tangent = glm::normalize(tangent);
            bitangent = glm::normalize(bitangent);

            // Create and store 3 vertices
            for (const auto& idx : { i0, i1, i2 }) {
                Vertex v;
                v.pos = positions[idx[0]];
                v.uv = uvs[idx[1]];
                v.normal = normals[idx[2]];
                v.tangent = tangent;
                v.bitangent = bitangent;

                vertexVec.push_back(v);
                indices.push_back(counter++);
            }
        }
    }
    std::vector<float> vertices;
    for (auto vert : vertexVec)
    {
        vertices.push_back(vert.pos.x);
        vertices.push_back(vert.pos.y);
        vertices.push_back(vert.pos.z);

        vertices.push_back(vert.uv.x);
        vertices.push_back(vert.uv.y);

        vertices.push_back(vert.normal.x);
        vertices.push_back(vert.normal.y);
        vertices.push_back(vert.normal.z);

        vertices.push_back(vert.tangent.x);
        vertices.push_back(vert.tangent.y);
        vertices.push_back(vert.tangent.z);

        vertices.push_back(vert.bitangent.x);
        vertices.push_back(vert.bitangent.y);
        vertices.push_back(vert.bitangent.z);
    }
    m_Vertices = vertices;
    m_Indices = indices;

    // Store vertexVec and indices in your model/mesh
    // e.g., this->vertices = vertexVec;
    //       this->indices = indices;
}

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




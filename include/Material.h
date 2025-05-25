#pragma once

#include"Texture.h"
#include"ShaderClass.h"

#include <iostream>
#include <functional>

#include"glm/glm.hpp"

class Material
{

public:
	Shader shader;
	std::vector<Texture> textures;
	Material(){}
	Material(const char* vertexPath, const char* fragmentPath, std::vector<const char*> texs)
	{
		Generate(vertexPath, fragmentPath, texs);
	}
	~Material(){}

	void Generate(const char* vertexPath, const char* fragmentPath, std::vector<const char*> texs)
	{
		shader.Generate(vertexPath, fragmentPath);
		for (auto tex : texs)
		{
			textures.push_back({ tex });
		}
	}


	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	virtual void ConfigureUniforms()
	{
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
	}

	void Use()
	{
		for (auto tex : textures)
			tex.Bind();
		shader.Use();
		ConfigureUniforms();
	}
};



class LitMaterial : public Material
{
public:
	LitMaterial(const char* vertexPath, const char* fragmentPath, std::vector<const char*> texs)
		:Material(vertexPath,fragmentPath,texs)
	{}

	glm::vec4 color;
	glm::vec3 lightColor;
	glm::vec3 lightPos;
	float ambientStrength;
	float lightStrength;
	
	virtual void ConfigureUniforms() override
	{
		Material::ConfigureUniforms();
		shader.SetVec4("col", color);
		shader.SetVec3("lightColor", lightColor);
		shader.SetVec3("lightDir", lightPos);
		shader.SetFloat("ambientStrength", ambientStrength);
		shader.SetFloat("lightStrength", lightStrength);
	}
};
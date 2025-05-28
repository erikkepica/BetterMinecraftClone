#pragma once
#include"Component.h"

#include"graphics/Texture.h"
#include"graphics/ShaderClass.h"

#include <iostream>
#include <functional>
#include<memory>

#include"glm/glm.hpp"

class Material : public Component
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

	void SetupMatricies(glm::mat4 model_, glm::mat4 view_, glm::mat4 projection_)
	{
		model = model_;
		view = view_;
		projection = projection_;
	}

	void Use()
	{
		for (auto tex : textures)
			tex.Bind();
		shader.Use();
		ConfigureUniforms();
	}

	virtual void AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win) override
	{
		win.push_back(std::make_unique<ListOpenGLTextureElements>(textures.data(), "Textures", textures.size()));
	}
	static std::string ID() { return "MATERIAL"; }
	virtual std::string GetID() override { return ID(); }
};



class LitMaterial : public Material
{
public:
	LitMaterial(const char* vertexPath, const char* fragmentPath, std::vector<const char*> texs)
		:Material(vertexPath,fragmentPath,texs)
	{}

	glm::vec4 color = glm::vec4(1);
	glm::vec3 lightColor;
	glm::vec3 lightPos;
	float lightStrength;
	float ambientStrength;
	
	void SetupLighting(glm::vec3 lightColor_, glm::vec3 lightPos_, float lightStrength_, float ambientStrength_)
	{
		lightColor = lightColor_;
		lightPos = lightPos_;
		lightStrength = lightStrength_;
		ambientStrength = ambientStrength_;
	}

	virtual void ConfigureUniforms() override
	{
		Material::ConfigureUniforms();
		shader.SetVec4("col", color);
		shader.SetVec3("lightColor", lightColor);
		shader.SetVec3("lightDir", lightPos);
		shader.SetFloat("ambientStrength", ambientStrength);
		shader.SetFloat("lightStrength", lightStrength);
	}

	virtual void AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win) override
	{
		win.push_back(std::make_unique<ListOpenGLTextureElements>(textures.data(), "Textures", textures.size()));
		win.push_back(std::make_unique<Color4Element>(&color[0], "Color"));
	}
};
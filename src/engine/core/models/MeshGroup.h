#pragma once

#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/postprocess.h>
#include <GLEW/glew.h>
#include <string>
#include <vector>
#include "../engine/core/Texture.h"

struct Mesh {
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
};

class MeshGroup
{
public:
	std::vector<Mesh> m_MeshList;
	std::vector<Texture*> m_TextureList;
	std::vector<unsigned int> m_MeshToTexture;

public:
	void LoadNode(aiNode* node, const aiScene* scene );
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);

	MeshGroup(std::string filepath);
	~MeshGroup();
};


#include "MeshGroup.h"
#include <iostream>

MeshGroup::MeshGroup(std::string filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		filePath, aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_GenSmoothNormals |
		aiProcess_JoinIdenticalVertices
	);

	if (!scene) {
		std::cout << "Failed to load: " << filePath << std::endl;
		std::cout << importer.GetErrorString() << std::endl;
		throw;
	}

	LoadNode(scene->mRootNode, scene);
}

MeshGroup::~MeshGroup()
{
	for (size_t i = 0; i < m_TextureList.size(); i++) {
		delete m_TextureList[i];
		m_TextureList[i] = nullptr;
	}
}


void MeshGroup::LoadNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		// node only stores ID of the mesh, the actual mesh is in the scene object
		unsigned int meshId = node->mMeshes[i];
		LoadMesh(scene->mMeshes[meshId], scene);
	}
}

void MeshGroup::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		vertices.insert(
			vertices.end(),
			{
				mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z // x, y, z
			}
		);

		// if first texture exists
		if (mesh->mTextureCoords[0]) {
			vertices.insert(
				vertices.end(),
				{
					mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, // u, v
				}
			);
		}
		else {
			vertices.insert(
				vertices.end(),
				{
					0, 0, // u, v
				}
			);
		}

		vertices.insert(
			vertices.end(),
			{
				-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z // normal x y z
			}
		);

		m_MeshList.push_back(Mesh{ vertices, indices });
		m_MeshToTexture.push_back(mesh->mMaterialIndex); // stores material index for this mesh
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++) { // each face has 3 index values
		aiFace face = mesh->mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
}

void MeshGroup::LoadMaterials(const aiScene* scene)
{
	m_TextureList.resize(scene->mNumMaterials); // not mNumTextures

	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		aiMaterial* material = scene->mMaterials[i];

		m_TextureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString filePath;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &filePath) == AI_SUCCESS) {
				try {
					// this step deals with absolute file paths for textures in object files
					int slashIdx = std::string(filePath.data).rfind("\\");
					std::string filename = std::string(filePath.data).substr(slashIdx + 1);
					std::string texturePath = std::string("assets/textures/") + filename;
					
					m_TextureList[i] = new Texture(texturePath);
				}
				catch (...) {
					delete m_TextureList[i];
					std::cout << "Failed to load diffuse texture" << std::endl;
				}
			}
		}

		if (!m_TextureList[i])
		{
			m_TextureList[i] = new Texture("assets/textures/defaults/plain.png");
		}
	}
}

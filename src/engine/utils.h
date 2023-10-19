#pragma once

#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak(); // __debugbreak() is a Visual Studio specific function
# define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

/**
 * @brief Populates normals in the gives vertex array, normals must be initialized to 0
 * @tparam T Type of vertex array
 * @param vertices pointer to vertex array
 * @param indices pointer to index array
 * @param layoutCount number of elements in attribute layout
 * @param vertexOffsetCount offset of first vertex element (count)
 * @param normalOffsetCount offset of first normal element (count)
 *
 * @returns pointer to vertex array
*/

template<typename T>
inline T* PopulateNormals(T* vertices, GLuint* indices, unsigned int layoutCount, unsigned int indexCount, unsigned int vertexOffsetCount, unsigned int normalOffsetCount)
{
	for (int idx = 0; idx < indexCount; idx += 3) {
		GLuint index_1 = indices[idx];
		GLuint index_2 = indices[idx + 1];
		GLuint index_3 = indices[idx + 2];

		T vertex_1_x = *(vertices + (layoutCount * index_1) + vertexOffsetCount);
		T vertex_1_y = *(vertices + (layoutCount * index_1) + vertexOffsetCount + 1);
		T vertex_1_z = *(vertices + (layoutCount * index_1) + vertexOffsetCount + 2);

		T vertex_2_x = *(vertices + (layoutCount * index_2) + vertexOffsetCount);
		T vertex_2_y = *(vertices + (layoutCount * index_2) + vertexOffsetCount + 1);
		T vertex_2_z = *(vertices + (layoutCount * index_2) + vertexOffsetCount + 2);

		T vertex_3_x = *(vertices + (layoutCount * index_3) + vertexOffsetCount);
		T vertex_3_y = *(vertices + (layoutCount * index_3) + vertexOffsetCount + 1);
		T vertex_3_z = *(vertices + (layoutCount * index_3) + vertexOffsetCount + 2);

		glm::vec3 line1 = glm::vec3(vertex_1_x, vertex_1_y, vertex_1_z) - glm::vec3(vertex_2_x, vertex_2_y, vertex_2_z);
		glm::vec3 line2 = glm::vec3(vertex_1_x, vertex_1_y, vertex_1_z) - glm::vec3(vertex_3_x, vertex_3_y, vertex_3_z);

		glm::vec3 normal = glm::normalize(glm::cross(line1, line2));

		// vertex at i1
		*(vertices + (layoutCount * index_1) + normalOffsetCount) += normal.x;
		*(vertices + (layoutCount * index_1) + normalOffsetCount + 1) += normal.y;
		*(vertices + (layoutCount * index_1) + normalOffsetCount + 2) += normal.z;

		// vertex at i2
		*(vertices + (layoutCount * index_2) + normalOffsetCount) += normal.x;
		*(vertices + (layoutCount * index_2) + normalOffsetCount + 1) += normal.y;
		*(vertices + (layoutCount * index_2) + normalOffsetCount + 2) += normal.z;

		// vertex at i3
		*(vertices + (layoutCount * index_3) + normalOffsetCount) += normal.x;
		*(vertices + (layoutCount * index_3) + normalOffsetCount + 1) += normal.y;
		*(vertices + (layoutCount * index_3) + normalOffsetCount + 2) += normal.z;
	}

	// TODO: remove redundant computation
	// normalize all normals computed so far
	for (int idx = 0; idx < indexCount; idx += 1) {
		GLuint index = indices[idx];

		glm::vec3 tempVector = glm::normalize(
			glm::vec3(
				*(vertices + (layoutCount * index) + normalOffsetCount),
				*(vertices + (layoutCount * index) + normalOffsetCount + 1),
				*(vertices + (layoutCount * index) + normalOffsetCount + 2)
			)
		);

		*(vertices + (layoutCount * index) + normalOffsetCount) += tempVector.x;
		*(vertices + (layoutCount * index) + normalOffsetCount + 1) += tempVector.y;
		*(vertices + (layoutCount * index) + normalOffsetCount + 2) += tempVector.z;

		std::cout 
			<< *(vertices + (layoutCount * index) + normalOffsetCount) << " | " 
			<< *(vertices + (layoutCount * index) + normalOffsetCount + 1) << " | " 
			<< *(vertices + (layoutCount * index) + normalOffsetCount + 2)
			<< std::endl;
	}

	return vertices;
}




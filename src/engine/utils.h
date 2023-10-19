#pragma once

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#define ASSERT(x) if (!(x)) __debugbreak(); // __debugbreak() is a Visual Studio specific function
# define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

template<typename T>
T& PopulateNormals(T* vertexArray, GLuint* indices, unsigned layoutCount, unsigned vertexOffsetCount, unsigned int normalOffsetCount) {
	unsigned int layoutSize = layoutCount * sizeof(T);

	for (int idx = 0; idx < sizeof(indices) / sizeof(GLuint); idx += 3) {
		/*index_1 = indices[idx];
		index_2 = indices[idx + 1];
		index_3 = indices[idx + 2];

		vertex_1_x = vertexArray + (layoutCount * index_1) + vertexOffsetCount;
		vertex_1_y = vertexArray + (layoutCount * index_1) + vertexOffsetCount + 1;
		vertex_1_z = vertexArray + (layoutCount * index_1) + vertexOffsetCount + 2;

		vertex_2_x = vertexArray + (layoutCount * index_2) + vertexOffsetCount;
		vertex_2_y = vertexArray + (layoutCount * index_2) + vertexOffsetCount + 1;
		vertex_2_z = vertexArray + (layoutCount * index_2) + vertexOffsetCount + 2;

		vertex_3_x = vertexArray + (layoutCount * index_3) + vertexOffsetCount;
		vertex_3_y = vertexArray + (layoutCount * index_3) + vertexOffsetCount + 1;
		vertex_3_z = vertexArray + (layoutCount * index_3) + vertexOffsetCount + 2;

		glm::vec3 line1 = glm::vec3(vertex_1_x, vertex_1_y, vertex_1_z) - glm::vec3(vertex_2_x, vertex_2_y, vertex_2_z);
		glm::vec3 line2 = glm::vec3(vertex_1_x, vertex_1_y, vertex_1_z) - glm::vec3(vertex_3_x, vertex_3_y, vertex_3_z);

		glm::vec3 normal = glm::normalize(glm::cross(line1, line2));*/
	}
}

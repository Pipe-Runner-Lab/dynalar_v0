#include <IMGUI/imgui.h>
#include <GLEW/glew.h>
#include "ClearColor.h"
#include "../engine/utils.h"

namespace scene {
	ClearColor::ClearColor():
		m_ClearColor{0.3f, 0.0f, 0.5f, 1.0f}
	{
	}
	
	void ClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	
	void ClearColor::OnImGUIRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}
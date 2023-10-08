#include "BaseScene.h"

scene::SceneMenu::SceneMenu(BaseScene*& ActiveScenePtr):
	m_ActiveScene(ActiveScenePtr)
{
}

void scene::SceneMenu::OnImGUIRender()
{
	for (auto& scene : m_scenes) {
		if (ImGui::Button(scene.first.c_str())) {
			m_ActiveScene = scene.second();
		}
	}
}

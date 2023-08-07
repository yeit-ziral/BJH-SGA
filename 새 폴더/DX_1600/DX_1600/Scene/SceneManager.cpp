#include "framework.h"
#include "SceneManager.h"

#include "BagicScene/CupHeadScene.h"
#include "BagicScene/MapToolScene.h"
#include "BagicScene/BossRoom.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	//_scenes.push_back(make_shared<CupHeadScene>());

	//_scenes.push_back(make_shared<MapToolScene>());

	_scenes.push_back(make_shared<BossRoom>());
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Update()
{
	_scenes[_curScene]->Update();
}

void SceneManager::Render()
{
	_scenes[_curScene]->Render();
}

void SceneManager::PostRender()
{
	_scenes[_curScene]->PostRender();

	if (ImGui::Button("NextScene", { 130,30 }))
		NextScene();

	if (ImGui::Button("PrevScene", { 130,30 }))
		PrevScene();

	if (ImGui::Button("SetScene", { 130,30 }))
		SetScene(_test);

	ImGui::SliderInt("SetSceneNumber", (int*)&_test, 0, 2);
}

void SceneManager::NextScene()
{
	if (_curScene >= _scenes.size() - 1)
		return;

	_scenes[_curScene]->End();
	++_curScene;
	_scenes[_curScene]->Init();
}

void SceneManager::PrevScene()
{
	if (_curScene <= 0)
		return;

	_scenes[_curScene]->End();
	--_curScene;
	_scenes[_curScene]->Init();
}

void SceneManager::SetScene(int number)
{
	if (number >= _scenes.size() - 1 || number < 0)
		return;

	_scenes[_curScene]->End();
	_curScene = number;
	_scenes[_curScene]->Init();
}

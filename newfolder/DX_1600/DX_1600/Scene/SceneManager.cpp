#include "framework.h"
#include "SceneManager.h"

#include "BagicScene/CupHeadScene.h"
#include "BagicScene/MapToolScene.h"
#include "BagicScene/BossRoom.h"
#include "BagicScene/Lobby.h"
#include "EffectScene.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	_scenes.push_back(make_shared<Lobby>());
	_scenes.push_back(make_shared<CupHeadScene>());
	_scenes.push_back(make_shared<BossRoom>());

	//_scenes.push_back(make_shared<EffectScene>());

	EffectManager::GetInstance()->AddEffect("Exp", L"Resource/exp2.png", Vector2(5, 4), Vector2(150, 150)); // Àâ¸÷ Á×À» ¶§
	EffectManager::GetInstance()->AddEffect("Exp2", L"Resource/explosion.png", Vector2(5, 5), Vector2(150, 150)); // º¸½º Á×À» ¶§, ÀÚÆøº´ ÀÚÆø

	FONT->Add("D2Coding", L"D2Coding");
}

SceneManager::~SceneManager()
{
	FONT->Delete();
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

	//if (ImGui::Button("NextScene", { 130,30 }))
	//	NextScene();

	//if (ImGui::Button("PrevScene", { 130,30 }))
	//	PrevScene();

	//if (ImGui::Button("SetScene", { 130,30 }))
	//	SetScene(_test);

	//ImGui::SliderInt("SetSceneNumber", (int*)&_test, 0, 2);
	ImGui::SliderInt("NowState", (int*)&_curScene, 0, 2);
}

void SceneManager::NextScene()
{

	_scenes[_curScene]->End();
	++_curScene;

	if (_curScene >= _scenes.size())
		//return;
		_curScene = _curScene % _scenes.size();


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

void SceneManager::LobbyScene()
{
	_scenes[_curScene]->End();
	_curScene = 0;

	_scenes[_curScene]->Init();
}

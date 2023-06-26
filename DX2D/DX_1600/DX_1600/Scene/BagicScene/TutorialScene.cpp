#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad1 = make_shared<Quad>(L"Resource/sun.png");
	//_quad1->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));
	_transform1 = make_shared<Transform>();

	_transform1->SetPosition(CENTER);

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->_data.imageSize = _quad1->GetImageSize();
	_filterBuffer->_data.radialCenter = Vector2(0.5f, 0.5f);

	_hpBar = make_shared<HPBar>(L"Resource/UI/Button.png", Vector2(200, 50));
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_transform1->Update();
	_filterBuffer->Update();
	
	_hpBar->Update();
}

void TutorialScene::Render()
{
	_transform1->SetBuffer(0);
	_filterBuffer->SetPSBuffer(0);
	_quad1->Render();
}

void TutorialScene::PostRender()
{
	ImGui::SliderInt("Selected", &_filterBuffer->_data.selected, 0, 10);
	ImGui::SliderInt("value1", &_filterBuffer->_data.value1, 1, 300);
	ImGui::SliderInt("value2", &_filterBuffer->_data.value2, 0, 300);
	ImGui::SliderInt("value3", &_filterBuffer->_data.value3, 0, 300);

	_hpBar->PostRender();
	ImGui::SliderInt("maxHp", &_maxHp, 0, 100);
	ImGui::SliderInt("curHp", &_curHp, 0, 100);
	_hpBar->SetMaxHp(_maxHp);
	_hpBar->SetCurHp(_curHp);
}

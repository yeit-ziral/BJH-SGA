#include "framework.h"
#include "Program.h"

#include "../Scene/TutorialScene.h"
#include "../Scene/SolarSystem.h"
#include "../Scene/DungreedScene.h"
#include "../Scene/ColliderScene.h"

Program::Program()
{
	_curScene = make_shared<ColliderScene>();

	_view = make_shared<MatrixBuffer>();
	_projection = make_shared<MatrixBuffer>();

	XMMATRIX projectM = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);

	_projection->SetData(projectM);

	_view->Update();
	_projection->Update();

	//Timer::GetInstance()->SetLockFPS(60,0);
}

Program::~Program()
{
	
}

void Program::Update()
{
	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();

	_curScene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	_view->SetVSBuffer(1);
	_projection->SetVSBuffer(2);

	// 누끼 딴거 사물만 남기고 배경 지움
	ALPHA->SetState();
	//ADDITIVE->SetState(); // 더 밝게 만드는 것

	_curScene->Render();

	ImGui::Text("FPS: %d", Timer::GetInstance()->GetFPS());

	_curScene->PostRender();

	// 맨 뒤에 만듬 -> 항상 보여야 하기 때문
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
// Scale, Rotate, Translate (SRT) : 정점의 이동의 종류들
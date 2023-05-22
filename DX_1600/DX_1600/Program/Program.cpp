#include "framework.h"
#include "Program.h"

#include "../Scene/TutorialScene.h"
#include "../Scene/SolarSystem.h"
#include "../Scene/DungreedScene.h"

Program::Program()
{
	_curScene = make_shared<DungreedScene>();

	_view = make_shared<MatrixBuffer>();
	_projection = make_shared<MatrixBuffer>();

	XMMATRIX projectM = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);

	_projection->SetData(projectM);

	_view->Update();
	_projection->Update();
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

	_view->SetVSBuffer(1);
	_projection->SetVSBuffer(2);

	// 누끼 딴거 사물만 남기고 배경 지움
	ALPHA->SetState();
	//ADDITIVE->SetState(); // 더 밝게 만드는 것

	_curScene->Render();

	Device::GetInstance()->Present();
}
// Scale, Rotate, Translate (SRT) : 정점의 이동의 종류들
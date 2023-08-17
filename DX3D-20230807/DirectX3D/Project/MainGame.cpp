#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	scene = new TutorialScene();
}

MainGame::~MainGame()
{
	delete scene;

	Release();
}

void MainGame::Update()
{
	scene->Update();
}

void MainGame::Render()
{
	scene->PreRender();

	Device::GetInstance()->Clear();

	scene->Render();

	scene->PostRender();

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
	Device::GetInstance(); // 안해줘도 생성시 만들어짐
	Enviroment::GetInstance();
}

void MainGame::Release()
{
	Device::Delete();
	Shader::Delete();
	Enviroment::Delete();
}

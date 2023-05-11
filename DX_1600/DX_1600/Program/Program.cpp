#include "framework.h"
#include "Program.h"

Program::Program()
{
	_curScene = make_shared<GoombaScene>();
}

Program::~Program()
{
	
}

void Program::Update()
{
	_curScene->Update();
}

void Program::Render()
{
	_curScene->Render();
}

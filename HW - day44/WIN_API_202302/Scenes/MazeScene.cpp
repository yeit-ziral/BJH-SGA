#include "framework.h"
#include "MazeScene.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
	_runner = make_shared<Mazerunner>(_maze);
}

MazeScene::~MazeScene()
{
}

void MazeScene::Update()
{
	_maze->Update();
	_runner->Update();
}

void MazeScene::Render(HDC hdc)
{
	_maze->Render(hdc);

	std::string endBestStr = std::to_string(_runner->GetEndPosBest());

	TextOut(hdc, WIN_WIDTH * 0.5f, 0, endBestStr.c_str(), endBestStr.length());
}

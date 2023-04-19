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

	int endBest = _runner->GetEndPosBest();

	string endBestStr = to_string(endBest);

	wstring wstr(endBestStr.begin(), endBestStr.end());

	LPCWSTR result = wstr.c_str();

	TextOut(hdc, WIN_WIDTH * 0.5f, 0, result, endBestStr.length());
}

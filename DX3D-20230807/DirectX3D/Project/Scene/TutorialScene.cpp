#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    cube = new Cube;
   
}

TutorialScene::~TutorialScene()
{
    delete cube;
    
}

void TutorialScene::Update()
{
}

void TutorialScene::PreRender()
{
    cube->Debug();
}

void TutorialScene::Render()
{
    //TODO : Render
    cube->Render();
}

void TutorialScene::PostRender()
{
    cube->Update();
}

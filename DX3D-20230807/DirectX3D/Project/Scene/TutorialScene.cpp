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
    cube->Update();
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
    //TODO : Render
    cube->Render();
}

void TutorialScene::PostRender()
{
}

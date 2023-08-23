#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    cube = new Cube({1.0f, 0.0f, 0.0f, 1.0f});
    cube2 = new Cube({0.0f, 1.0f, 0.0f, 1.0f});
   
    cube2->translation.x = 3;

    cube2->SetParent(cube);
}

TutorialScene::~TutorialScene()
{
    delete cube;
    delete cube2;
    
}

void TutorialScene::Update()
{
    cube->Update();
    cube2->Update();

    cube->rotation.y += 0.0001f;
}

void TutorialScene::PreRender()
{
    cube->Debug();
    cube2->Debug();
}

void TutorialScene::Render()
{
    //TODO : Render
    cube->Render();
    cube2->Render();
}

void TutorialScene::PostRender()
{

}

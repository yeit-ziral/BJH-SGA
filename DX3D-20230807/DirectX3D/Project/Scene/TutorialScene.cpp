#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    cube = new Cube({1.0f, 0.0f, 0.0f, 1.0f});
    cube2 = new Cube({0.0f, 1.0f, 0.0f, 1.0f});
   
    //cube2->translation.x = 3;

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

    //cube->rotation.y += 0.0001f;

    if (KEY_PRESS(VK_LEFT))
        cube->translation += cube->Left() * Time::Delta();

    if (KEY_PRESS(VK_RIGHT))
        cube->translation += cube->Right() * Time::Delta();

    if (KEY_PRESS(VK_UP))
        cube->translation += cube->Up() * Time::Delta();

    if (KEY_PRESS(VK_DOWN))
        cube->translation += cube->Down() * Time::Delta();

    if (KEY_PRESS('Q'))
        cube->rotation.z += Time::Delta();

    if (KEY_PRESS('E'))
        cube->rotation.z -= Time::Delta();
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

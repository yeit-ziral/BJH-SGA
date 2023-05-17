#include "framework.h"
#include "TutorialScene.h"

#define LERP(s,e,t) s + (e - s)*t //linear experience

TutorialScene::TutorialScene()
{
    _sun = make_shared<Planet>(L"Resource/sun.png");
    _sunPoint = make_shared<Planet>(L"Resource/sun.png");
    _earth = make_shared<Planet>(L"Resource/earth.png");
    _earthPoint = make_shared<Planet>(L"Resource/earth.png");
    _moon = make_shared<Planet>(L"Resource/moon.png");

    _earthPoint->GetTransform()->SetParent(_sunPoint->GetTransform());
    _earth->GetTransform()->SetParent(_sunPoint->GetTransform());
    _moon->GetTransform()->SetParent(_earthPoint->GetTransform());

    _sun->GetTransform()->SetPosition(CENTER);
    _sunPoint->GetTransform()->SetPosition(CENTER);
    _earth->GetTransform()->SetPosition(Vector2(5000, 0));
    _earthPoint->GetTransform()->SetPosition(Vector2(5000, 0));
    _moon->GetTransform()->SetPosition(Vector2(1000, 0));

    _sun->GetTransform()->SetScale({ 0.1f, 0.1f });
    _sunPoint->GetTransform()->SetScale({ 0.1f, 0.1f });
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
    // sun spin
    _angle2 += 0.0001f;
    // earth spin around sun
    _angle2_1 += 0.0003f;
    // earth spin
    _angle1 += 0.001f;
    // moon spin around earth
    _angle1_1 += 0.0003f;

    Vector2 temp = LERP(_sun->GetTransform()->GetPos(), mousePos, 0.001f);
    _sun->GetTransform()->SetPosition(temp);
    _sunPoint->GetTransform()->SetPosition(temp);

    _sun->GetTransform()->SetAngle(_angle2);
    _sunPoint->GetTransform()->SetAngle(_angle2_1);
    _earth->GetTransform()->SetAngle(_angle1);
    _earthPoint->GetTransform()->SetAngle(_angle1_1);

    _moon->Update();
    _earthPoint->Update();
    _earth->Update();
    _sunPoint->Update();
    _sun->Update();
}

void TutorialScene::Render()
{
    _sunPoint->Render();
    _sun->Render();
    _earthPoint->Render();
    _earth->Render();
    _moon->Render();
}

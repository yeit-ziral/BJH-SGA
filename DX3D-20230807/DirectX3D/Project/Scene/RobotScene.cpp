#include "Framework.h"
#include "RobotScene.h"

RobotScene::RobotScene()
{
	_body = new Cube({ 1.0f, 1.0f, 1.0f, 1.0f });
	_head = new Cube({ 1.0f, 0.0f, 0.0f, 1.0f });
	_leftArm = new Cube({ 0.0f, 1.0f, 0.0f, 1.0f });
	_rightArm = new Cube({ 0.0f, 1.0f, 0.0f, 1.0f });
	_leftLeg = new Cube({ 0.0f, 0.0f, 1.0f, 1.0f });
	_rightLeg = new Cube({ 0.0f, 0.0f, 1.0f, 1.0f });

	_head->SetParent(_body);
	_leftArm->SetParent(_body);
	_rightArm->SetParent(_body);
	_leftLeg->SetParent(_body);
	_rightLeg->SetParent(_body);
}

RobotScene::~RobotScene()
{
}

void RobotScene::Update()
{
}

void RobotScene::PreRender()
{
}

void RobotScene::Render()
{
}

void RobotScene::PostRender()
{
}

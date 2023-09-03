#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");
//
//#pragma region "·Îº¿"
//	_body = new Cube({ 1.0f, 1.0f, 1.0f, 1.0f });
//	_head = new Cube({ 1.0f, 0.0f, 0.0f, 1.0f });
//	_leftArm = new Cube({ 1.0f, 0.0f, 0.0f, 1.0f });
//	_rightArm = new Cube({ 1.0f, 0.0f, 0.0f, 1.0f });
//	_leftLeg = new Cube({ 1.0f, 0.0f, 0.0f, 1.0f });
//	_rightLeg = new Cube({ 1.0f, 0.0f, 0.0f, 1.0f });
//
//	_head->SetParent(_body);
//	_leftArm->SetParent(_body);
//	_rightArm->SetParent(_body);
//	_leftLeg->SetParent(_body);
//	_rightLeg->SetParent(_body);
//
//	_body->scale = { 1.0f, 1.0f, 1.0f };
//	_head->scale = { 0.5f,0.5f,0.5f };
//	_leftArm->scale = { 0.4f, 1.0f, 0.5f };
//
//	_rightArm->scale = { 0.4f, 1.0f, 0.5f };
//	_leftLeg->scale = { 0.5f, 1.2f, 0.5f };
//	_rightLeg->scale = { 0.5f, 1.2f, 0.5f };
//
//	_head->translation.y += 2.0f;
//	_leftArm->translation.x -= 1.5f;
//	_rightArm->translation.x += 1.5f;
//	_leftLeg->translation.x -= 0.8;
//	_leftLeg->translation.y -= 1.5f;
//	_rightLeg->translation.x += 0.8f;
//	_rightLeg->translation.y -= 1.5f;
//
//	_head->SetPivot({ 0.0f, -1.0f, 0.0f });
//	_leftArm->SetPivot({ 0.0f, 1.0f, 1.0f });
//	_rightArm->SetPivot({ 0.0f, 1.0f, 1.0f });
//	_leftLeg->SetPivot({ 0.0f, 1.0f, 1.0f });
//	_rightLeg->SetPivot({ 0.0f, 1.0f, 1.0f });
//#pragma endregion


	sphere = new Sphere({ 0.0f, 0.2f, 0.5f, 1.0f }, 20.0f);
}

TerrainScene::~TerrainScene()
{
	delete terrain;
//
//#pragma region ·Îº¿
//	delete _head;
//	delete _leftArm;
//	delete _rightArm;
//	delete _leftLeg;
//	delete _rightLeg;
//	delete _body;
//#pragma endregion
}

void TerrainScene::Update()
{
	terrain->Update();
//
//#pragma region ·Îº¿
//	_body->Update();
//	_head->Update();
//	_leftArm->Update();
//	_rightArm->Update();
//	_leftLeg->Update();
//	_rightLeg->Update();
//
//	if (KEY_PRESS('W'))
//	{
//		_body->translation.z += 0.0001f;
//		if (_leftArm->rotation.x > 1.0f)
//		{
//			_leftArm->_pendulumMovement = true;
//		}
//		if (_leftArm->rotation.x < -1.0f)
//		{
//			_leftArm->_pendulumMovement = false;
//		}
//
//		if (!_leftArm->_pendulumMovement)
//		{
//			_leftArm->rotation.x += 0.001f;
//			_rightArm->rotation.x -= 0.001f;
//			_leftLeg->rotation.x -= 0.001f;
//			_rightLeg->rotation.x += 0.001f;
//		}
//		else if (_leftArm->_pendulumMovement)
//		{
//			_leftArm->rotation.x -= 0.001f;
//			_rightArm->rotation.x += 0.001f;
//			_leftLeg->rotation.x += 0.001f;
//			_rightLeg->rotation.x -= 0.001f;
//		}
//	}
//
//	if (KEY_PRESS('S'))
//	{
//		_body->translation.z -= 0.0001f;
//		if (_leftArm->rotation.x > 1.0f)
//		{
//			_leftArm->_pendulumMovement = true;
//		}
//		if (_leftArm->rotation.x < -1.0f)
//		{
//			_leftArm->_pendulumMovement = false;
//		}
//
//		if (!_leftArm->_pendulumMovement)
//		{
//			_leftArm->rotation.x += 0.001f;
//			_rightArm->rotation.x -= 0.001f;
//			_leftLeg->rotation.x -= 0.001f;
//			_rightLeg->rotation.x += 0.001f;
//		}
//		else if (_leftArm->_pendulumMovement)
//		{
//			_leftArm->rotation.x -= 0.001f;
//			_rightArm->rotation.x += 0.001f;
//			_leftLeg->rotation.x += 0.001f;
//			_rightLeg->rotation.x -= 0.001f;
//		}
//	}
//	if (KEY_PRESS('D'))
//	{
//		_body->rotation.y += 0.0001f;
//	}
//	if (KEY_PRESS('A'))
//	{
//		_body->rotation.y -= 0.0001f;
//	}
//#pragma endregion

	sphere->Update();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	terrain->Render();

//#pragma region ·Îº¿
//	_body->Render();
//	_head->Render();
//	_leftArm->Render();
//	_rightArm->Render();
//	_leftLeg->Render();
//	_rightLeg->Render();
//#pragma endregion

	sphere->Render();
}

void TerrainScene::PostRender()
{
}

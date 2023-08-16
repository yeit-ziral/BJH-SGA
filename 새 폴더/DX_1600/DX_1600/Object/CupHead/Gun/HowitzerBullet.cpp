#include "framework.h"
#include "HowitzerBullet.h"

using namespace tinyxml2;

HowitzerBullet::HowitzerBullet()
{
	_bullet = make_shared<CircleCollider>(16.0f);

	_transform = make_shared<Transform>();
	_transform->SetParent(_bullet->GetTransform());

	_quad = make_shared<Quad>(L"Resource/howitzerBullet.png");

	_bullet->Update();
	_transform->Update();
}

HowitzerBullet::~HowitzerBullet()
{
}

void HowitzerBullet::Update()
{
	if (!_isActive)
		return;

	_upPower -= 800.0f * DELTA_TIME; // 초당 -800 pixel/sec

	if (_upPower < -600.0f)
		_upPower = -600.0f;

	Vector2 a(_speed, _upPower);

	_speedFixingNum = a.Length();

	NormalizeDir();

	_transform->SetAngle(atan2f(_dir.y, _dir.x));

	_bullet->GetTransform()->AddVector2((_dir * _speedFixingNum) * DELTA_TIME);

	_bullet->Update();
	_transform->Update();
}

void HowitzerBullet::Render()
{
	if (!_isActive)
		return;

	_bullet->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}

void HowitzerBullet::PostRender()
{
	ImGui::Text("Up Power : %f", this->_upPower);
}

void HowitzerBullet::Shoot(Vector2 target, Vector2 startPos)
{
	_isActive = true;

	CalculateYspeed(target, startPos);


	_bullet->GetTransform()->SetPosition(startPos);

}

void HowitzerBullet::CalculateYspeed(Vector2 target, Vector2 startPos)
{

	float ax = target.x - startPos.x;
	float ay = target.y - startPos.y;

	// 랜덤하게 주어진 x 방향 속도로 ax를 나누어 도달 시간을 구함

	_speed = (ax / 1.5f) + RandomNum(0, 5);

	float time = ax / _speed;

	// 시간동안 target의 y축 위치로 이동하도록 초기 y축 속도를 구한다

	_upPower = (ay / time) - (-800 * time);
}

void HowitzerBullet::EndEvent()
{
}
#include "framework.h"
#include "HowitzerBullet.h"

using namespace tinyxml2;

HowitzerBullet::HowitzerBullet()
{
}

HowitzerBullet::~HowitzerBullet()
{
}

void HowitzerBullet::Update()
{
	{
		_upPower -= 800.0f * DELTA_TIME; // 초당 -800 pixel/sec

		if (_upPower < -600.0f)
			_upPower = -600.0f;

		_bullet->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _upPower * DELTA_TIME);
	}

	_bullet->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME); // 주어진 렌덤한 x축 속도로 이동
}

void HowitzerBullet::Render()
{
}

void HowitzerBullet::Shoot(Vector2 target, Vector2 startPos)
{
	float ax = target.x - startPos.x;

	// 랜덤하게 주어진 x 방향 속도로 ax를 나누어 도달 시간을 구함

	_speed = RandomNum(500, 700);

	float time = ax / _speed;

	// 시간동안 target의 y축 위치로 이동하도록 초기 y축 속도를 구한다

	CalculateYspeed(target.y, time);
}

void HowitzerBullet::EndEvent()
{
}

void HowitzerBullet::CalculateYspeed(float targetY, float time)
{
	_upPower = (targetY / time) + (-800 * time);
}

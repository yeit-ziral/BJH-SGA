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
		_upPower -= 800.0f * DELTA_TIME;

		if (_upPower < -600.0f)
			_upPower = -600.0f;

		_bullet->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _upPower * DELTA_TIME);
	}
}

void HowitzerBullet::Render()
{
}

void HowitzerBullet::Shoot(Vector2 target, Vector2 startPos)
{
	float a = target.x - startPos.x;
}

void HowitzerBullet::EndEvent()
{
}

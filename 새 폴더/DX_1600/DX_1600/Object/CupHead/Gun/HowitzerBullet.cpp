#include "framework.h"
#include "HowitzerBullet.h"

using namespace tinyxml2;

HowitzerBullet::HowitzerBullet(Vector2 target, Vector2 startPos)
{


	CalculateYspeed(target, startPos);
}

HowitzerBullet::~HowitzerBullet()
{
}

void HowitzerBullet::Update()
{
	{
		_upPower -= 800.0f * DELTA_TIME; // �ʴ� -800 pixel/sec

		if (_upPower < -600.0f)
			_upPower = -600.0f;

		_bullet->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _upPower * DELTA_TIME);
	}

	_bullet->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME); // �־��� ������ x�� �ӵ��� �̵�
}

void HowitzerBullet::Render()
{
}

void HowitzerBullet::Shoot(Vector2 target, Vector2 startPos)
{
	if (_atkCool)
	{
		_timer += DELTA_TIME;
		if (_timer > _coolingtime)
		{
			_timer = 0.0f;
			_atkCool = false;
		}
		return;
	}



	_atkCool = true;
}

void HowitzerBullet::EndEvent()
{
}

void HowitzerBullet::CalculateYspeed(Vector2 target, Vector2 startPos)
{

	float ax = target.x - startPos.x;

	// �����ϰ� �־��� x ���� �ӵ��� ax�� ������ ���� �ð��� ����

	_speed = RandomNum(500, 700);

	float time = ax / _speed;

	// �ð����� target�� y�� ��ġ�� �̵��ϵ��� �ʱ� y�� �ӵ��� ���Ѵ�

	_upPower = (target.y / time) + (-800 * time);
}

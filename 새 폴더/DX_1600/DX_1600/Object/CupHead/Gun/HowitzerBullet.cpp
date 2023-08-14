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

	_upPower -= 800.0f * DELTA_TIME; // �ʴ� -800 pixel/sec

	if (_upPower < -600.0f)
		_upPower = -600.0f;

	Vector2 a(_speed, _upPower);

	_speedFixingNum = a.Length();

	NormalizeDir();

	_transform->SetAngle(atan2f(_dir.y, _dir.x));

	_bullet->GetTransform()->AddVector2((_dir * _speedFixingNum) * DELTA_TIME);

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

void HowitzerBullet::Shoot(Vector2 target, Vector2 startPos)
{
	_isActive = true;

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

	_bullet->GetTransform()->SetPosition(startPos);

	CalculateYspeed(target, startPos);

	_atkCool = true;
}

void HowitzerBullet::EndEvent()
{
}

void HowitzerBullet::CalculateYspeed(Vector2 target, Vector2 startPos)
{

	float ax = target.x - startPos.x;

	// �����ϰ� �־��� x ���� �ӵ��� ax�� ������ ���� �ð��� ����

	_speed = (ax / 1.5f) + RandomNum(-100, 100);

	float time = ax / _speed;

	// �ð����� target�� y�� ��ġ�� �̵��ϵ��� �ʱ� y�� �ӵ��� ���Ѵ�

	_upPower = (target.y / time) + (-800 * time);
}

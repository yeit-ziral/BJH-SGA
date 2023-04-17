#include "framework.h"
#include "Cannon.h"

Cannon::Cannon(Vector2 pos)
	:_isActive(true)
{
	_body = make_shared<CircleCollider>(pos, 50);
	_muzzle = make_shared<Line>(Vector2(pos), Vector2(pos.x + _muzzleLength, pos.y));

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		_bullets.push_back(bullet);
	}

	_brush = CreateSolidBrush(BLUE);
	_pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (_isActive == false) return;
	if (_isControlled)
	{
		Move();
		Angle();
		Fire();
	}
	CheckAttack();

	_body->Update();
	_muzzle->Update();
	for (auto& bullet : _bullets)
	{
		bullet->Update();
	}
}

void Cannon::Render(HDC hdc)
{
	if (_isActive == false) return;
	_muzzle->Render(hdc);

	//SelectObject(hdc, _brush);
	SelectObject(hdc, _pen);

	/*shared_ptr<CircleCollider> temp = dynamic_pointer_cast<CircleCollider>(_body);
	float left = _body->GetCenter().x - temp->GetRadius();
	float right = _body->GetCenter().x + temp->GetRadius();
	float top = _body->GetCenter().y - temp->GetRadius();
	float bottom = _body->GetCenter().y + temp->GetRadius();
	Ellipse(hdc, left, top, right, bottom);*/
	_body->Render(hdc);
	for (auto& bullet : _bullets)
	{
		bullet->Render(hdc);
	}
}


void Cannon::Move()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->MoveCenter(Vector2(-1.0f, 0.0f));
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->MoveCenter(Vector2(1.0f, 0.0f));
	}
	_muzzle->_start = _body->GetCenter();
	_muzzle->_end = _muzzle->_start + (_muzzleDir * _muzzleLength);
}

void Cannon::Angle()
{
	if (GetAsyncKeyState(VK_UP))
	{
		_muzzleAngle += 0.1f;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		_muzzleAngle -= 0.1f;
	}

	_muzzleDir = Vector2(cosf(_muzzleAngle), -sinf(_muzzleAngle));
}

void Cannon::Fire()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		// ²¨Á®ÀÖ´Â ¾Ö¸¸ ½¸
		auto iter = std::find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<Bullet>& bullet)->bool
		{
			if (bullet->IsActive() == false)
				return true;
			return false;
		});
		if (iter != _bullets.end())
		{
			(*iter)->SetPos(_muzzle->_end);
			(*iter)->Shoot(_muzzleDir.NormalVector2(), 10.0f);
		}

	}
}

void Cannon::CheckAttack()
{
	if (_target.expired())
		return;
	if (_target.lock()->_isActive == false
		|| _isActive == false
		|| _isControlled == false)
	{
		return;
	}

	for (auto& bullet : _bullets)
	{
		if (bullet->IsCollision(_target.lock()))
		{
			_target.lock()->_isActive = false;
			bullet->SetActive(false);
		}
	}
}

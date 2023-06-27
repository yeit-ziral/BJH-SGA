#include "framework.h"
#include "Cup_Player.h"
#include "Cup_Ani.h"
#include "Cup_Bullet.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	SOUND->Add("Cup_Attack", "Resource/Sound/Attack.wav", false);

	_collider = make_shared<CircleCollider>(50.0f);
	_animation = make_shared<Cup_Ani>();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}

	_animation->SetParent(_collider->GetTransform());
	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/hit_4x2.png", Vector2(4, 2), Vector2(100, 100), 0.1f);
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	if (!_isAlive)
		return;
	Input();
	_collider->Update();
	_animation->Update();
	for(auto& bullet : _bullets)
		bullet->Update();
	if (!_animation->IsActive())
		_isAlive = false;
}

void Cup_Player::Render()
{
	if (!_isAlive)
		return;
	_animation->Render();
	for(auto& bullet : _bullets)
		bullet->Render();
	_collider->Render();
}

void Cup_Player::PostRender()
{

}


void Cup_Player::Input()
{
	// 중력적용
	{
		_jumpPower -= 15.0f;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_collider->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
	}

	if (!IsAlive())
		return;

	if (_animation->GetState() == Cup_Ani::State::HIT)
		return;

	if (KEY_PRESS(VK_LEFT))
	{
		Vector2 movePos = Vector2(-_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		Vector2 movePos = Vector2(_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	Fire();

	Jump();
}

void Cup_Player::Fire()
{
	if (_atkCool)
	{
		_time += DELTA_TIME;
		if (_time > _atkSpeed)
		{
			_time = 0.0f;
			_atkCool = false;
		}
		return;
	}

	if (KEY_PRESS('X'))
	{
		SOUND->Play("Cup_Attack", 0.3f);
		auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
			[](const shared_ptr<Cup_Bullet>& obj)-> bool {return !obj->_isActive(); });

		if (bulletIter == _bullets.end())
			return;

		_atkCool = true;
		Vector2 startPos = _collider->GetPos();
		if (_animation->GetIsRight())
		{
			startPos += Vector2(50, 0);
			(*bulletIter)->SetRight();
			(*bulletIter)->Shoot(Vector2(1, 0), startPos);
		}
		else
		{
			startPos += Vector2(-50, 0);
			(*bulletIter)->SetLeft();
			(*bulletIter)->Shoot(Vector2(-1, 0), startPos);
		}
	}

}

void Cup_Player::Jump()
{
	if (KEY_DOWN('Z') && _animation->GetISGround())
	{
		//CAMERA->ShakeStart(50.0f, 30.0f);
		_jumpPower = 600.0f;
		_animation->SetIsGround(false);
	}
}

void Cup_Player::Damaged(int damgae)
{
	if (!_isAlive)
		return;
	_hp -= damgae;
	_animation->DamagedEvent();

	if (_hp < 1)
	{
		_hp = 0;
		_animation->DieEvent();
	}
}

bool Cup_Player::IsCollision_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetBulletCollider()))
		{
			bullet->_isActive = false;
			EFFECT_PLAY("Hit", bullet->GetPosition());
			return true;
		}
	}

	return false;
}


void Cup_Player::SetGrounded()
{
	if (!IsAlive())
		return;

	if (!_animation->GetISGround() && _jumpPower < 0)
	{
		_animation->SetIsGround(true);
		if (_animation->GetState() == Cup_Ani::State::HIT)
			return;
		_animation->SetStateIdle();
	}
}

bool Cup_Player::IsAlive()
{
	if (_animation->GetState() == Cup_Ani::State::GHOST)
		return false;
	else
		return true;
}

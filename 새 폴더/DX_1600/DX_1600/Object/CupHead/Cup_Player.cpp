#include "framework.h"
#include "Cup_Player.h"
#include "Cup_Ani.h"
#include "Cup_Bullet.h"
#include "Gun/Gun.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	SOUND->Add("Cup_Attack", "Resource/Sound/Attack.wav", false);

	_collider = make_shared<CircleCollider>(50.0f);
	_animation = make_shared<Cup_Ani>();

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

	if (!_animation->IsActive())
		_isAlive = false;
}

void Cup_Player::Render()
{
	if (!_isAlive)
		return;
	_animation->Render();

	_collider->Render();
}

void Cup_Player::PostRender()
{

}


void Cup_Player::Input()
{
	// �߷����� -> ���� �Ѿ˿��� �����ؾ� ��
	{
		_jumpPower -= 15.0f;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_collider->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
	}

	if (!_isAlive)
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

	//Fire();

	Jump();
}

//void Cup_Player::Fire() // ������ �ѱ� ��
//{
//	if (KEY_PRESS(VK_LBUTTON))
//	{
//		SOUND->Play("Cup_Attack", 0.3f);
//		// ���콺 ��Ű ���� �� ���� Fire() �ҷ�����
//
//			// ���콺 �������� �Ѿ� ���
//		Vector2 dir = MOUSE_POS - GetPos();
//		_gun->Fire();
//
//	}
//}

void Cup_Player::Jump()
{
	if (KEY_DOWN(VK_SPACE) && _animation->GetISGround())
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

//bool Cup_Player::IsCollision_Bullets(shared_ptr<Collider> col)
//{
//	_gun->IsCollision_Bullets(col);
//}


void Cup_Player::SetGrounded()
{
	if (!_isAlive)
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

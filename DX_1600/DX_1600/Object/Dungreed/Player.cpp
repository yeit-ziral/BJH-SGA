#include "framework.h"
#include "Player.h"

Player::Player()
{
	_player = make_shared<Quad>(L"Resource/Player.png");
	_player->GetTransform()->SetPosition(Vector2(100, 100));

	_bowSlot = make_shared<Transform>();

	_bow = make_shared<Quad>(L"Resource/Bow.png");
	_bow->GetTransform()->SetParent(_bowSlot);
	_bow->GetTransform()->SetPosition({ 50, 0 });
	_bow->GetTransform()->SetAngle(-PI * 0.75f);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Bullets> bullet = make_shared<Bullets>();
		_bullets.push_back(bullet);
	}
}

Player::~Player()
{
}

void Player::Update()
{
	_bowSlot->SetPosition(_player->GetTransform()->GetPos());

	SetBowAngle();

	_player->Update();
	_bow->Update();
	_bowSlot->Update();

	for (auto bullet : _bullets)
		bullet->Update();

	Fire();
}

void Player::Render()
{
	_player->Render();
	_bow->Render();

	for (auto bullet : _bullets)
		bullet->Render();
}

void Player::SetBowAngle()
{
	Vector2 playerToMouse = MOUSE_POS - GetPos();
	float angle = playerToMouse.Angle();
	_bowSlot->SetAngle(angle);
}

void Player::Fire()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
			[](const shared_ptr<Bullets>& obj)-> bool {return !obj->IsActive(); });

		Vector2 dir = MOUSE_POS - _bowSlot->GetPos();
		if (bulletIter != _bullets.end())
		{
			(*bulletIter)->Shoot(dir, _bow->GetTransform()->GetWorldPosition());
		}
	}
}
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
		shared_ptr<Bullets> bullet = make_shared<Bullets>(_bow->GetTransform()->GetWorldPosition());
		_bullets.push_back(bullet);
	}
}

Player::~Player()
{
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
		Fire();

	SetBowAngle();

	_bowSlot->SetPosition(_player->GetTransform()->GetPos());

	_player->Update();
	_bowSlot->Update();
	_bow->Update();

	for (auto bullet : _bullets)
		bullet->Update();
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
	Vector2 playerToMouse = mousePos - GetPos();
	float angle = playerToMouse.Angle();
	_bowSlot->SetAngle(angle);
}

void Player::Fire()
{
	Vector2 dir = mousePos - GetPos();

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<Bullets> obj)-> bool
		{
			return !obj->IsActive();
		});

	if (bulletIter == _bullets.end())
		return;

	(*bulletIter)->Shoot(dir, _bow->GetTransform()->GetWorldPosition());
}
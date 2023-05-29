#include "framework.h"
#include "Dun_Player.h"

#include "Dun_Bullet.h"

Dun_Player::Dun_Player()
{
	_quad = make_shared<Quad>(L"Resource/Player.png");
	float a = _quad->GetTransform()->GetWorldScale().x * 0.5f;
	_player = make_shared<CircleCollider>(50);
	_player->GetTransform()->SetPosition(Vector2(100.0f,WIN_HEIGHT * 0.5f));

	_bowSlot = make_shared<Transform>();

	_bow = make_shared<Quad>(L"Resource/Bow.png");
	_bow->GetTransform()->SetParent(_bowSlot);
	_bow->GetTransform()->SetPosition({50,0});
	_bow->GetTransform()->SetAngle(-PI * 0.75f);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Dun_Bullet> bullet = make_shared<Dun_Bullet>();
		bullet->_isActive = false;
		_bullets.push_back(bullet);
	}
}

Dun_Player::~Dun_Player()
{
}

void Dun_Player::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		Fire();
	}

	SetBowAngle();
	_quad->GetTransform()->SetPosition(_player->GetTransform()->GetWorldPosition());

	_bowSlot->SetPosition(_quad->GetTransform()->GetPos());

	_player->GetTransform()->SetPosition(_player->GetTransform()->GetPos() + Vector2(0.0f, -0.1f));

	_player->Update();
	_quad->Update();
	_bowSlot->Update();
	_bow->Update();

	for(auto bullet : _bullets)
		bullet->Update();
}

void Dun_Player::Render()
{
	_player->Render();
	_quad->Render();
	_bow->Render();

	for(auto bullet : _bullets)
		bullet->Render();
}

void Dun_Player::SetBowAngle()
{
	Vector2 playerToMouse = MOUSE_POS - GetPos();
	float angle = playerToMouse.Angle();
	_bowSlot->SetAngle(angle);
}

void Dun_Player::Fire()
{
	Vector2 dir = MOUSE_POS - GetPos();

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(), 
	[](const shared_ptr<Dun_Bullet> obj)-> bool { return !obj->_isActive; });

	if(bulletIter == _bullets.end())
		return;

	(*bulletIter)->Shoot(dir, _bow->GetTransform()->GetWorldPosition());
}

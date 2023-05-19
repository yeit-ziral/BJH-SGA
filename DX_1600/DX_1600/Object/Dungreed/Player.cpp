#include "framework.h"
#include "Player.h"

Player::Player(wstring file, Vector2 scale)
{
	_player = make_shared<Quad>(file);
	_player->GetTransform()->SetScale(scale);

	_bowSlot = make_shared<Transform>();
}

Player::~Player()
{
}

void Player::Update()
{

	_player->Update();
	_bowSlot->SetPosition(_player->GetTransform()->GetPos());
}

void Player::Render()
{
	_player->Render();
}

void Player::SetBowAngle(float angle)
{
	Vector2 playerToMouse = mousePos - _player->GetTransform()->GetPos();
	float angle = playerToMouse.Angle();

	_bowSlot->SetBowAngle(angle);
}

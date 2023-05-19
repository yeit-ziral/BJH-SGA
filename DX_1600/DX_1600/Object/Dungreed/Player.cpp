#include "framework.h"
#include "Player.h"

Player::Player(wstring file, Vector2 scale)
{
	_player = make_shared<Quad>(file);
	_player->GetTransform()->SetScale(scale);
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Render()
{
}

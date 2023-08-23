#include "framework.h"
#include "Lobby.h"
#include "../../Object/CupHead/Player/Cup_Player.h"

Lobby::Lobby()
{
	_player = make_shared<Cup_Player>
}

Lobby::~Lobby()
{
}

void Lobby::Update()
{
}

void Lobby::Render()
{
}

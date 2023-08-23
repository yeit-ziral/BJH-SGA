#include "framework.h"
#include "Lobby.h"
#include "../../Object/CupHead/Player/Cup_Player.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Potal.h"

Lobby::Lobby()
{
	_player = make_shared<Cup_Player>();


	_track = make_shared<Cup_Track>();
	Vector2 trackSize = _track->GetTrackSize();

	_potal = make_shared<Potal>();
	_potal->SetPosition(Vector2(200.0f, 0.0f));
	_potal->_isActive = true;
}

Lobby::~Lobby()
{
}

void Lobby::Init()
{
	_player->SetPosition(Vector2(0, 0));

	Vector2 trackSize = _track->GetTrackSize();

	CAMERA->SetTarget(_player->GetTransform());
	//CAMERA->SetLeftBottom(Vector2((-trackSize.x * 0.125f), -100.0f));
	//CAMERA->SetRightTop(Vector2((trackSize.x), 1000.0f));

	Load();
}

void Lobby::End()
{
}

void Lobby::Update()
{
	_player->Update();
	 _track->Update();
	 _potal->Update();

	 if (_track->GetColider()->Block(_player->GetCollider()))
	 {
		 if (_track->GetColider()->_sideCollision)
			 return;

		 _player->SetGrounded();
	 }

	 if (_potal->IsCollision(_player->GetCollider()))
		 SceneManager::GetInstance()->NextScene();
}

void Lobby::Render()
{
	 _potal->Render();
	 _track->Render();
	_player->Render();
}

void Lobby::Save()
{
}

void Lobby::Load()
{
}

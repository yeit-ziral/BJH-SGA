#include "framework.h"
#include "Cup_Ani.h"

using namespace tinyxml2;

Cup_Ani::Cup_Ani()
{
	CreateAction(L"Resource/CupHead/player/Idle.png", "Resource/CupHead/player/Idle.xml", "CUP_IDLE", Vector2(250, 250));
	CreateAction(L"Resource/CupHead/player/Jump.png", "Resource/CupHead/player/Jump.xml", "CUP_JUMP", Vector2(120, 120));
	CreateAction(L"Resource/CupHead/player/Run.png", "Resource/CupHead/player/Run.xml", "CUP_RUN", Vector2(120, 140));
	CreateAction(L"Resource/CupHead/player/AimStraightShot.png", "Resource/CupHead/player/AimStraightShot.xml", "CUP_SHOT", Vector2(250, 250));
	CreateAction(L"Resource/CupHead/player/RunShot.png", "Resource/CupHead/player/RunShot.xml", "CUP_RUNSHOT", Vector2(120, 120));
	CreateAction(L"Resource/CupHead/player/Player_Hit.png", "Resource/CupHead/player/Player_Hit.xml", "CUP_HIT", Vector2(250, 250), false);
	CreateAction(L"Resource/CupHead/player/Player_Ghost.png", "Resource/CupHead/player/Player_Ghost.xml", "CUP_GHOST", Vector2(250, 250), false);
	_transform = make_shared<Transform>();
	_transform->SetPosition(Vector2(0.0f, 9.76f));

	// Action Envent ¼³Á¤
	{
		_actions[HIT]->SetEndEvent(std::bind(&Cup_Ani::SetStateIdle, this));
		_actions[GHOST]->SetEndEvent(std::bind(&Cup_Ani::EndEvent, this));
	}

	SetRight();
}

Cup_Ani::~Cup_Ani()
{
}

void Cup_Ani::Update()
{
	if (!_isActive)
		return;
	StateControl();

	_actions[_curState]->Update();
	_sprites[_curState]->Update();
	_transform->Update();
}

void Cup_Ani::Render()
{
	if (!_isActive)
		return;
	_transform->SetBuffer(0);

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

void Cup_Ani::PostRender()
{
	ImGui::SliderFloat2("FixedPos", (float*)&_fixedPos, 0, 100);
	_transform->SetPosition(_fixedPos);
}


void Cup_Ani::CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, bool isLoop, float time)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	XMLElement* texturAtlas = document->FirstChildElement();
	XMLElement* row = texturAtlas->FirstChildElement();

	vector<Action::Clip> clips;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();
		
		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action;
	if (isLoop)
	{
		action = make_shared<Action>(clips, actionName);
	}
	else
	{
		action = make_shared<Action>(clips, actionName, Action::Type::END);
	}
	action->Play();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	action->Update();
	sprite->Update();

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Ani::StateControl()
{
	if (_curState == State::HIT || _curState == State::GHOST)
		return;

	if (KEY_DOWN('Z'))
	{
		SetState(JUMP);
	}

	if (!_isGround)
		return;

	if (KEY_UP(VK_LEFT))
	{
		SetState(IDLE);
		_isRight = false;
	}
	if (KEY_PRESS(VK_LEFT))
	{
		SetState(RUN);
		_isRight = false;
		SetLeft();
	}

	if (KEY_UP(VK_RIGHT))
	{
		SetState(IDLE);
		_isRight = true;
	}
	if (KEY_PRESS(VK_RIGHT))
	{
		SetState(RUN);
		_isRight = true;
		SetRight();
	}

	if (KEY_UP('X'))
	{
		SetState(IDLE);
	}
	if (KEY_PRESS('X'))
	{
		SetState(SHOT);
	}

	if (KEY_PRESS('X') && (KEY_PRESS(VK_RIGHT) || KEY_PRESS(VK_LEFT)))
	{
		_curState = State::RUN_SHOT;
	}
}

void Cup_Ani::SetState(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Cup_Ani::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Ani::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}

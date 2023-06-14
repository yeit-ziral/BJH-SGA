#include "framework.h"
#include "Cup_Monster.h"
using namespace tinyxml2;

Cup_Monster::Cup_Monster()
{
	_monster = make_shared<CircleCollider>(150);

	CreateAction(L"Resource/CupHead/BossStart.png", "Resource/CupHead/BossStart.xml", "START", Vector2(100, 100), Action::Type::END);
	CreateAction(L"Resource/CupHead/BossLoop.png", "Resource/CupHead/BossLoop.xml", "LOOP", Vector2(200, 200), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/BossEnd.png", "Resource/CupHead/BossEnd.xml", "END", Vector2(400, 400), Action::Type::END, std::bind(&Cup_Monster::EndEvent, this));
	CreateAction(L"Resource/CupHead/BossDie.png", "Resource/CupHead/BossDie.xml", "DEAD", Vector2(400, 400), Action::Type::END);

	// Action Event ¼³Á¤
	{
		_actions[State::START]->SetAlmostEndEvent([this]()->void { _curState = State::LOOP; });
	}

	_intBuffer = make_shared<IntBuffer>();

	_transform = make_shared<Transform>();
	_transform->SetParent(_monster->GetTransform());
}

Cup_Monster::~Cup_Monster()
{
}

void Cup_Monster::Update()
{
	if (!_isAlive)
		return;

	Input();

	_monster->Update();
	_actions[_curState]->Update();
	_intBuffer->Update();
	_sprites[_curState]->Update();
	_transform->Update();
}

void Cup_Monster::Render()
{
	if (!_isAlive)
		return;

	_transform->SetBuffer(0);

	_sprites[_curState]->SetCurFrame(_actions[_curState]->GetCurClip());
	_intBuffer->SetPSBuffer(1);
	_sprites[_curState]->Render();

	_monster->Render();
}

void Cup_Monster::PostRender()
{
	ImGui::SliderInt("BossState", (int*)&_curState, 0, 3);
}

void Cup_Monster::Input()
{
	if (_hp > 0)
	{
		SetAction(LOOP);
	}
	if (_hp <= 0)
	{ 
		SetAction(END);
	}
}

void Cup_Monster::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Cup_Monster::CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvpath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

	document->LoadFile(xmlpath.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

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

	shared_ptr<Action> action = make_shared<Action>(clips, actionName, type);
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvpath, size);

	action->Update();
	sprite->Update();

	sprite->SetCurFrame(action->GetCurClip());

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Monster::EndEvent()
{
	if (_curState == State::START)
	{
		_curState = State::LOOP;
		_actions[_curState]->Play();
		_actions[START]->Reset();
		return;
	}

	if (_curState == State::LOOP)
	{
		if (_hp <= 0)
		{
			_curState = State::END;
		}
		_actions[_curState]->Play();
		_actions[LOOP]->Reset();
		return;
	}

	if (_curState == State::END)
	{
		_curState = State::DEAD;
		_actions[_curState]->Play();
		_actions[END]->Reset();
		return;
	}
}

void Cup_Monster::GetAttacked(int amount)
{
	if (!_isAlive)
		return;
	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0;
		
		_isAlive = false;
	}
}

void Cup_Monster::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Monster::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}

#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	CreateAction();
	CreateActionRight();
	CreateActionLeft();

	_col = make_shared<CircleCollider>(50);

	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 9.876));

	_curAction = &_actions[0];
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	_col->Update();

	for (auto& action : _actions)
	{
		action->Update();
	}
	_sprite->Update();
	_transform->Update();
	(*_curAction)->Update();
}

void Cup_Player::Render()
{
	_transform->SetBuffer(0);
	_sprite->SetCurFrame((*_curAction)->GetCurClip());
	_sprite->Render();

	_col->Render();
}

void Cup_Player::PostRender()
{
	//ImGui::SliderFloat2("FixedPos", (float*)&_fixedPos, 0, 100);
	//_transform->SetPosition(_fixedPos);
}

void Cup_Player::CreateAction()
{
	wstring srvPath = L"Resource/CupHead/Idle.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Idle.xml";
	document->LoadFile(path.c_str());

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

	shared_ptr<Action> _action = make_shared<Action>(clips, "CUP_IDLE");
	_actions.push_back(_action);
	_sprite = make_shared<Sprite>(srvPath, Vector2(250, 250));
}

void Cup_Player::CreateActionRight()
{
	// 오른쪽으로 걸어가는 액션
	wstring srvPath = L"Resource/CupHead/Run.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Run.xml";
	document->LoadFile(path.c_str());

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

	shared_ptr<Action> _action = make_shared<Action>(clips, "CUP_RUN");
	_actions.push_back(_action);
	_sprite = make_shared<Sprite>(srvPath, Vector2(250, 250));
}

void Cup_Player::CreateActionLeft()
{
	wstring srvPath = L"Resource/CupHead/Run.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Run.xml";
	document->LoadFile(path.c_str());

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

	shared_ptr<Action> _action = make_shared<Action>(clips, "CUP_RUN");
	_actions.push_back(_action);
	_sprite = make_shared<Sprite>(srvPath, Vector2(250, 250));
}

void Cup_Player::SelectDir()
{
	if (KEY_PRESS('D'))
	{
		_actions[1]->Play();
		_curAction = &_actions[1];
	}
	else if (KEY_UP('D'))
	{
		_actions[0]->Play();
		_curAction = &_actions[0];
	}

	if (KEY_PRESS('A'))
	{
		_actions[2]->Play();
		_curAction = &_actions[2];
	}
	else if (KEY_UP('A'))
	{
		_actions[0]->Play();
		_curAction = &_actions[0];
	}
}

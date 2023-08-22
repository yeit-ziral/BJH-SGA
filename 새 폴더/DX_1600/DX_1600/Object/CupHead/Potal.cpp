#include "framework.h"
#include "Potal.h"

using namespace tinyxml2;

Potal::Potal()
{
	_collider = make_shared<CircleCollider>(50.0f);

	CreateAction(L"Resource/Potal.png", "Resource/Potal.xml", "Potal", Vector2(100.0f, 100.0f), true);

	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());

	_collider->Update();
	_transform->Update();
}

Potal::~Potal()
{
}

void Potal::Update()
{
	if (!_isActive)
		return;

	_collider->Update();

	_action->Update();
	_sprite->Update();
	_transform->Update();
}

void Potal::Render()
{
	if (!_isActive)
		return;

	_transform->SetBuffer(0);
	_sprite->SetCurClip(_action->GetCurClip());
	_sprite->Render();
	_collider->Render();
}

void Potal::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

	document->LoadFile(xmmlPath.c_str());

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

	shared_ptr<Action> action;
	if (isLoop)
	{
		action = make_shared<Action>(clips, actionName);
	}
	else
	{
		action = make_shared<Action>(clips, actionName, Action::Type::END, 0.1f);
	}
	action->Play();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);
	_action = action;
	_sprite = sprite;
}

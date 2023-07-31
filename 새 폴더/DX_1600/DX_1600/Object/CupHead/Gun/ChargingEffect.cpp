#include "framework.h"
#include "ChargingEffect.h"

using namespace tinyxml2;

ChargingEffect::ChargingEffect()
{
	CreateAction(L"Resource/CupHead/weapon/ChargingEffect.png", "Resource/CupHead/weapon/ChargingEffect.xml", "ChargingEffect", Vector2(10, 10), false);
	_transform = make_shared<Transform>();
	_transform->Update();
}

ChargingEffect::~ChargingEffect()
{
}

void ChargingEffect::Update()
{
}

void ChargingEffect::Render()
{
	_transform->SetBuffer(0);
	_sprite->Render();
}

void ChargingEffect::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop)
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
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);
	_action = action;
	_sprite = sprite;
}

void ChargingEffect::SetLeft()
{
	_sprite->SetLeft();
}

void ChargingEffect::SetRight()
{
	_sprite->SetRight();
}

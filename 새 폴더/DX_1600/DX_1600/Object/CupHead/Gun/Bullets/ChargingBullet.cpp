#include "framework.h"
#include "ChargingBullet.h"
using namespace tinyxml2;

ChargingBullet::ChargingBullet()
{
	_bullet = make_shared<CircleCollider>(15.0f);

	CreateAction(L"Resource/CupHead/weapon/ChargeBullet.png", "Resource/CupHead/weapon/ChargeBullet.xml", "ChargingBullet", Vector2(18.0f, 40.0f), true);

	_transform = make_shared<Transform>();
	_transform->SetParent(_bullet->GetTransform());
	_transform->SetAngle(-PI * 0.5f);
	_transform->SetPosition(Vector2(0.0f, 0.0f));

	_bullet->Update();
	_transform->Update();
}

ChargingBullet::~ChargingBullet()
{
}

void ChargingBullet::Update()
{
	if (!_isActive)
		return;

	// Update the timer
	_timer += DELTA_TIME;

	if (_timer >= _inactiveTime)
	{
		_isActive = false;
		_timer = 0.0f;
	}

	if (_dir.x > 0)
		SetRight();
	if (_dir.x < 0)
		SetLeft();

	_bullet->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	_bullet->Update();

	_action->Update();
	_sprite->Update();
	_transform->Update();
}

void ChargingBullet::Render()
{
	if (!_isActive)
		return;

	_transform->SetBuffer(0);
	_sprite->SetCurClip(_action->GetCurClip());
	_sprite->Render();
	_bullet->Render();
}

void ChargingBullet::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop)
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

void ChargingBullet::Shoot(Vector2 dir, Vector2 startPos)
{
	_isActive = true;

	_action->Play();

	_bullet->GetTransform()->SetPosition(startPos);

	_dir = dir.NormalVector2();
	float angle = _dir.Angle();
	_bullet->GetTransform()->SetAngle(angle);
}

void ChargingBullet::SetLeft()
{
	_sprite->SetLeft();
}

void ChargingBullet::SetRight()
{
	_sprite->SetRight();
}

#include "framework.h"
#include "Gun.h"

#include "../Cup_Bullet.h"

using namespace tinyxml2;

Gun::Gun()
{
	_collider = make_shared<CircleCollider>(30.0f);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}

}

Gun::~Gun()
{
}

void Gun::Update()
{
	if (_selected == false)
		return;

	for (auto& bullet : _bullets)
		bullet->Update();
}

void Gun::Render()
{
	if (_selected == false)
		return;

	for (auto& bullet : _bullets)
		bullet->Render();
}

bool Gun::IsCollision_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetBulletCollider()))
		{
			bullet->_isActive = false;
			EFFECT_PLAY("Hit", bullet->GetPosition());
			return true;
		}
	}

	return false;
}

void Gun::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop)
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

	//shared_ptr<Action> action;
	if (isLoop)
	{
		_action = make_shared<Action>(clips, actionName);
	}
	else
	{
		_action = make_shared<Action>(clips, actionName, Action::Type::END, 0.1f);
	}
	_action->Play();
	_gun = make_shared<Sprite>(srvPath, size);
}

void Gun::SetRight()
{
	_gun->SetRight();
}

void Gun::SetLeft()
{
	_gun->SetLeft();
}

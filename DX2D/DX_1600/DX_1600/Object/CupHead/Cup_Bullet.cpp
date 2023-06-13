#include "framework.h"
#include "Cup_Bullet.h"

using namespace tinyxml2;

Cup_Bullet::Cup_Bullet()
{
	_bullet = make_shared<CircleCollider>(5.0f);

	CreateAction(L"Resource/CupHead/Bullet_Intro.png", "Resource/CupHead/Bullet_Intro.xml", "IntroBullet", Vector2(100.0f, 100.0f), Action::END);
	CreateAction(L"Resource/CupHead/Bullet_Loop.png", "Resource/CupHead/Bullet_Loop.xml", "LoopBullet", Vector2(100.0f, 100.0f), Action::LOOP);

	_transform = make_shared<Transform>();
	_transform->SetParent(_bullet->GetTransform());
	_transform->SetAngle(-PI * 0.5f);
	_transform->SetPosition(Vector2(-50.0f, 0.0f));

	_actions[INTRO]->SetEndEvent(std::bind(&Cup_Bullet::EndEvent, this));
}

Cup_Bullet::~Cup_Bullet()
{
}

void Cup_Bullet::Update()
{
	if (!_isActive)
		return;

	_bullet->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	
	_bullet->Update();

	if (_bullet->GetTransform()->GetWorldPosition().y > WIN_HEIGHT || _bullet->GetTransform()->GetWorldPosition().y < 0
		|| _bullet->GetTransform()->GetWorldPosition().x > WIN_WIDTH || _bullet->GetTransform()->GetWorldPosition().x < 0)
	{
		_isActive = false;
		_isEnd = false;
	}

	_actions[_state]->Update();
	_sprites[_state]->Update();
	_transform->Update();
}

void Cup_Bullet::Render()
{
	if (!_isActive)
		return;

	_transform->SetBuffer(0);
	_sprites[_state]->SetCurFrame(_actions[_state]->GetCurClip());
	_sprites[_state]->Render();
	_bullet->Render();
}

void Cup_Bullet::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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

	shared_ptr<Action> action = make_shared<Action>(clips, actionName);
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);
	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Bullet::Shoot(Vector2 dir, Vector2 startPos)
{
	_isActive = true;
	_state = INTRO;
	_actions[_state]->Play();
	_actions[LOOP]->Reset();

	_bullet->GetTransform()->SetPosition(startPos);

	if (dir.x > 0.0f)
	{
		_dir = RIGHT_VECTOR;
		SetRight();
	}
	else
	{
		_dir = LEFT_VECTOR;
		SetLeft();
	}
}

void Cup_Bullet::EndEvent()
{
	_state = LOOP;
	_actions[LOOP]->Play();
}

void Cup_Bullet::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Bullet::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}

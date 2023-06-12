#include "framework.h"
#include "Cup_Player.h"

#include "Cup_Bullet.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	_col = make_shared<CircleCollider>(50);

	//CreateAction(L"Resource/CupHead/Idle.png", "Resource/Idle.xml", "IDLE", Vector2(250, 250));

	CreateIdleAction();
	CreateRunAction();
	CreateJumpAction();

	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0,9.876));
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Input();
	SelectState();
	_col->Update();

	_actions[_state]->Update();
	_sprites[_state]->Update();
	
	_transform->Update();

	for (auto bullet : _bullets)
		bullet->Update();
}

void Cup_Player::Render()
{
	_transform->SetBuffer(0);
	
	_sprites[_state]->SetCurFrame(_actions[_state]->GetCurClip());
	_sprites[_state]->Render();

	_col->Render();
}

void Cup_Player::PostRender()
{
	//ImGui::SliderFloat2("FixedPos", (float*)&_fixedPos,0,100);
	//_transform->SetPosition(_fixedPos);
}

void Cup_Player::CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size)
{
	wstring srvPath = srvpath;
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = xmlpath;
	document->LoadFile(path.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;

	while (true)
	{
		if(row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x,y,w,h,srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, "CUP_IDLE");
	action->Play();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvpath, size);
	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Player::CreateIdleAction()
{
	wstring srvPath = L"Resource/CupHead/Idle.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Idle.xml";
	document->LoadFile(path.c_str());

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

	shared_ptr<Action> action = make_shared<Action>(clips, "CUP_IDLE");
	action->Play();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, Vector2(250, 250));
	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Player::CreateRunAction()
{
	wstring srvPath = L"Resource/CupHead/Run.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Run.xml";
	document->LoadFile(path.c_str());

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

	shared_ptr<Action> action = make_shared<Action>(clips, "CUP_RUN");
	action->Play();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, Vector2(120, 120));
	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Player::CreateJumpAction()
{
	wstring srvPath = L"Resource/CupHead/Jump.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Jump.xml";
	document->LoadFile(path.c_str());

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

	shared_ptr<Action> action = make_shared<Action>(clips, "CUP_RUN");
	action->Play();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, Vector2(120, 120));
	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Player::SelectState()
{
	if (!_isJump)
	{
		if (KEY_UP('A'))
		{
			_state = State::IDLE;
		}

		if (KEY_UP('D'))
		{
			_state = State::IDLE;
		}


		if (KEY_PRESS('A'))
		{
			_state = State::RUN_R;
			SetLeft();
		}

		if (KEY_PRESS('D'))
		{
			_state = State::RUN_R;
			SetRight();
		}
	}
	if (_isJump)
	{
		if (KEY_PRESS('A'))
		{
			_state = State::JUMP;
			SetLeft();
		}

		if (KEY_PRESS('D'))
		{
			_state = State::JUMP;
			SetRight();
		}

	}
}

void Cup_Player::Input()
{
	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	Jump();
}

void Cup_Player::Jump()
{
	// 중력적용
	{
		_jumpPower -= 15;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_col->GetTransform()->AddVector2(Vector2(0, 1) * _jumpPower * DELTA_TIME);
	}

	if (KEY_DOWN(VK_SPACE))
	{
		if (_isJump)
			return;

		_jumpPower = 500.0f;
		_isJump = true;
	}
}

void Cup_Player::AnimationControl()
{
	if (abs(_jumpPower) > 800.0f)
		return;
}

void Cup_Player::SetBowAngle()
{
	Vector2 playerToMouse = MOUSE_POS - GetPos();
	float angle = playerToMouse.Angle();
	_bowSlot->SetAngle(angle);
}

bool Cup_Player::IsCollision_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetBulletCollider()))
		{
			bullet->_isActive = false;
			return true;
		}
	}

	return false;
}

void Cup_Player::Fire()
{
	Vector2 dir = MOUSE_POS - GetPos();

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Cup_Bullet> obj)-> bool { return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	(*bulletIter)->Shoot(dir, _bowTrans->GetWorldPosition());
}

void Cup_Player::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Player::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}

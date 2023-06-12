#include "framework.h"
#include "Cup_Player.h"
#include "Cup_Bullet.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	_col = make_shared<CircleCollider>(50);

	CreateAction(L"Resource/CupHead/Idle.png", "Resource/CupHead/Idle.xml", "IDLE", Vector2(250, 250), Action::LOOP);
	CreateAction(L"Resource/CupHead/Jump.png", "Resource/CupHead/Jump.xml", "JUMP", Vector2(100, 100), Action::LOOP);
	CreateAction(L"Resource/CupHead/Run.png", "Resource/CupHead/Run.xml", "RUN", Vector2(100, 130), Action::LOOP);
	CreateAction(L"Resource/CupHead/Attack.png", "Resource/CupHead/Attack.xml", "ATTACK", Vector2(100, 130), Action::END, std::bind(&Cup_Player::Attack, this));

	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0,9.876));

	SetAction(IDLE);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Input();
	Jump();

	_col->Update();

	_actions[_curState]->Update();
	_sprites[_curState]->Update();
	_transform->Update();

	for (auto bullet : _bullets)
		bullet->Update();
}

void Cup_Player::Render()
{
	_transform->SetBuffer(0);
	
	_sprites[_curState]->SetCurFrame(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_col->Render();

	for (auto bullet : _bullets)
		bullet->Render();
}

void Cup_Player::PostRender()
{
	ImGui::SliderInt("State", (int*)&_curState, 0, 3);
}

void Cup_Player::CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvpath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = xmlpath;
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

	shared_ptr<Action> action = make_shared<Action>(clips, "CUP_IDLE");
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvpath, size);

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Player::Input()
{
	if (KEY_DOWN('F') && _isAttack == false && _isJump == false)
	{
		_isAttack = true;
		SetAction(ATTACK);
	}

	if (KEY_PRESS('A'))
	{
		Move(LEFT_VECTOR);
		SetLeft();
		_isRight = false;
	}

	if (KEY_PRESS('D'))
	{
		Move(RIGHT_VECTOR);
		SetRight();
		_isRight = true;
	}

	if (KEY_DOWN(VK_SPACE) && _isJump == false)
	{
		_jumpPower = 500.0f;
		_isJump = true;
	}

	if (_curState != RUN && _curState != IDLE)
		return;

	if (KEY_PRESS('A') || KEY_PRESS('D'))
		SetAction(RUN);
	else if (_curState == RUN)
		SetAction(IDLE);
}

void Cup_Player::Jump()
{
	if (_isJump == true)
		SetAction(JUMP);
	else if (_curState == JUMP && _isJump == false)
		SetAction(IDLE);

	// 중력적용
	{
		_jumpPower -= 15;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_col->GetTransform()->AddVector2(Vector2(0, 1) * _jumpPower * DELTA_TIME);
	}
}

void Cup_Player::Attack()
{
	_isAttack = false;
	SetAction(IDLE);

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Cup_Bullet> obj)-> bool { return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	if(_isRight)
	(*bulletIter)->Shoot(RIGHT_VECTOR, _col->GetTransform()->GetWorldPosition());

	if (!_isRight)
		(*bulletIter)->Shoot(RIGHT_VECTOR, _col->GetTransform()->GetWorldPosition());
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

void Cup_Player::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
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

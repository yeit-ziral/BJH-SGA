#include "framework.h"
#include "Link.h"

Link::Link()
{
	CreateActionFront();
	CreateActionBack();
	CreateActionRight();
	CreateActionLeft();

	Vector2 size = ADD_SRV(L"Resource/Link.png")->GetImageSize();
	size.x /= 10;
	size.y /= 8;
	_sprite = make_shared<Sprite>(L"Resource/Link.png", Vector2(10, 8), size);
	_transform = make_shared<Transform>();
	_collider = make_shared<RectCollider>(size);

	_transform->SetPosition(CENTER);

	// Listner 패턴, Observer 패턴, 구독자 패턴
	//for (int i = 0; i < 4; i++)
	//{
	//	_actions[i]->SetEndEvent(std::bind(&Link::EndEvent, this)); // 멤버함수에 필요한 객체와 함수를 묶어서 보내 줌
	//}
	_curAction = &_actions[0];

	_hp = 100;
	_atk = 5;
}

Link::~Link()
{
}

void Link::Update()
{
	SelectDir();
	_sprite->Update();
	_transform->Update();
	(*_curAction)->Update();
}

void Link::Collider_Update()
{
	_collider->Update();
}

void Link::Render()
{
	_transform->SetBuffer(0);
	_sprite->SetCurFrame((*_curAction)->GetCurClip());
	_sprite->Render();
}

void Link::PostRender()
{
	if (_isEnd)
		ImGui::Text("EndEvent!!.");
}

void Link::CreateActionFront()
{
	// 앞으로 걸어가는 액션
	vector<Action::Clip> clips;
	{
		shared_ptr<SRV> srv = ADD_SRV(L"Resource/Link.png");
		Vector2 imageSize = srv->GetImageSize();
		Vector2 maxFrame = { 10,8 };
		float w = imageSize.x / maxFrame.x;
		float h = imageSize.y / maxFrame.y;

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, h * 4, w, h, srv);
			clips.push_back(clip1);
		}
	}

	shared_ptr<Action> _action = make_shared<Action>(clips, "RUN_F", Action::Type::LOOP);

	_actions.push_back(_action);
}

void Link::CreateActionBack()
{
	// 뒤로 걸어가는 액션
	vector<Action::Clip> clips;
	{
		shared_ptr<SRV> srv = ADD_SRV(L"Resource/Link.png");
		Vector2 imageSize = srv->GetImageSize();
		Vector2 maxFrame = { 10,8 };
		float w = imageSize.x / maxFrame.x;
		float h = imageSize.y / maxFrame.y;

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, h * 6, w, h, srv);
			clips.push_back(clip1);
		}
	}

	shared_ptr<Action> _action = make_shared<Action>(clips, "RUN_F", Action::Type::LOOP);

	_actions.push_back(_action);
}

void Link::CreateActionRight()
{
	// 오른쪽으로 걸어가는 액션
	vector<Action::Clip> clips;
	{
		shared_ptr<SRV> srv = ADD_SRV(L"Resource/Link.png");
		Vector2 imageSize = srv->GetImageSize();
		Vector2 maxFrame = { 10,8 };
		float w = imageSize.x / maxFrame.x;
		float h = imageSize.y / maxFrame.y;

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, h * 7, w, h, srv);
			clips.push_back(clip1);
		}
	}

	shared_ptr<Action> _action = make_shared<Action>(clips, "RUN_F", Action::Type::LOOP);

	_actions.push_back(_action);
}

void Link::CreateActionLeft()
{
	// 왼쪽으로 걸어가는 액션
	vector<Action::Clip> clips;
	{
		shared_ptr<SRV> srv = ADD_SRV(L"Resource/Link.png");
		Vector2 imageSize = srv->GetImageSize();
		Vector2 maxFrame = { 10,8 };
		float w = imageSize.x / maxFrame.x;
		float h = imageSize.y / maxFrame.y;

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, h * 5, w, h, srv);
			clips.push_back(clip1);
		}
	}

	shared_ptr<Action> _action = make_shared<Action>(clips, "RUN_F", Action::Type::LOOP);

	_actions.push_back(_action);
}

void Link::SelectDir()
{
	// 앞으로 움직이기
	if (KEY_DOWN('S'))
	{
		_actions[0]->Play();
		_isEnd = false;
		_curAction = &_actions[0];
	}
	else if (KEY_PRESS('S'))
	{
		Vector2 movePos = Vector2(0.0f, -50.0f) * DELTA_TIME;
		_transform->SetPosition(_transform->GetWorldPosition() + movePos);
	}
	else if (KEY_UP('S'))
	{
		_actions[0]->Reset();
	}

	// 뒤로 움직이기
	if(KEY_DOWN('W'))
	{
		_actions[1]->Play();
		_isEnd = false;
		_curAction = &_actions[1];
	}
	else if (KEY_PRESS('W'))
	{
		Vector2 movePos = Vector2(0.0f, 50.0f) * DELTA_TIME;
		_transform->SetPosition(_transform->GetWorldPosition() + movePos);
	}
	else if (KEY_UP('W'))
	{
		_actions[1]->Reset();
	}

	// 오른쪽으로 움직이기
	if(KEY_DOWN('D'))
	{
		_actions[2]->Play();
		_isEnd = false;
		_curAction = &_actions[2];
	}
	else if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(50.0f, 0.0f) * DELTA_TIME;
		_transform->SetPosition(_transform->GetWorldPosition() + movePos);
	}
	else if (KEY_UP('D'))
	{
		_actions[2]->Reset();
	}

	// 왼쪽으로 움직이기
	if(KEY_DOWN('A'))
	{
		_actions[3]->Play();
		_isEnd = false;
		_curAction = &_actions[3];
	}
	else if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-50.0f, 0.0f) * DELTA_TIME;
		_transform->SetPosition(_transform->GetWorldPosition() + movePos);
	}
	else if (KEY_UP('A'))
	{
		_actions[3]->Reset();
	}
}
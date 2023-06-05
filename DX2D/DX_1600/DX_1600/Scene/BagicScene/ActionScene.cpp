#include "framework.h"
#include "ActionScene.h"

ActionScene::ActionScene()
{

	Vector2 size = ADD_SRV(L"Resource/Link.png")->GetImageSize();
	size.x /= 10;
	size.y /= 8;
	_sprite = make_shared<Sprite>(L"Resource/Link.png", Vector2(10, 8), size);
	_transform = make_shared<Transform>();

	_transform->SetPosition(CENTER);

	// Listner ����, Observer ����, ������ ����
	_action->SetEndEvent(std::bind(&ActionScene::EndEvent, this)); // ����Լ��� �ʿ��� ��ü�� �Լ��� ��� ���� ��
}

ActionScene::~ActionScene()
{
}

void ActionScene::Update()
{
	_sprite->Update();
	_transform->Update();
	_action->Update();
}

void ActionScene::Render()
{
	_transform->SetBuffer(0);
	_sprite->SetCurFrame(_action->GetCurClip());
	_sprite->Render();
}

void ActionScene::PostRender()
{
	if (_isEnd)
		ImGui::Text("EndEvent!!.");
}

void ActionScene::CreateAction()
{
	if (KEY_PRESS('W'))
	{
		// ������ �ɾ�� �׼�
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
	
		_action = make_shared<Action>(clips, "RUN_F", Action::Type::END);
		_action->Play();
	}
}

void ActionScene::CreateActionBack()
{
	if (KEY_PRESS('S'))
	{

	// �ڷ� �ɾ�� �׼�
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

	_action = make_shared<Action>(clips, "RUN_F", Action::Type::END);
	_action->Play();
	}
}

void ActionScene::CreateActionRight()
{
	if (KEY_PRESS('D'))
	{
	// ���������� �ɾ�� �׼�
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

	_action = make_shared<Action>(clips, "RUN_F", Action::Type::END);
	_action->Play();
	}
}

void ActionScene::CreateActionLeft()
{
	if (KEY_PRESS('A'))
	{
	// �������� �ɾ�� �׼�
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

	_action = make_shared<Action>(clips, "RUN_F", Action::Type::END);
	_action->Play();
	}
}

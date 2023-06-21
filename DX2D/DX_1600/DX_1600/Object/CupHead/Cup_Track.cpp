#include "framework.h"
#include "Cup_Track.h"

Cup_Track::Cup_Track()
{
	_track = make_shared<Quad>(L"Resource/CupHead/clown_bg_track.png");
	_transform = make_shared<Transform>();
	trackSize = _track->GetQuadHalfSize() * 2.0f;
	_col = make_shared<RectCollider>(trackSize);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 75));
	_col->GetTransform()->SetPosition(Vector2(0.0f, CENTER.y * -1));
}

Cup_Track::~Cup_Track()
{
}

void Cup_Track::Update()
{
	_transform->Update();
	_col->Update();
}

void Cup_Track::Render()
{
	_transform->SetBuffer(0);
	_track->Render();
	_col->Render();
}

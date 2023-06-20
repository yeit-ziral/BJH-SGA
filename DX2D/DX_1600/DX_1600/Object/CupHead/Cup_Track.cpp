#include "framework.h"
#include "Cup_Track.h"

Cup_Track::Cup_Track()
{
	_track = make_shared<Quad>(L"Resource/CupHead/clown_bg_track.png");
	_transform = make_shared<Transform>();
	trackSize = Vector2(_track->GetImageSize().x, _track->GetQuadHalfSize().y);
	_col = make_shared<RectCollider>(trackSize * 2.0f);

	_transform->SetParent(_col->GetTransform());

	_transform->Update();
}

Cup_Track::~Cup_Track()
{
}

void Cup_Track::Update()
{
	_col->Update();
}

void Cup_Track::Render()
{
	_transform->SetBuffer(0);
	_track->Render();
	_col->Render();
}

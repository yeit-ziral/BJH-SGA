#pragma once
class DungreedScene : public Scene
{
public:
	DungreedScene();
	virtual ~DungreedScene();

	virtual void Collider_Update() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class Dun_Monster> _monster;
	shared_ptr<class Dun_Player_Advanced> _player;
	shared_ptr<class Dun_Ground> _ground;
	shared_ptr<RectCollider> _floor;
};


#pragma once
class DungreedScene : public Scene
{
public:
	DungreedScene();
	virtual ~DungreedScene();

	virtual void Update();
	virtual void Render();

private:
	shared_ptr<Player> _player;
};


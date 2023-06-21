#pragma once
class CupHeadScene : public Scene
{
public:
	CupHeadScene();
	virtual ~CupHeadScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CheckAttack();

private:
	shared_ptr<class Cup_Player> _player;

	shared_ptr<class Cup_Track> _track;
	shared_ptr<class Cup_Track> _track2;

	shared_ptr<class Cup_Monster> _monster;

	shared_ptr<ActionFilterBuffer> _AFBuffer;

	shared_ptr<Effect> _effect;
};


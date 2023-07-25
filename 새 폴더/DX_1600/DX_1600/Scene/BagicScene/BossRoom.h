#pragma once
class BossRoom : public Scene
{
public:
	BossRoom();
	virtual ~BossRoom();

	virtual void Init() override;
	virtual void End() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CheckAttack();

	void Save();
	void Load();

private:
	shared_ptr<class Cup_Player> _player;

	shared_ptr<class Cup_Track> _track;
	shared_ptr<class Cup_Block> _block;

	shared_ptr<class Cup_Boss> _monster;

	shared_ptr<Button> _button;

	shared_ptr<ActionFilterBuffer> _AFBuffer;

	shared_ptr<Effect> _effect;
};


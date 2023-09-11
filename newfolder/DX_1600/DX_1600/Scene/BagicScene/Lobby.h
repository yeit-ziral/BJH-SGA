#pragma once
class Lobby : public Scene
{
public:
	Lobby();
	virtual ~Lobby();

	virtual void Init() override;
	virtual void End() override;
	virtual void Update() override;
	virtual void Render() override;

	void Save();
	void Load();

private:
	//shared_ptr<class Cup_Player> _player;

	shared_ptr<class Cup_Track> _track;

	shared_ptr<class Potal> _potal;

	shared_ptr<class HPBar> _hpBar;

	shared_ptr<class HPBar> _gunHpBar;

	//shared_ptr<class inventory> _inven;

	shared_ptr<class Helmet> _helmet;
	shared_ptr<class KingBullet> _kingBullet;
	shared_ptr<class Scope> _scope;
	shared_ptr<class SpeedBoots> _speedBoots;

	shared_ptr<class HpPotion> _hpPotion;
	shared_ptr<class FixingTool> _fixingTool;

	shared_ptr<class RandomBox> _randomBox;
};
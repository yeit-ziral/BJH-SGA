#pragma once
class RandomBox
{
public:
	enum class ItemState
	{
		NONE,
		FIXINGTOOL,
		HELMET,
		HPPOTION,
		KINGBULLET,
		SCOPE,
		SPEEDBOOTS
	};

	RandomBox();
	~RandomBox();

	void Update();
	void Render();

	int RandomNum(int min, int max);
	void SetRandomItem();
	void SetItemStateNone() { _itemState = ItemState::NONE; }

	shared_ptr<Transform> GetTransform() { return _transform; }

	bool _isActive = false;

	bool IsCollision(Cup_Player* a);

private:
	shared_ptr<class FixingTool> _fixingTool;
	shared_ptr<class Helmet> _helmet;
	shared_ptr<class HpPotion> _hpPotion;
	shared_ptr<class KingBullet> _kingBullet;
	shared_ptr<class Scope> _scope;
	shared_ptr<class SpeedBoots> _speedBoots;

	ItemState _itemState = ItemState::NONE;

	shared_ptr<Transform> _transform;

	int randNum = 0;
};


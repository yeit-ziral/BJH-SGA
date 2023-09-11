#pragma once
class RandomBox
{
public:
	RandomBox();
	~RandomBox();

	void Update();
	void Render();



private:
	shared_ptr<class FixingTool> _fixingTool;
	shared_ptr<class Helmet> _helmet;
	shared_ptr<class HpPotion> _hpPotion;
	shared_ptr<class KingBullet> _kingBullet;
	shared_ptr<class 

};


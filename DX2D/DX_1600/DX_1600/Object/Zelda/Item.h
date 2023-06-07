#pragma once
class Item
{
public:
	Item(wstring path, Vector2 maxFrame, Vector2 size);
	~Item();

	void Update();
	void Render();
	void PostRender();

	int GetHp() { return _hp; }
	int SetHp(int value) { _hp += value; }

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _transform;

	int _hp;
};


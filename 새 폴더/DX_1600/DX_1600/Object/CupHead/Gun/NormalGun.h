#pragma once
class NormalGun : public Gun
{
public:
	NormalGun();
	virtual ~NormalGun();

	virtual void Update();
	virtual void Render();

	void Fire(Vector2 dir);

	void Selected(bool Bool) { _selected = Bool; }

private:

};
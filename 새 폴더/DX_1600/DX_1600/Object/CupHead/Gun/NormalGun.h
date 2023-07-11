#pragma once
class NormalGun : public Gun
{
public:
	NormalGun();
	virtual ~NormalGun();

	virtual void Update();
	virtual void Render();

	virtual void Fire()override;

	void Selected(bool Bool) { _selected = Bool; }

private:

};
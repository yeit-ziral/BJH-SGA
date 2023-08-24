#pragma once
class Machinegun : public Gun
{
public:
	Machinegun();
	virtual ~Machinegun();

	virtual void Update();
	virtual void Render();

	void Fire(Vector2 dir);

	void Selected(bool Bool) { _selected = Bool; }

private:

};
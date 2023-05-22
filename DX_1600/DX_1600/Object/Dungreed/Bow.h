#pragma once
class Bow
{
public:
	Bow();
	~Bow();

	void Update();
	void Render();

	shared_ptr<Transform> parent;

private:
	
};
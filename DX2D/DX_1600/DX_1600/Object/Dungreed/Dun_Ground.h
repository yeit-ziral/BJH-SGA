#pragma once
class Dun_Ground
{
public:
	Dun_Ground();
	~Dun_Ground();

	void Update();
	void Render();

	shared_ptr<RectCollider> GetGroundCollider() { return _ground; }

private:
	shared_ptr<RectCollider> _ground;
};


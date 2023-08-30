#pragma once
class SpeedBoots
{
public:
	SpeedBoots();
	~SpeedBoots();

	void Update();
	void Render();

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
};


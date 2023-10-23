#pragma once
class Zombie : public ModelAnimator
{
public:
	Zombie();
	~Zombie();

	void Update();
	void Render();

	void Debug();

	void UpdateLeftHand();

private:

	float speed = 1.0f;
	float takeTime = 0.2f;

	class Knife_A* weapon;

	Transform* leftHand;
};
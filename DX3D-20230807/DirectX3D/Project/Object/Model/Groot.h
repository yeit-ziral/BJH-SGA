#pragma once
class Groot : public ModelAnimator
{
public:
	Groot();
	~Groot();

	void Update();
	void Render();

	void Debug();

	void UpdateLeftHand();

private:

	float speed = 1.0f;
	float takeTime = 0.2f;

	Sphere* weapon;

	Transform* leftHand;
};
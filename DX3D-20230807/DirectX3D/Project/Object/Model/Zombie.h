#pragma once
class Zombie : public ModelAnimator
{
	enum AnimState
	{
		IDLE, RUN, ATTACK
	}; 
	AnimState curState = AnimState::IDLE;
public:
	Zombie();
	~Zombie();

	void Update();
	void Render();

	void Debug();

	void UpdateLeftHand();

	void SetClip(AnimState state);

private:

	float speed = 1.0f;
	float takeTime = 0.2f;

	class Knife_A* weapon;

	Transform* leftHand;
};
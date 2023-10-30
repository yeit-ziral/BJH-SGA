#pragma once
class Groot : public ModelAnimator
{
	enum AnimState
	{
		IDLE, RUN, ATTACK
	} curState = IDLE;
public:
	Groot();
	~Groot();

	void Update();
	void Render();

	void Debug();

	void UpdateLeftHand();

	void SetClip(AnimState state);

private:
	void Move();

private:

	float speed = 1.0f;
	float takeTime = 0.2f;

	Model* weapon;

	Transform* leftHand;

	float moveSpeed = 20.0f;

	float rotSpeed = 3.0f;

	ProgressBar* hpBar;
};
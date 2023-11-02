#pragma once
class ModelClip // �ִϸ��̼� �ϳ� �������
{
	friend class ModelAnimator;
	friend class ModelAnimatorInstancing;
public:
	ModelClip();
	~ModelClip();

	KeyFrame* GetKeyFrames(string name);

	void SetEndEvent(function<void()> EndEvent, float ratio)
	{
		this->EndEvent	= EndEvent;

		this->ratio		= ratio;
	}
	
private:
	string name = "";

	UINT frameCount = 0;

	float ticksPerSecond = 0.0f;
	float duration		 = 0.0f;

	unordered_map<string, KeyFrame*> keyFrames = {};

	function<void()> EndEvent;

	float ratio;
};
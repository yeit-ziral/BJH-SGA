#pragma once
class ModelClip // 애니메이션 하나 들고있음
{
public:
	ModelClip();
	~ModelClip();

	KeyFrame* GetKeyFrames(string name);
	
private:
	string name = "";

	UINT frameCount = 0;

	float ticksPerSecond = 0.0f;
	float duration		 = 0.0f;

	unordered_map<string, KeyFrame*> keyFrames;
};
#pragma once
class ModelAnimator
{
public:
	ModelAnimator();
	~ModelAnimator();

	void ReadClip(string file, UINT clipIndex = 0); // 하나짜리가 많아서 clipIndex 기본값을 0으로 함

private:
	ModelReader* reader;

	vector<ModelClip*> clips;
};
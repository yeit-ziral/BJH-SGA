#pragma once
class ModelAnimator
{
public:
	ModelAnimator();
	~ModelAnimator();

	void ReadClip(string file, UINT clipIndex = 0); // �ϳ�¥���� ���Ƽ� clipIndex �⺻���� 0���� ��

private:
	ModelReader* reader;

	vector<ModelClip*> clips;
};
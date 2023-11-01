#pragma once
class InstancingScene : public Scene
{
	struct InstanceData
	{
		Matrix transform;

		Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
public:
	InstancingScene();
	~InstancingScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	//vector<Quad*> quads;

	const UINT COUNT = 50;

	Quad* quad;

	vector<InstanceData> instanceData;

	VertexBuffer* instanceBuffer;
};
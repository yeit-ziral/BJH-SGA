#pragma once
class DeferredRenderScene : public Scene
{
public:
	DeferredRenderScene(); // 늦게 연산시킴 -> 2D 화면에 보이는 곳 만 light 계산을 함 => 연산량이 줄어듬 , 알파 적용이 힘듬
	~DeferredRenderScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	void CreateObjects();

private:
	Quad* floor;
	Groot* groot;
	Model* bunny;
	Sphere* sphere;

	GeometryBuffer* gBuffer;

	Material* material;
	VertexBuffer* vertexBuffer;
};
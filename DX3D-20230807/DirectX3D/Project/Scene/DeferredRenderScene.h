#pragma once
class DeferredRenderScene : public Scene
{
public:
	DeferredRenderScene(); // �ʰ� �����Ŵ -> 2D ȭ�鿡 ���̴� �� �� light ����� �� => ���귮�� �پ�� , ���� ������ ����
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
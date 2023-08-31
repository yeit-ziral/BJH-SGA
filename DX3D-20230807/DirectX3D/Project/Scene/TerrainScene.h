#pragma once
class TerrainScene : public Scene
{
public:
	TerrainScene();
	~TerrainScene();

	void CreateMesh();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	vector<VertexTexture> vertices;
	vector<UINT>		  indices;

	Material* material;
	Mesh* mesh;

	MatrixBuffer* worldBuffer;

	UINT width  = 10;
	UINT height = 10;

	Texture* heightMap;

	const float MAP_HEIGHT = 20.0f;
};
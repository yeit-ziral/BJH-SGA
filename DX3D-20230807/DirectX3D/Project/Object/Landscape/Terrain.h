#pragma once
class Terrain : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Terrain(wstring diffuseFile, wstring heightFile);
	~Terrain();

	void Render();

	Material* GetMaterial() { return material; }

private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();

private:
	vector<VertexType> vertices;
	vector<UINT>				indices;

	Material* material;
	Mesh* mesh;

	MatrixBuffer* worldBuffer;

	UINT width = 10;
	UINT height = 10;

	Texture* heightMap;

	const float MAP_HEIGHT = 20.0f;
};
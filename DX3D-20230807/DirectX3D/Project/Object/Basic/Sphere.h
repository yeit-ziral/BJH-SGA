#pragma once
class Sphere : public Transform
{
	typedef VertexTextureNormal VertexType;
public:
	Sphere(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	~Sphere();

	void Update();
	void Render();

	Material* GetMaterial() { return material; }

private:
	void CreateMesh();


private:
	MatrixBuffer* worldBuffer = nullptr;

	vector<VertexType> vertices;
	vector<UINT> indices;

	Material*	material = nullptr;
	Mesh*		mesh	 = nullptr;

	UINT sliceCount = 25;
	UINT stackCount = 25;
	float radius;
};

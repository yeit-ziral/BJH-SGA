#pragma once
class Sphere : public Transform
{
public:
	Sphere(Vector4 color, float radius);
	~Sphere();

	void Update();
	void Render();

	float Ridan(float value) { return value * XM_PI / 180; }

	void CreateMesh(Vector4 color);
	void CreateNormal();

private:
	MatrixBuffer* worldBuffer;

	vector<VertexColorNormal> vertices;
	vector<UINT> indices;

	Material* material;
	Mesh* mesh;

	UINT latitudes = 25;
	UINT longitudes = 25;
	float radius;
};

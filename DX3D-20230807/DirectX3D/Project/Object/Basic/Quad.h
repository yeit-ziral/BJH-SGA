#pragma once
class Quad : public Transform
{
public:
	Quad(Vector2 size = {1,1});
	Quad(vector<Vector3> points);
	Quad(wstring file);
	~Quad();

	void Render();

	Material* GetMaterial() { return material; }

protected:
	Material* material = nullptr;
	Mesh*	  mesh	   = nullptr;

	vector<VertexTextureNormal> vertices;
	vector<UINT>				indices;


	MatrixBuffer* worldBuffer = nullptr;
};
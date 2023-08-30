#pragma once
class Quad : public Transform
{
public:
	Quad(Vector2 size = {1,1});
	Quad(vector<Vector3> points);
	~Quad();

	void Render();

private:
	Material* material = nullptr;
	Mesh*	  mesh	   = nullptr;

	vector<VertexTexture> vertices;
	vector<UINT>		  indices;


	MatrixBuffer* worldBuffer = nullptr;
};
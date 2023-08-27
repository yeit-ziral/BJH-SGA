#pragma once
class Cube : public Transform // 부모클래스여서 간접접근하지 않아도 됨
{
public:
	Cube(Vector4 color);
	~Cube();

    void Update();
    void Render();

    void CreateMesh(Vector4 color);

    void Debug();

    bool _pendulumMovement = false;

private:
    Material* material;

    Mesh* mesh;

    MatrixBuffer* worldBuffer;

    vector<VertexColor> vertices;
    vector<UINT> indices;

    static int count;

    string label = "";
};


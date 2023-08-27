#pragma once
class Cube : public Transform // �θ�Ŭ�������� ������������ �ʾƵ� ��
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


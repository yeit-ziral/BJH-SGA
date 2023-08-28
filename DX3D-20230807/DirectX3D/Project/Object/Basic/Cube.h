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

    // 6�� ���� ������
    vector<Vector3> GetTopVertices() 
    {
        vector<Vector3> a = { vertices[0].pos, vertices[1].pos, vertices[2].pos, vertices[3].pos };

        return a; 
    }

private:
    Material* material;

    Mesh* mesh;

    MatrixBuffer* worldBuffer;

    vector<VertexColor> vertices;
    vector<UINT> indices;

    static int count;

    string label = "";
};


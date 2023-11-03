#include "Framework.h"
#include "Cube.h"

int Cube::count = 0;

Cube::Cube(Vector4 color)
{
    material = new Material(L"Color");

    CreateMesh(color);
    CreateNormal();

    mesh = new Mesh(vertices, indices);

    //WVP

    worldBuffer = new WorldBuffer();

    count++;
}

Cube::~Cube()
{
    delete mesh;
    delete material;

    delete worldBuffer;
}

void Cube::Update()
{
    ////static float angle = 0.0f;
    //
    ////angle += 0.0002f;
    //
    ////XMMATRIX world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f); // RollPitchYaw : Roll->�ٶ󺸴� ������ ������ ȸ��, Pitch->�ٶ󺸴� ���⿡�� �������� ������ ȸ��, Yaw->�ٶ󺸴� ������ ���Ʒ� ������ ������ ȸ��
    //
    //S = XMMatrixScaling(scale.x, scale.y, scale.z);
    ////R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); // Roll -> Pitch -> Yaw ������ ���ư�(z�� ȸ���� ���� �������� �����ؼ� �ٸ� �� ȸ���� ������ ����)
    //
    //XMMATRIX rotX = XMMatrixRotationX(rotation.x);
    //XMMATRIX rotY = XMMatrixRotationY(rotation.y);
    //XMMATRIX rotZ = XMMatrixRotationZ(rotation.z);
    //
    //R = rotX * rotY * rotZ; // Z�� �ֻ��� �θ��� ȸ��, X�� ȸ���� �ٸ� �� ȸ���� ������ �� �� ����.
    //
    //T = XMMatrixTranslation(translation.x, translation.y, translation.z);
    //
    //world = S * R * T;

    Transform::Update();

    worldBuffer->SetData(world);
}

void Cube::Render()
{
    material->SetMaterial();
        mesh->SetMesh();
     //������� �����ϴ� �ܰ�
    //WVP
    worldBuffer->SetVSBuffer(0);


    // Draw
    //deviceContext->Draw(vertices.size(), 0); // Draw���� ������ ����
    DC->DrawIndexed(indices.size(), 0, 0); //index�� Draw���� ������ ����


}

void Cube::CreateMesh(Vector4 color)
{
    //Vertex
 //Vertex vertex(0.0f, 0.0f, 0.0f);
    vertices =
    {
        VertexType({-0.5f, +0.5f, -0.5f}, color, Vector3()),
        VertexType({+0.5f, +0.5f, -0.5f}, color, Vector3()),
        VertexType({-0.5f, -0.5f, -0.5f}, color, Vector3()),
        VertexType({+0.5f, -0.5f, -0.5f}, color, Vector3()),  

        VertexType({-0.5f, +0.5f, +0.5f}, color, Vector3()),
        VertexType({+0.5f, +0.5f, +0.5f}, color, Vector3()),
        VertexType({-0.5f, -0.5f, +0.5f}, color, Vector3()),
        VertexType({+0.5f, -0.5f, +0.5f}, color, Vector3())
    };
    // ���� ���������� �� �������� �Ÿ��� ����Ͽ� ���� ��� ������

   //VertexBuffer



    //IndexBuffer
    indices =
    {
        //Front
        0,1,2,
        2,1,3,

        //Right
        1, 5, 3,
        3, 5, 7,

        //Top
        0, 4, 1,
        1, 4, 5,

        //Left
        4, 0, 6,
        6, 0, 2,

        //Back
        5, 4, 7,
        7, 4, 6,

        //Bottom
        2, 3, 6,
        6, 3, 7
    };
}

void Cube::CreateNormal()
{
    for (UINT i = 0; i < indices.size() / 3; i++)
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        Vector3 v01 = p1 - p0;
        Vector3 v02 = p2 - p0;

        Vector3 normal = Vector3::Cross(v01, v02).GetNormalized();

        vertices[index0].normal += normal;
        vertices[index1].normal += normal;
        vertices[index2].normal += normal;
    }
}

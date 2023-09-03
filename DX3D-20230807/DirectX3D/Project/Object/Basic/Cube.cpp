#include "Framework.h"
#include "Cube.h"

int Cube::count = 0;

Cube::Cube(Vector4 color)
{
    //material = new Material(L"Tutorial");
    material = new Material();
    material->SetShader(L"Diffuse");

    CreateMesh(color);

    //WVP

    worldBuffer = new MatrixBuffer();
    //worldBuffer = new LightBuffer();

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

    //deviceContext->Draw(vertices.size(), 0); // Draw���� ������ ����
    DC->DrawIndexed(indices.size(), 0, 0); //index�� Draw���� ������ ����


    // Draw

}

void Cube::CreateMesh(Vector4 color)
{
    //Vertex
 //Vertex vertex(0.0f, 0.0f, 0.0f);
    vertices =
    {
        VertexColor({-1.0f, +1.0f, -1.0f}, color),
        VertexColor({+1.0f, +1.0f, -1.0f}, color),
        VertexColor({-1.0f, -1.0f, -1.0f}, color),
        VertexColor({+1.0f, -1.0f, -1.0f}, color),
                                           
        VertexColor({-1.0f, +1.0f, +1.0f}, color),
        VertexColor({+1.0f, +1.0f, +1.0f}, color),
        VertexColor({-1.0f, -1.0f, +1.0f}, color),
        VertexColor({+1.0f, -1.0f, +1.0f}, color)
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

    mesh = new Mesh(vertices, indices);
}

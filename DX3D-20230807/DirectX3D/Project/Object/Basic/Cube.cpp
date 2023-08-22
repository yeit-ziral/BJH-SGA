#include "Framework.h"
#include "Cube.h"

Cube::Cube()
{
    material = new Material(L"Tutorial");

 
    CreateMesh();



    //WVP

    worldBuffer = new MatrixBuffer();
}

Cube::~Cube()
{
    delete mesh;
    delete material;

    delete worldBuffer;
}

void Cube::Update()
{
    //static float angle = 0.0f;

    //angle += 0.0002f;

    //XMMATRIX world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f); // RollPitchYaw : Roll->�ٶ󺸴� ������ ������ ȸ��, Pitch->�ٶ󺸴� ���⿡�� �������� ������ ȸ��, Yaw->�ٶ󺸴� ������ ���Ʒ� ������ ������ ȸ��

    S = XMMatrixScaling(scale.x, scale.y, scale.z);
    R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); // Roll -> Pitch -> Yaw ������ ���ư�(z�� ȸ���� ���� �������� �����ؼ� �ٸ� �� ȸ���� ������ ����)
    T = XMMatrixTranslation(translation.x, translation.y, translation.z);

    world = S * R * T;

    worldBuffer->SetData(world);
}

void Cube::Render()
{
    material->SetMaterial();
        mesh->SetMesh();
     //������� �����ϴ� �ܰ�

    //deviceContext->Draw(vertices.size(), 0); // Draw���� ������ ����
    DC->DrawIndexed(indices.size(), 0, 0); //index�� Draw���� ������ ����


    // Draw
    //WVP
    worldBuffer->SetVSBuffer(0);

}

void Cube::CreateMesh()
{
    //Vertex
 //Vertex vertex(0.0f, 0.0f, 0.0f);
    vertices =
    {
        VertexColor({-1.0f, +1.0f, -1.0f}, {1.0f, 0.0f,0.0f,1.0f}),
        VertexColor({+1.0f, +1.0f, -1.0f}, {0.0f, 1.0f,0.0f,1.0f}),
        VertexColor({-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f,1.0f,1.0f}),
        VertexColor({+1.0f, -1.0f, -1.0f}, {1.0f, 1.0f,1.0f,1.0f}),

        VertexColor({-1.0f, +1.0f, +1.0f}, {1.0f, 0.0f,0.0f,1.0f}),
        VertexColor({+1.0f, +1.0f, +1.0f}, {0.0f, 1.0f,0.0f,1.0f}),
        VertexColor({-1.0f, -1.0f, +1.0f}, {0.0f, 0.0f,1.0f,1.0f}),
        VertexColor({+1.0f, -1.0f, +1.0f}, {1.0f, 1.0f,1.0f,1.0f})
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

void Cube::Debug()
{
    if (ImGui::BeginMenu("Cube"))
    {
        ImGui::DragFloat3("Scale",          (float*)&scale,         0.01f,      0.01f,      100.0f);
        //ImGui::DragFloat3("Rotation",       (float*)&rotation,      0.01f,      -XM_2PI,    XM_2PI);

        ImGui::SliderAngle("RotationX", &rotation.x);
        ImGui::SliderAngle("RotationY", &rotation.y);
        ImGui::SliderAngle("RotationZ", &rotation.z);

        ImGui::DragFloat3("Translation",    (float*)&translation,   0.01f,      -WIN_WIDTH, WIN_WIDTH);



        ImGui::EndMenu();
    }
}

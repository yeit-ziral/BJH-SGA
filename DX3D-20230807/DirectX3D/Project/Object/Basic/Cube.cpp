#include "Framework.h"
#include "Cube.h"

Cube::Cube()
{
    vertexShader = Shader::GetVS(L"Tutorial");
    pixelShader = Shader::GetPS(L"Tutorial");

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
    // 선형 보간법으로 각 정점에서 거리에 비례하여 색을 섞어서 보여줌

   //VertexBuffer
    vertexBuffer = new VertexBuffer(vertices);


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

    indexBuffer = new IndexBuffer(indices);


    //WVP

    worldBuffer = new MatrixBuffer();
}

Cube::~Cube()
{
    delete vertexBuffer;
    delete indexBuffer;

    delete worldBuffer;
}

void Cube::Update()
{
    static float angle = 0.0f;

    angle += 0.0002f;

    XMMATRIX world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f); // RollPitchYaw : Roll->바라보는 방향을 축으로 회전, Pitch->바라보는 방향에서 오른쪽을 축으로 회전, Yaw->바라보는 방향의 위아래 방향을 축으로 회전

    worldBuffer->SetData(world);
}

void Cube::Render()
{
    vertexShader->SetShader();
    pixelShader->SetShader();


    vertexBuffer->IASetBuffer();
    indexBuffer->IASetBuffer();


    // 여기까지는 세팅하는거라서 순서 상관 없음

    //deviceContext->Draw(vertices.size(), 0); // Draw부터 렌더링 시작
    DC->DrawIndexed(indices.size(), 0, 0); //index로 Draw부터 렌더링 시작


    // Draw
    //WVP
    worldBuffer->SetVSBuffer(0);

}

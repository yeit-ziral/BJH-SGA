#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    vertexShader = Shader::GetVS(L"Tutorial");
    pixelShader = Shader::GetPS(L"Tutorial");


    //////////////////////////////////////

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
    viewBuffer = new MatrixBuffer();
    projBuffer = new MatrixBuffer();

    XMVECTOR   eyePos = XMVectorSet(+3.0f, +3.0f, -3.0f, +1.0f);
    XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, +1.0f);
    XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, +0.0f);

    XMMATRIX view = XMMatrixLookAtLH(eyePos, focusPos, upVector);

    viewBuffer->SetData(view);

    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV4, 
        WIN_WIDTH / WIN_HEIGHT, 
        0.1f, 
        1000.0f
    ); //Fov : Fild of view �þ߰�
    
    projBuffer->SetData(projection);
}

TutorialScene::~TutorialScene()
{
    delete vertexBuffer;
    delete indexBuffer;

    delete worldBuffer;
    delete  viewBuffer;
    delete  projBuffer;
}

void TutorialScene::Update()
{
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
    

    //TODO : Render


    

    vertexShader->SetShader();
    pixelShader->SetShader();
    

    vertexBuffer->IASetBuffer();
    indexBuffer->IASetBuffer();


    // ��������� �����ϴ°Ŷ� ���� ��� ����

    //deviceContext->Draw(vertices.size(), 0); // Draw���� ������ ����
    DC->DrawIndexed(indices.size(), 0, 0); //index�� Draw���� ������ ����


    //WVP
    // Draw
    worldBuffer->SetVSBuffer(0);
    viewBuffer->SetVSBuffer(1);
    projBuffer->SetVSBuffer(2);



    static float angle = 0.0f;

    angle += 0.0002f;

    XMMATRIX world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f); // RollPitchYaw : Roll->�ٶ󺸴� ������ ������ ȸ��, Pitch->�ٶ󺸴� ���⿡�� �������� ������ ȸ��, Yaw->�ٶ󺸴� ������ ���Ʒ� ������ ������ ȸ��

    worldBuffer->SetData(world);

    /////////////////////////////////////////


}

void TutorialScene::PostRender()
{
}

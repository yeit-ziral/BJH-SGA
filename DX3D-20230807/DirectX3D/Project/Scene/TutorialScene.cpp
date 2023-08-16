#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
   

    

    /////////////////////////////////////////////////////////

    D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    DC->RSSetViewports(1, &viewPort); // RS니까 Rasterizer State에서 실행, 설정단계라서 OM보다 뒤에 와도 상관 없음


    //VertexShader
    

   



    // PixelShader

    

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
    // 선형 보간법으로 각 정점에서 거리에 비례하여 색을 섞어서 보여줌

   //VertexBuffer
    {
        // vertexBuffer에 담아서 넘김
        D3D11_BUFFER_DESC bufferDesc = {};

        bufferDesc.ByteWidth = sizeof(VertexColor) * vertices.size();
        bufferDesc.Usage = D3D11_USAGE_DEFAULT; // DEFAULT는 CPU에서 정보 수정 불가능
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA data;

        data.pSysMem = vertices.data(); // vertices[0]으로 넘길 수 있지만 이 경우 vertices[0]이 비어있으면 오류가 생김

        DEVICE->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
    }


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

    {
        D3D11_BUFFER_DESC bufferDesc = {};

        bufferDesc.ByteWidth = sizeof(Vertex) * indices.size();
        bufferDesc.Usage = D3D11_USAGE_DEFAULT; // DEFAULT는 CPU에서 정보 수정 불가능
        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA data;

        data.pSysMem = indices.data(); // vertices[0]으로 넘길 수 있지만 이 경우 vertices[0]이 비어있으면 오류가 생김

        DEVICE->CreateBuffer(&bufferDesc, &data, &indexBuffer);
    }


    //WVP

    wvp.world = XMMatrixIdentity();

    XMVECTOR   eyePos = XMVectorSet(+3.0f, +3.0f, -3.0f, +1.0f);
    XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, +1.0f);
    XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, +0.0f);

    wvp.view = XMMatrixLookAtLH(eyePos, focusPos, upVector);

    wvp.projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f); //Fov : Fild of view 시야각

    {
        D3D11_BUFFER_DESC bufferDesc = {};

        bufferDesc.ByteWidth = sizeof(WVP);
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        DEVICE->CreateBuffer(&bufferDesc, nullptr, &constBuffer);
    }
}

TutorialScene::~TutorialScene()
{

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

    stride = sizeof(VertexColor);
    offset = 0;

    DC->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    
    DC->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    

    // 여기까지는 세팅하는거라서 순서 상관 없음

    //deviceContext->Draw(vertices.size(), 0); // Draw부터 렌더링 시작
    DC->DrawIndexed(indices.size(), 0, 0); //index로 Draw부터 렌더링 시작


    //WVP
    WVP data;

    data.world = XMMatrixTranspose(wvp.world);
    data.view = XMMatrixTranspose(wvp.view);
    data.projection = XMMatrixTranspose(wvp.projection);

    DC->UpdateSubresource(constBuffer, 0, nullptr, &data, 0, 0);
    DC->VSSetConstantBuffers(0, 1, &constBuffer);

    static float angle = 0.0f;

    angle += 0.0002f;

    wvp.world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f); // RollPitchYaw : Roll->바라보는 방향을 축으로 회전, Pitch->바라보는 방향에서 오른쪽을 축으로 회전, Yaw->바라보는 방향의 위아래 방향을 축으로 회전


    /////////////////////////////////////////


}

void TutorialScene::PostRender()
{
}

#include "Framework.h"
#include "Enviroment.h"

Enviroment::Enviroment()
{
    CreateViewport();
    CreatePerspective();
}

Enviroment::~Enviroment()
{
    delete  viewBuffer;
    delete  projBuffer;
}

void Enviroment::CreateViewport()
{
    D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    DC->RSSetViewports(1, &viewPort); // RS니까 Rasterizer State에서 실행, 설정단계라서 OM보다 뒤에 와도 상관 없음
}

void Enviroment::CreatePerspective()
{
    viewBuffer = new MatrixBuffer();
    projBuffer = new MatrixBuffer();

    XMVECTOR   eyePos = XMVectorSet(+0.0f, +0.0f, -5.0f, +1.0f);
    XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, +1.0f);
    XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, +0.0f);

    XMMATRIX view = XMMatrixLookAtLH(eyePos, focusPos, upVector);

    viewBuffer->SetData(view);

    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (
        /*XM_PIDIV2*/1.8151424221f, // 그냥 실수를 넣어도 됨
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    ); //Fov : Fild of view 시야각

    projBuffer->SetData(projection);

    viewBuffer->SetVSBuffer(1);
    projBuffer->SetVSBuffer(2);
}
#include "Framework.h"
#include "Enviroment.h"

Enviroment::Enviroment()
{
    CreateViewport();
    CreatePerspective();

    lightBuffer = new LightBuffer();
}

Enviroment::~Enviroment()
{
    delete  projBuffer;
    delete lightBuffer;
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

    DC->RSSetViewports(1, &viewPort); // RS�ϱ� Rasterizer State���� ����, �����ܰ�� OM���� �ڿ� �͵� ��� ����
}

void Enviroment::CreatePerspective()
{
    projBuffer = new MatrixBuffer();



    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV4/*1.8151424221f*/, // �׳� �Ǽ��� �־ ��
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    ); //Fov : Fild of view �þ߰�

    projBuffer->SetData(projection);

    projBuffer->SetVSBuffer(2);
}

void Enviroment::SetEnviroment()
{
    lightBuffer->SetPSBuffer(0);

}

void Enviroment::PostRender()
{
    ImGui::SliderFloat3("LightDirection", (float*)&lightBuffer->data.direction, -1.0f, +1.0f);
    ImGui::ColorEdit4("AmbientLight", (float*)&lightBuffer->data.ambientLight);
}

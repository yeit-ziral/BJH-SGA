#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateViewport();
    CreatePerspective();

    lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
    delete  projBuffer;
    delete lightBuffer;
}

void Environment::CreateViewport() // 3D ����ü�� 2D�� �����ϸ鼭 ��� ǥ������ ����
{
    D3D11_VIEWPORT viewPort; // �츮�� ����ִ� ȭ�� -> ������ ��� �� ����(ȭ�� ���� ����)
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width    = WIN_WIDTH;
    viewPort.Height     = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    DC->RSSetViewports(1, &viewPort); // RS�ϱ� Rasterizer State���� ����, �����ܰ�� OM���� �ڿ� �͵� ��� ����
}

void Environment::CreatePerspective()
{
    projBuffer = new MatrixBuffer();



    projMatrix = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV4/*1.8151424221f*/, // �׳� �Ǽ��� �־ ��
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    ); //Fov : Fild of view �þ߰�

    projBuffer->SetData(projMatrix);

    projBuffer->SetVSBuffer(2);
}

void Environment::SetEnvironment()
{
    lightBuffer->SetPSBuffer(0);

}

void Environment::PostRender()
{
    ImGui::SliderFloat3("LightDirection", (float*)&lightBuffer->data.direction, -1.0f, +1.0f);
    ImGui::ColorEdit4("AmbientLight", (float*)&lightBuffer->data.ambientLight);
}

#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateViewport();
    CreatePerspective();
    CreateOrthographic();

    lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
    delete  persBuffer;
    delete lightBuffer;
}

void Environment::CreateViewport() // 3D 절두체를 2D로 압축하면서 어떻게 표현할지 결정
{
    D3D11_VIEWPORT viewPort; // 우리가 띄워주는 화면 -> 여러개 띄울 수 있음(화면 분할 가능)
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width    = WIN_WIDTH;
    viewPort.Height     = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    DC->RSSetViewports(1, &viewPort); // RS니까 Rasterizer State에서 실행, 설정단계라서 OM보다 뒤에 와도 상관 없음
}

void Environment::CreatePerspective()
{
    persBuffer = new MatrixBuffer();



    persMatrix = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV4/*1.8151424221f*/, // 그냥 실수를 넣어도 됨
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    ); //Fov : Fild of view 시야각

    persBuffer->SetData(persMatrix);
}

void Environment::CreateOrthographic()
{
    orthoBuffer = new MatrixBuffer();

    orthoMatrix = XMMatrixOrthographicOffCenterLH(0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

    orthoBuffer->SetData(orthoMatrix);

    UIViewBuffer = new ViewBuffer();
}

void Environment::SetEnvironment()
{
    lightBuffer->SetPSBuffer(0);

    persBuffer->SetVSBuffer(2);

    StateManager::GetInstance()->Set();
}

void Environment::PostSet()
{
    UIViewBuffer->SetVSBuffer(1);
     orthoBuffer->SetVSBuffer(2);

     StateManager::GetInstance()->PostSet();
}

void Environment::PostRender()
{
    ImGui::SliderFloat3("LightDirection", (float*)&lightBuffer->data.direction, -1.0f, +1.0f);
    ImGui::ColorEdit4("AmbientLight", (float*)&lightBuffer->data.ambientLight);
}

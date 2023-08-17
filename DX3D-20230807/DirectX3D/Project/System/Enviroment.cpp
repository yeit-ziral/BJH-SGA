#include "Framework.h"
#include "Enviroment.h"

Enviroment::Enviroment()
{
    CreateViewport();
    CreatePerspective();
}

Enviroment::~Enviroment()
{
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
}

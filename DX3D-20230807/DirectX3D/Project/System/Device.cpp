#include "Framework.h"
#include "Device.h"

Device::Device()
{
    CreateDeviceAndSwapChain();
    CreateBackBuffer();
}

Device::~Device()
{
                device->Release();
         deviceContext->Release();
    swapChain->Release();
    renderTargetView->Release();
}

void Device::CreateDeviceAndSwapChain()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferCount = 1; // backBuffer�� ��ΰ�

    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT; // ũ��
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // RGBA�� �Ǽ��� �ְڴٴ� ��
    // RGBA 8��Ʈ * 4�� = 32��Ʈ, UNORM = Unsigned Normal = 0 ~ 1

    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; //refreshRate = ���ź�(�󸶳� ȭ���� �����ϳ�), Numerator : ����
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // Denomiantor : �и�

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // buffer ���ó�� rendertarget ouput�̶�� ��

    swapChainDesc.OutputWindow = hWnd;

    swapChainDesc.SampleDesc.Count = 1; // sampling(ǥ��ȭ)�� ��������, Ȯ��,��ҽ� ��� �׸������� �̸� ���
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.Windowed = true; // ��üȭ���� ��������, â ȭ���� �������� ����
    // Desc�� ������ ����ٴ� ����

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG, // �Ӽ�
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );
}

void Device::CreateBackBuffer()
{
    ID3D11Texture2D* backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr); // ������ ������������ Output Merge �ܰ�
}

void Device::Clear()
{
    float clearColor[4] = { 0.33f, 0.33f, 0.4f, 1.0f };

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // backBuffer�� clear ��
}

void Device::Present()
{
    swapChain->Present(0, 0); // backBuffer�� frontBuffer�� ��ü�ϴ� �Լ�
}

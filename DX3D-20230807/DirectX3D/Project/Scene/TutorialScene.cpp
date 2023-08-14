#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
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

    ID3D11Texture2D* backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr); // ������ ������������ Output Merge �ܰ�

    /////////////////////////////////////////////////////////

    D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    deviceContext->RSSetViewports(1, &viewPort); // RS�ϱ� Rasterizer State���� ����, �����ܰ�� OM���� �ڿ� �͵� ��� ����


    //VertexShader
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* vertexBlob;
    D3DCompileFromFile
    (
        L"_Shader/VertexTutorial.hlsl",
        nullptr,
        nullptr,
        "main",
        "vs_5_0",
        flags,
        0,
        &vertexBlob, // ���� ������ �޾ƿͼ� �����ϴ� ��ü
        nullptr
    );

    device->CreateVertexShader
    (
        vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(),
        nullptr,
        &vertexShader
    );

    D3D11_INPUT_ELEMENT_DESC layoutDesc[2] = {};
    layoutDesc[0].SemanticName = "POSITION";
    layoutDesc[0].SemanticIndex = 0;
    layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // float�� 4byte���� ���ڰ� 32��(4 x 8 bit) , �� 12byte
    layoutDesc[0].InputSlot = 0;
    layoutDesc[0].AlignedByteOffset = 0; // �տ� �����Ͱ� �󸶳� ������ �����ϰ� �ִ���
    layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[0].InstanceDataStepRate = 0;

    layoutDesc[1].SemanticName = "COLOR";
    layoutDesc[1].SemanticIndex = 0;
    layoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // color�� Float4�� A32 ����
    layoutDesc[1].InputSlot = 0;
    layoutDesc[1].AlignedByteOffset = 12;
    layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[1].InstanceDataStepRate = 0;


    device->CreateInputLayout
    (
        layoutDesc, // �迭�̶� &�� �Ⱥٿ��� �̹� �ּҰ���
        ARRAYSIZE(layoutDesc), //������ ��ȯ�ϴ� ��ũ��//�迭�� ũ��
        vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(),
        &inputLayout
    );

    vertexBlob->Release();


    // PixelShader

    ID3DBlob* pixelBlob;
    D3DCompileFromFile
    (
        L"_Shader/PixelTutorial.hlsl",
        nullptr,
        nullptr,
        "main",
        "ps_5_0",
        flags,
        0,
        &pixelBlob, // ���� ������ �޾ƿͼ� �����ϴ� ��ü
        nullptr
    );

    device->CreatePixelShader
    (
        pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(),
        nullptr,
        &pixelShader
    );

    pixelBlob->Release();

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
    {
        // vertexBuffer�� ��Ƽ� �ѱ�
        D3D11_BUFFER_DESC bufferDesc = {};

        bufferDesc.ByteWidth = sizeof(VertexColor) * vertices.size();
        bufferDesc.Usage = D3D11_USAGE_DEFAULT; // DEFAULT�� CPU���� ���� ���� �Ұ���
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA data;

        data.pSysMem = vertices.data(); // vertices[0]���� �ѱ� �� ������ �� ��� vertices[0]�� ��������� ������ ����

        device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
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
        bufferDesc.Usage = D3D11_USAGE_DEFAULT; // DEFAULT�� CPU���� ���� ���� �Ұ���
        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA data;

        data.pSysMem = indices.data(); // vertices[0]���� �ѱ� �� ������ �� ��� vertices[0]�� ��������� ������ ����

        device->CreateBuffer(&bufferDesc, &data, &indexBuffer);
    }


    //WVP

    wvp.world = XMMatrixIdentity();

    XMVECTOR   eyePos = XMVectorSet(+3.0f, +3.0f, -3.0f, +1.0f);
    XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, +1.0f);
    XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, +0.0f);

    wvp.view = XMMatrixLookAtLH(eyePos, focusPos, upVector);

    wvp.projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f); //Fov : Fild of view �þ߰�

    {
        D3D11_BUFFER_DESC bufferDesc = {};

        bufferDesc.ByteWidth = sizeof(WVP);
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        device->CreateBuffer(&bufferDesc, nullptr, &constBuffer);
    }
}

TutorialScene::~TutorialScene()
{
    device->Release();
    deviceContext->Release();
    swapChain->Release();
    renderTargetView->Release();
}

void TutorialScene::Update()
{
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // backBuffer�� clear ��

    //TODO : Render

    stride = sizeof(VertexColor);
    offset = 0;

    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);
    // ��������� �����ϴ°Ŷ� ���� ��� ����

    //deviceContext->Draw(vertices.size(), 0); // Draw���� ������ ����
    deviceContext->DrawIndexed(indices.size(), 0, 0); //index�� Draw���� ������ ����


    //WVP
    WVP data;

    data.world = XMMatrixTranspose(wvp.world);
    data.view = XMMatrixTranspose(wvp.view);
    data.projection = XMMatrixTranspose(wvp.projection);

    deviceContext->UpdateSubresource(constBuffer, 0, nullptr, &data, 0, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &constBuffer);

    static float angle = 0.0f;

    angle += 0.0002f;

    wvp.world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f); // RollPitchYaw : Roll->�ٶ󺸴� ������ ������ ȸ��, Pitch->�ٶ󺸴� ���⿡�� �������� ������ ȸ��, Yaw->�ٶ󺸴� ������ ���Ʒ� ������ ������ ȸ��


    /////////////////////////////////////////


    swapChain->Present(0, 0); // backBuffer�� frontBuffer�� ��ü�ϴ� �Լ�
}

void TutorialScene::PostRender()
{
}

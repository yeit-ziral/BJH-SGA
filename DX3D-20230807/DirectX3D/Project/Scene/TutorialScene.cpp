#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferCount = 1; // backBuffer가 몇개인가

    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT; // 크기
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // RGBA를 실수로 넣겠다는 뜻
    // RGBA 8비트 * 4개 = 32비트, UNORM = Unsigned Normal = 0 ~ 1

    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; //refreshRate = 갱신빈도(얼마나 화면을 갱신하냐), Numerator : 분자
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // Denomiantor : 분모

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // buffer 사용처가 rendertarget ouput이라는 뜻

    swapChainDesc.OutputWindow = hWnd;

    swapChainDesc.SampleDesc.Count = 1; // sampling(표본화)와 관련있음, 확대,축소시 어떻게 그릴것인지 미리 계산
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.Windowed = true; // 전체화면을 쓸것인지, 창 화면을 쓸것인지 정함
    // Desc는 뭔가를 만든다는 뜻임

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG, // 속성
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

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr); // 랜더링 파이프라인의 Output Merge 단계

    /////////////////////////////////////////////////////////

    D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    deviceContext->RSSetViewports(1, &viewPort); // RS니까 Rasterizer State에서 실행, 설정단계라서 OM보다 뒤에 와도 상관 없음


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
        &vertexBlob, // 파일 정보를 받아와서 저장하는 객체
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
    layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // float이 4byte여서 숫자가 32임(4 x 8 bit) , 총 12byte
    layoutDesc[0].InputSlot = 0;
    layoutDesc[0].AlignedByteOffset = 0; // 앞에 데이터가 얼마나 공간을 차지하고 있는지
    layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[0].InstanceDataStepRate = 0;

    layoutDesc[1].SemanticName = "COLOR";
    layoutDesc[1].SemanticIndex = 0;
    layoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // color는 Float4라서 A32 붙음
    layoutDesc[1].InputSlot = 0;
    layoutDesc[1].AlignedByteOffset = 12;
    layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[1].InstanceDataStepRate = 0;


    device->CreateInputLayout
    (
        layoutDesc, // 배열이라서 &을 안붙여도 이미 주소값임
        ARRAYSIZE(layoutDesc), //갯수를 반환하는 메크로//배열의 크기
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
        &pixelBlob, // 파일 정보를 받아와서 저장하는 객체
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
        bufferDesc.Usage = D3D11_USAGE_DEFAULT; // DEFAULT는 CPU에서 정보 수정 불가능
        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA data;

        data.pSysMem = indices.data(); // vertices[0]으로 넘길 수 있지만 이 경우 vertices[0]이 비어있으면 오류가 생김

        device->CreateBuffer(&bufferDesc, &data, &indexBuffer);
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

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // backBuffer를 clear 함

    //TODO : Render

    stride = sizeof(VertexColor);
    offset = 0;

    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);
    // 여기까지는 세팅하는거라서 순서 상관 없음

    //deviceContext->Draw(vertices.size(), 0); // Draw부터 렌더링 시작
    deviceContext->DrawIndexed(indices.size(), 0, 0); //index로 Draw부터 렌더링 시작


    //WVP
    WVP data;

    data.world = XMMatrixTranspose(wvp.world);
    data.view = XMMatrixTranspose(wvp.view);
    data.projection = XMMatrixTranspose(wvp.projection);

    deviceContext->UpdateSubresource(constBuffer, 0, nullptr, &data, 0, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &constBuffer);

    static float angle = 0.0f;

    angle += 0.0002f;

    wvp.world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f); // RollPitchYaw : Roll->바라보는 방향을 축으로 회전, Pitch->바라보는 방향에서 오른쪽을 축으로 회전, Yaw->바라보는 방향의 위아래 방향을 축으로 회전


    /////////////////////////////////////////


    swapChain->Present(0, 0); // backBuffer와 frontBuffer를 교체하는 함수
}

void TutorialScene::PostRender()
{
}

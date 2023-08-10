// Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100


struct Vertex
{
    Vertex(float x, float y, float z)
    {
        pos = XMFLOAT3(x, y, z);
    }

    XMFLOAT3 pos;
};

ID3D11Device*           device;         // 무언가를 만들 때 사용, CPU를 다루는 객체
ID3D11DeviceContext*    deviceContext;  // 무언가를 그릴 때 사용, GPU를 다루는 객체

IDXGISwapChain*             swapChain;          // 더블버퍼링을 구현하는 객체
ID3D11RenderTargetView*     renderTargetView;   // view 들어가는 것들은 다 GPU에서 하는것들임, 백버퍼를 관리하는 객체


UINT stride = 0;
UINT offset = 0;


/////////////////////////////////////////////////////////////////


ID3D11VertexShader* vertexShader;
ID3D11PixelShader* pixelShader;

ID3D11InputLayout* inputLayout;

ID3D11Buffer* vertexBuffer; // constBuffer, IndexBuffer등이 추가로 있음



void Initialize();
void Render();
void Release();

HWND hWnd;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT));

    Initialize();

    MSG msg;

    //// 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0)) // 창을 계속 띄우기 위해 GetMessage가 true를 반환하도록 쓸데없는 message가 강제적을 계속 생성됨 -> 메모리 낭비
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 실제로 메세지가 들어왔을 때만 true => 이때만 if문 실행 
        {
            if (msg.message == WM_QUIT) // Quit Message가 왔을 때 while문 탈출
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // TODO : Update, Render
            Render();
        }
    };

    Release();

    return (int) msg.wParam;
}



void Initialize()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferCount = 1; // backBuffer가 몇개인가

    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT; // 크기
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // RGBA를 실수로 넣겠다는 뜻
    // RGBA 8비트 * 4개 = 32비트, UNORM = Unsigned Normal = 0 ~ 1

    swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60; //refreshRate = 갱신빈도(얼마나 화면을 갱신하냐), Numerator : 분자
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // Denomiantor : 분모

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // buffer 사용처가 rendertarget ouput이라는 뜻

    swapChainDesc.OutputWindow = hWnd;

    swapChainDesc.SampleDesc.Count   = 1; // sampling(표본화)와 관련있음, 확대,축소시 어떻게 그릴것인지 미리 계산
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
    viewPort.TopLeftX   = 0.0f;
    viewPort.TopLeftY   = 0.0f;
    viewPort.Width      = WIN_WIDTH;
    viewPort.Height     = WIN_HEIGHT;
    viewPort.MinDepth   = 0.0f;
    viewPort.MaxDepth   = 1.0f;

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

    D3D11_INPUT_ELEMENT_DESC layoutDesc[1] = {};
    layoutDesc[0].SemanticName          = "POSITION";
    layoutDesc[0].SemanticIndex         = 0;
    layoutDesc[0].Format                = DXGI_FORMAT_R32G32B32_FLOAT; // float이 4byte여서 숫자가 32임(4 x 8 bit)
    layoutDesc[0].InputSlot             = 0;
    layoutDesc[0].AlignedByteOffset     = 0; // 앞에 데이터가 얼마나 공간을 차지하고 있는지
    layoutDesc[0].InputSlotClass        = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[0].InstanceDataStepRate  = 0;

    

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
    Vertex vertex(0.0f, 0.0f, 0.0f);


    //VertexBuffer

    // vertexBuffer에 담아서 넘김
    D3D11_BUFFER_DESC bufferDesc = {};

    bufferDesc.ByteWidth            = sizeof(Vertex) * 1;
    bufferDesc.Usage                = D3D11_USAGE_DEFAULT; // DEFAULT는 CPU에서 정보 수정 불가능
    bufferDesc.BindFlags            = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags       = 0;
    bufferDesc.MiscFlags            = 0;
    bufferDesc.StructureByteStride  = 0;

    D3D11_SUBRESOURCE_DATA data;

    data.pSysMem = &vertex;

    device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
}

void Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // backBuffer를 clear 함

    //TODO : Render

    stride = sizeof(Vertex);
    offset = 0;

    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST); // 

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);
    // 여기까지는 세팅하는거라서 순서 상관 없음

    deviceContext->Draw(1, 0); // Draw부터 렌더링 시작

    /////////////////////////////////////////


    swapChain->Present(0, 0); // backBuffer와 frontBuffer를 교체하는 함수
}

void Release()
{
    device->Release();
    deviceContext->Release();
    swapChain->Release();
    renderTargetView->Release();
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; // -> 구조체 : 매개변수를 모아놓은 것

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) // 인스턴스 초기화
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rect = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

   hWnd = CreateWindowW
   (
       szWindowClass, 
       szTitle, 
       WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, //창 시작점
       rect.right - rect.left, rect.bottom - rect.top, // 창 크기
       nullptr, nullptr, hInstance, nullptr
   );

   SetMenu(hWnd, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // Quit message를 보냄
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

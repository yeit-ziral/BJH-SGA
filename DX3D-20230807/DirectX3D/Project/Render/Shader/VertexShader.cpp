#include "Framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile
    (
        file.c_str(),
        nullptr,
        nullptr,
        "main",
        "vs_5_0",
        flags,
        0,
        &blob, // 파일 정보를 받아와서 저장하는 객체
        nullptr
    );

    DEVICE->CreateVertexShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &vertexShader
    );

    CreateInputLayout();
}

VertexShader::~VertexShader()
{
    vertexShader->Release();
    inputLayout->Release();
}

void VertexShader::SetShader()
{

    DC->IASetInputLayout(inputLayout);
    DC->VSSetShader(vertexShader, nullptr, 0);
}

void VertexShader::CreateInputLayout()
{
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


    DEVICE->CreateInputLayout
    (
        layoutDesc, // 배열이라서 &을 안붙여도 이미 주소값임
        ARRAYSIZE(layoutDesc), //갯수를 반환하는 메크로//배열의 크기
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        &inputLayout
    );
}

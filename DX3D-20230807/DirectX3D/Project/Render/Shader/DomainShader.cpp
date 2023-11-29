#include "Framework.h"
#include "DomainShader.h"

DomainShader::DomainShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile
    (
        file.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "ds_5_0",
        flags,
        0,
        &blob, // 파일 정보를 받아와서 저장하는 객체
        nullptr
    );

    DEVICE->CreateDomainShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    );
}

DomainShader::~DomainShader()
{
    shader->Release();
}

void DomainShader::SetShader()
{
    DC->DSSetShader(shader, nullptr, 0);
}

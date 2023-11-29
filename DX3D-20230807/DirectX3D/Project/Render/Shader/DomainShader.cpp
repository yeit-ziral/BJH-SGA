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
        &blob, // ���� ������ �޾ƿͼ� �����ϴ� ��ü
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

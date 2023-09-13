#include "Framework.h"
#include "Shader.h"

map<wstring, Shader*> Shader::shaders = {};

Shader::~Shader()
{
    blob->Release();
}

VertexShader* Shader::GetVS(wstring file)
{
    file = L"_Shader/Vertex" + file + L".hlsl";

    if (shaders.count(file) > 0)
        return (VertexShader*)shaders[file]; // 명시적 형변환, 강제적으로 형변환을 시킴(static_cast), dynamic_cast는 형변환이 안되면 null 반환, 때에 따라 강제로 형변환 시켜서 안되면 터지도록 하는게 오류 찾기 더 편함

    shaders[file] = new VertexShader(file);

    return (VertexShader*)shaders[file];
}

PixelShader* Shader::GetPS(wstring file)
{
    file = L"_Shader/Pixel" + file + L".hlsl";

    if (shaders.count(file) > 0)
        return (PixelShader*)shaders[file];

    shaders[file] = new PixelShader(file);

    return (PixelShader*)shaders[file];

    return nullptr;
}

ComputeShader* Shader::GetCS(wstring file)
{
    file = L"_Shader/" + file + L".hlsl";

    if (shaders.count(file) > 0)
        return (ComputeShader*)shaders[file];

    shaders[file] = new ComputeShader(file);

    return (ComputeShader*)shaders[file];

    return nullptr;
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders) // 범위 기반 for문
        delete shader.second; // 각 위치의 내용만 지움, 할당은 되어있음

    shaders.clear(); // 해서 쓰레기 데이터를 지워줌 delete 했을 때 값만 사라지기 때문
}

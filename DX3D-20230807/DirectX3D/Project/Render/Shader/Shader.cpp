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

    assert(PathFileExists(file.c_str()));

    if (shaders.count(file) > 0)
        return (VertexShader*)shaders[file]; // ����� ����ȯ, ���������� ����ȯ�� ��Ŵ(static_cast), dynamic_cast�� ����ȯ�� �ȵǸ� null ��ȯ, ���� ���� ������ ����ȯ ���Ѽ� �ȵǸ� �������� �ϴ°� ���� ã�� �� ����

    shaders[file] = new VertexShader(file);

    return (VertexShader*)shaders[file];
}

PixelShader* Shader::GetPS(wstring file)
{
    file = L"_Shader/Pixel" + file + L".hlsl";

    assert(PathFileExists(file.c_str()));

    if (shaders.count(file) > 0)
        return (PixelShader*)shaders[file];

    shaders[file] = new PixelShader(file);

    return (PixelShader*)shaders[file];

    return nullptr;
}

ComputeShader* Shader::GetCS(wstring file)
{
    file = L"_Shader/" + file + L".hlsl";

    assert(PathFileExists(file.c_str()));

    if (shaders.count(file) > 0)
        return (ComputeShader*)shaders[file];

    shaders[file] = new ComputeShader(file);

    return (ComputeShader*)shaders[file];

    return nullptr;
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders) // ���� ��� for��
        delete shader.second; // �� ��ġ�� ���븸 ����, �Ҵ��� �Ǿ�����

    shaders.clear(); // �ؼ� ������ �����͸� ������ delete ���� �� ���� ������� ����
}

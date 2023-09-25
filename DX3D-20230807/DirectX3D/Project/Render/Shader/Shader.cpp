#include "Framework.h"
#include "Shader.h"

map<wstring, Shader*> Shader::shaders = {};

Shader::~Shader()
{
    blob->Release();
}

VertexShader* Shader::GetVS(wstring file)
{
    wstring key = file;

    file = L"_Shader/Vertex" + file + L".hlsl";

    assert(PathFileExists(file.c_str()));

    if (shaders.count(file) > 0)
        return (VertexShader*)shaders[file]; // ����� ����ȯ, ���������� ����ȯ�� ��Ŵ(static_cast), dynamic_cast�� ����ȯ�� �ȵǸ� null ��ȯ, ���� ���� ������ ����ȯ ���Ѽ� �ȵǸ� �������� �ϴ°� ���� ã�� �� ����

    shaders[file] = new VertexShader(file);

    shaders[file]->path = key; // shader ���� �� �־��ֱ�

    return (VertexShader*)shaders[file];
}

PixelShader* Shader::GetPS(wstring file)
{
    wstring key = file;

    file = L"_Shader/Pixel" + file + L".hlsl";

    assert(PathFileExists(file.c_str()));

    if (shaders.count(file) > 0)
        return (PixelShader*)shaders[file];

    shaders[file] = new PixelShader(file);

    shaders[file]->path = key;

    return (PixelShader*)shaders[file];
}

ComputeShader* Shader::GetCS(wstring file)
{
    wstring key = file;

    file = L"_Shader/" + file + L".hlsl";

    assert(PathFileExists(file.c_str()));

    if (shaders.count(file) > 0)
        return (ComputeShader*)shaders[file];

    shaders[file] = new ComputeShader(file);

    shaders[file]->path = key;

    return (ComputeShader*)shaders[file];
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders) // ���� ��� for��
        delete shader.second; // �� ��ġ�� ���븸 ����, �Ҵ��� �Ǿ�����

    shaders.clear(); // �ؼ� ������ �����͸� ������ delete ���� �� ���� ������� ����
}

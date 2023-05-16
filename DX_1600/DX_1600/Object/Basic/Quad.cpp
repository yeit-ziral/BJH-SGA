#include "framework.h"
#include "Quad.h"

Quad::Quad()
{

    _vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
}

Quad::Quad(wstring srvFile)
{
    _vs = make_shared<VertexShader>(L"Shader/TextureVS.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/TexturePS.hlsl");

    _srv = make_shared<SRV>(srvFile);
    _ss = make_shared<SamplerState>();

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());

    _transform = make_shared<Transform>();
}

Quad::~Quad()
{
}

void Quad::Update()
{
    _transform->Update();
}

void Quad::Render()
{
    _vertexBuffer->Set(0);
    _indexBuffer->Set();

    _transform->SetBuffer(0);
    _vs->Set();

    _srv->Set(0);
    _ss->Set(0);
    _ps->Set();

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DC->DrawIndexed(_indices.size(), 0, 0);
}

void Quad::CreateVertices()
{
    // 시계방향으로 그리기
    // 
    Vertex temp;
    Vector2 halfSize;
    halfSize.x = (_srv->GetImageSize().x) * 0.5f;
    halfSize.y = (_srv->GetImageSize().y) * 0.5f;

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    temp.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    temp.uv = { 1.0f, 0.0f };
    _vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(halfSize.x, halfSize.y, 0.0f);
    temp.color = XMFLOAT4(0.7f, 0.6f, 1.0f, 1.0f);
    temp.uv = { 0.0f, 0.0f };
    _vertices.push_back(temp); // 오른쪽 위

    temp.pos = XMFLOAT3(halfSize.x, -halfSize.y, 0.0f);
    temp.color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
    temp.uv = { 0.0f, 1.0f };
    _vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f);
    temp.color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    temp.uv = { 1.0f, 1.0f };
    _vertices.push_back(temp); // 왼쪽 아래

    // 사각형 반쪽 삼각형 두개 그림
    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(0);
    _indices.push_back(2);
    _indices.push_back(3);
}

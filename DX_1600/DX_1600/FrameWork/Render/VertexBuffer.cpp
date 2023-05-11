#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	CreateVertices();
	CreateVertexBuffer();


    
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::CreateVertices()
{
    // �ð�������� �׸���
    // �簢�� ���� �ﰢ��
    Vertex temp;
    temp.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
    temp.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    temp.uv = { 1.0f, 0.0f };
    vertices.push_back(temp); // ���� ��

    temp.pos = XMFLOAT3(0.5f, 0.5f, 0.0f);
    temp.color = XMFLOAT4(0.7f, 0.6f, 1.0f, 1.0f);
    temp.uv = { 0.0f, 0.0f };
    vertices.push_back(temp); // ������ ��

    temp.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
    temp.color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
    temp.uv = { 0.0f, 1.0f };
    vertices.push_back(temp); // ������ �Ʒ�

    // �簢�� ���� �ﰢ��
    temp.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
    temp.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    temp.uv = { 1.0f, 0.0f };
    vertices.push_back(temp); // ���� ��

    temp.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
    temp.color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
    temp.uv = { 0.0f, 1.0f };
    vertices.push_back(temp); // ������ �Ʒ�

    temp.pos = XMFLOAT3(-0.5f, -0.5f, 0.0f);
    temp.color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    temp.uv = { 1.0f, 1.0f };
    vertices.push_back(temp); // ���� �Ʒ�

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
}

void VertexBuffer::CreateVertexBuffer()
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex) * vertices.size();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices.data();

    DEVICE->CreateBuffer(&bd, &initData, vertexBuffer.GetAddressOf());
}

void VertexBuffer::Set(int slot)
{
    DC->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
}

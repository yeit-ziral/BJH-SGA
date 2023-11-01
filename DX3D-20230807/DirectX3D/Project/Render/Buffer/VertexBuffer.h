#pragma once
class VertexBuffer
{
public:
	template<typename T>
	VertexBuffer(vector<T>& vertices);
	~VertexBuffer();

	void IASetBuffer( D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void IASetBuffer(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    void UpdateVertex(void* data, UINT count);

private:
	ID3D11Buffer* vertexBuffer; // constBuffer, IndexBuffer���� �߰��� ����

    UINT stride = 0;
    UINT offset = 0;
};

template<typename T>
inline VertexBuffer::VertexBuffer(vector<T>& vertices)
{
    stride = sizeof(T);
    offset = 0;

    // vertexBuffer�� ��Ƽ� �ѱ�
    D3D11_BUFFER_DESC bufferDesc = {};

    bufferDesc.ByteWidth           = stride * vertices.size();
    bufferDesc.Usage               = D3D11_USAGE_DEFAULT; // DEFAULT�� CPU���� ���� ���� �Ұ���
    bufferDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags      = 0;
    bufferDesc.MiscFlags           = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA data; //�ʱ� ������ ����

    data.pSysMem = vertices.data(); // vertices[0]���� �ѱ� �� ������ �� ��� vertices[0]�� ��������� ������ ����

    DEVICE->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
}
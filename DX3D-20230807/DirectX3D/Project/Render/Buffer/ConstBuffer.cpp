#include "Framework.h"
#include "ConstBuffer.h"

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
    : data(data), dataSize(dataSize)
{
    D3D11_BUFFER_DESC bufferDesc = {};

    bufferDesc.ByteWidth            = dataSize;                     // ���� ũ��
    bufferDesc.Usage                = D3D11_USAGE_DYNAMIC;          // ���ó, �ٸ� �������� Ư¡�� ������ ����ؾ� ��  �߿�!!
    bufferDesc.BindFlags            = D3D11_BIND_CONSTANT_BUFFER;   
    bufferDesc.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;       // �ٸ� ��ɵ� �߰��Ϸ��� or ������ | �� ����ϸ� ��, CPU�� ���� �����ϰ� ��
    bufferDesc.MiscFlags            = 0; //��Ÿ����� ����
    bufferDesc.StructureByteStride  = 0;

    DEVICE->CreateBuffer(&bufferDesc, nullptr, &constBuffer); // ������ ���� ����
}

ConstBuffer::~ConstBuffer()
{
    constBuffer->Release();
}

void ConstBuffer::SetVSBuffer(UINT slot)
{
    UpdateSubResource();

    DC->VSSetConstantBuffers(slot, 1, &constBuffer);
}

void ConstBuffer::SetPSBuffer(UINT slot)
{
    UpdateSubResource();

    DC->PSSetConstantBuffers(slot, 1, &constBuffer);
}

void ConstBuffer::SetCSBuffer(UINT slot)
{
    UpdateSubResource();

    DC->CSSetConstantBuffers(slot, 1, &constBuffer);
}

void ConstBuffer::UpdateSubResource()
{
    // Map, Unmap

    DC->Map(constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource); // Map : �� �� �ְ� �Ѳ��� ���°�, ���⼭�� subResource�� ������ �� �ְ� �ϴ� �۾��̴�.

    memcpy(subResource.pData, data, dataSize); // �迭�� �����͸� ������ �� �� , _Dst-> ������, _Src->����, dataSize��ŭ �ű�

    DC->Unmap(constBuffer, 0); // Unmap : �ٽ� �Ѳ��� �ݴ°�, ���� ������ ���� ����

    //DC->UpdateSubresource(constBuffer, 0, nullptr, data, 0, 0); // ���⼭ ������(WVP�� ���) �Ѱ���
}

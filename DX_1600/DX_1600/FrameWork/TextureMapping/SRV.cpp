#include "framework.h"
#include "SRV.h"

SRV::SRV(wstring file)
{
    ScratchImage image;
    wstring path = file;
    LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);

    // �ǹ��� ����� �۾�
    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
        shaderResourceView.GetAddressOf());
}

SRV::~SRV()
{
}

void SRV::Set(int slot)
{
    DC->PSSetShaderResources(0, 1, shaderResourceView.GetAddressOf());
}

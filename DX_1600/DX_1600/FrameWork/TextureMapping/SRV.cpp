#include "framework.h"
#include "SRV.h"

SRV::SRV(wstring file)
{
    ScratchImage image;
    wstring path = L"Resource/Goomba.png";
    LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);

    // �ǹ��� ����� �۾�
    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
        shaderResourceView.GetAddressOf());
}

SRV::~SRV()
{
}

void SRV::Set()
{
    DC->PSSetShaderResources(0, 1, shaderResourceView.GetAddressOf());
}

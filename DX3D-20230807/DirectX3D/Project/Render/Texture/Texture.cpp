#include "Framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::textures = {};

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	:srv(srv), image(move(image)) 
// move : �̵� ������ => ���� ����, ������ �ּҰ��� �޾ƿ��� ���� ���� ���� ��ü���� �ּҰ��� ��� �ְ� ��, �޸𸮸� �Ƴ� �� ����
// �����ָ� image�� ������ �����̶�� ����
{

}

Texture::~Texture()
{
	srv->Release();
}

Texture* Texture::Get(wstring file)
{
	// ������ �ִ°� ����
	file = L"Texture/" + file;

	if (textures.count(file) > 0)
		return textures[file];

	wstring extension = GetExtension(file);

	// ������ ���� ����
	ScratchImage image;

	if (extension == L"tga")
		LoadFromTGAFile(file.c_str(), nullptr, image);

	else if (extension == L"dds")
		LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);

	else
		LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image); // ScratchImage�� �̵� �����ڿ��� �� �Լ��� ������ ���������� image �� �������� ���� �������� ���⼭ �Ѱ�� ����


	ID3D11ShaderResourceView* srv = nullptr;

	CreateShaderResourceView
	(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);

	textures[file] = new Texture(srv, image);

	return textures[file];
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> pair : textures)
		delete pair.second;

	textures.clear();
}

void Texture::PSSetShaderResources(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &srv);
}

vector<Vector4> Texture::ReadPixels()
{
	unsigned char* pixels = image.GetPixels(); // ���ϰ��� uint8_t(unsigned char)*�� ���� -> �迭�� �ּҰ� �������̿��� ù��° �ּҰ��� �˾Ƶ� ������ ���� �� ������ �� �ִ�.

	UINT size = image.GetPixelsSize() * 0.25f; // �ȼ� ����

	vector<Vector4> colors(size); // = color; color.resize(size)

	float scale = 1.0f / 255.0f;

	UINT count = 0;

	for (Vector4& color : colors) // call by reference�� �������� ��ȯ������
	{
		color.x = pixels[count++] * scale;
		color.y = pixels[count++] * scale;
		color.z = pixels[count++] * scale;
		color.w = pixels[count++] * scale;
	}

	return colors;
}

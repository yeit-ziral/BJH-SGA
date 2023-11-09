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
	if (!isReferred) // ������ ���� RenderTarget���� �����ֱ� ����
		srv->Release();
}

Texture* Texture::Get(wstring file)
{
	wstring path = file;

	//if (file == L"Texture/Model/Pumpkin/Pumpkin.fbm\\Pumpkin_DefaultMaterial_BaseColor.png")
	//	file = L"Texture/Model/Pumpkin/Pumpkin_DefaultMaterial_BaseColor.png";

	if (file == L"")
		return nullptr;

	if (!StartsWith(file, L"Texture")) 	// ������ �ִ°� ����
		file = L"Texture/" + file;

	assert(PathFileExists(file.c_str())); // ���� ������ �߰������� ������ ������ �ִ��� Ȯ��(PathFileExists)�ϰ� ������ �ߴ�(assert)

	if (textures.count(file) > 0)
		return textures[file];

	wstring extension = GetExtension(file);

	// ������ ���� ����
	ScratchImage image;

	if (extension == L"tga" || extension == L"TGA")
		LoadFromTGAFile(file.c_str(), nullptr, image);

	else if (extension == L"dds" || extension == L"DDS")
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

	textures[file]->path = path;

	return textures[file];
}

Texture* Texture::Get(wstring key, ID3D11ShaderResourceView* srv)
{
	if (textures.count(key) > 0)
		return textures[key];

	ScratchImage image;

	textures.emplace(key, new Texture(srv, image));
	textures[key]->isReferred = true;

	return textures[key];
}

Texture* Texture::Load(wstring file)
{
	wstring path = file; // ��������� path�� static������ ���� static������ �Լ� �����͸� ����

	if (file == L"")
		return nullptr;

	// ������ �ִ°� ����
	file = L"Texture/" + file;

	assert(PathFileExists(file.c_str())); // ���� ������ �߰������� ������ ������ �ִ��� Ȯ��(PathFileExists)�ϰ� ������ �ߴ�(assert)

	if (textures.count(file) > 0)
	{
		textures.erase(file);
	}

	wstring extension = GetExtension(file);

	// ������ ���� ����
	ScratchImage image; // ���� path�� ���� ���

	if (extension == L"tga" || extension == L"TGA")
		LoadFromTGAFile(file.c_str(), nullptr, image);

	else if (extension == L"dds" || extension == L"DDS")
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

	textures[file]->path = path;

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

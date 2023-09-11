#pragma once
class BinaryWriter // 보안에 좋고 확장명을 바꿀 수 있다
{
public:
	BinaryWriter(wstring path);
	~BinaryWriter();

	void Int(int data);
	void UInt(UINT data);
	void Float(float data);
	void String(string data);

	void Byte(void* data, UINT dataSize);

private:
	HANDLE _file;
	DWORD _size;
};


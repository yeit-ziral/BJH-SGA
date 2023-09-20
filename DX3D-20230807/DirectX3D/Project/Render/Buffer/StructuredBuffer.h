#pragma once
class StructuredBuffer
{
public:
	StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount, UINT outputStride, UINT outputCount);
	~StructuredBuffer();

	void Copy(void* data, UINT size); // GPU���� �Ѱܹ��� ���� �� �ִ� �����͸� �� �� �ִ� �����ͷ� ��ȯ
	void UpdateInput(void* data);

	ID3D11UnorderedAccessView* GetUAV() { return uav; }
	ID3D11ShaderResourceView* GetSRV() { return srv; }

	// D3D11_USAGE_WRITE�� ���۸� �ٽ� GPU���� ����� ��


	void SetSRV();
	void SetUAV();

private:
	void CreateInput();
	void CreateSRV();
	void CreateOutput();
	void CreateUAV(); // �����͸� ä��� ����
	void CreateResult(); // output�� D3D11_USAGE_DEFAULT�̶� CPU�� ���� ���ϱ⿡ ���⼭ D3D11_USAGE_STAGING�� ��ȯ

private:
	ID3D11UnorderedAccessView* uav; // GPU���� ������ ����� ������� CPU�� �Ѱ��ֱ� ����, �����(D3D11_USAGE_DEFAULT)
	ID3D11ShaderResourceView*  srv; // lay, poligon�� ������ GPU�� �ѱ�� ����,  �б��

	ID3D11Resource*  input; // GPU�� �Ѱ��� ������
	ID3D11Resource* output; // CPU�� �Ѱ��� ������
	ID3D11Resource* result; // CPU�� ���� �� �ִ� �����ͷ� ��ȯ�Ǿ� ����

	// input, srv(�Բ� ����) -> output,result,uav (�Բ� ����)
	// ������ ��ȯ ����(?) : input -> srv -> output -> uav  -> result �Լ� ����

	void* inputData;
	UINT inputStride;
	UINT inputCount;

	UINT outputStride;
	UINT outputCount;
};
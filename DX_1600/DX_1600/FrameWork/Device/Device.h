#pragma once
class Device
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Device();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Device* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDC() { return _deviceContext; }

	void Clear();
	void Present();

private:
	Device();
	~Device();

	void CreateDeviceAndSwapChain();
	void CreateDoubleBuffer();

	static Device* _instance;

	// �η»繫����
// ���ָ� �ñ�� �������� ���� ��ǥ �̱�
// ��ǻ���� �ϵ���� ��� ����, ���ҽ� �Ҵ�(�ϵ��� ������ �� �ְ� �����ִ� ��)
	ComPtr<ID3D11Device> _device; // shared ptr���� �� ������ ĸ��ȭ�� �ؼ� shared_ptr�δ� �ٷ� �� ���� �����

	// ���Ⱘ��
	// ��Ʈ���� ���������� �ٸ��ִ� ���Ⱘ��
	// �������� ����� ����(����� �׸��� ����)
	// -> ���ҽ��� �׷��� ���������ο� ���ε�, GPU�� ������ ����� ����
	ComPtr<ID3D11DeviceContext> _deviceContext;

	// DX�� �������̽��ν� 1�� �̻��� ǥ���� ������ �� �ִ�.
	// ������ ǥ��(����, �ؽ���)�� ����ϱ� ���� �����͸� �����Ѵ�.
	ComPtr<IDXGISwapChain> _swapChain;

	// ���� ���� �׸� ��(�ĸ� ����)�� ����Ű�� ������
	// View... ������
	ComPtr<ID3D11RenderTargetView> _renderTargetView;
};


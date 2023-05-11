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

	// 인력사무소장
// 외주를 맡기고 실질적인 공사 대표 뽑기
// 컴퓨터의 하드웨어 기능 점검, 리소스 할당(하드웨어에 접근할 수 있게 도와주는 얘)
	ComPtr<ID3D11Device> _device; // shared ptr보다 더 엄격한 캡슐화를 해서 shared_ptr로는 다룰 수 없어 만든것

	// 연출감독
	// 세트장을 실질적으로 꾸며주는 연출감독
	// 렌더링할 대상을 결정(어따가 그릴지 결정)
	// -> 리소스를 그래픽 파이프라인에 바인딩, GPU가 수행할 명령을 지시
	ComPtr<ID3D11DeviceContext> _deviceContext;

	// DX의 인터페이스로써 1개 이상의 표면을 포함할 수 있다.
	// 각각의 표면(버퍼, 텍스쳐)을 출력하기 전에 데이터를 보관한다.
	ComPtr<IDXGISwapChain> _swapChain;

	// 지금 당장 그릴 곳(후면 버퍼)을 가리키는 포인터
	// View... 포인터
	ComPtr<ID3D11RenderTargetView> _renderTargetView;
};


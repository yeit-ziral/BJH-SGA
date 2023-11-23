#pragma once
class RenderTarget
{
public:
	RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	~RenderTarget();

	void Set(DepthStencil* depthStencil, Vector4 clearColor = Vector4(1, 1, 1, 1));

	ID3D11RenderTargetView* GetRTV() { return rtv; }
	ID3D11ShaderResourceView* GetSRV() { return srv; }  // 원본 수정 불가능 -> 값 복사만 함
	ID3D11ShaderResourceView*& GetSRVRef() { return srv; } // 원본 수정 가능

	static void SetMulti(RenderTarget** targets, UINT count, DepthStencil* depthStencil, Vector4 clearColor = { 1,1,1,1 });// multi renderTarget을 세팅함

private:
	void CreateRTVTexture();
	void CreateRTV();
	void CreateSRV();

private:
	UINT width, height;

	bool isStencil = false;

	ID3D11Texture2D* rtvTexture;
	ID3D11RenderTargetView* rtv;
	ID3D11ShaderResourceView* srv;

};
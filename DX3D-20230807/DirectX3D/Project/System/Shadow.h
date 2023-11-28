#pragma once
class Shadow
{
public:
	Shadow(UINT width = 2000, UINT height = 2000); // 크기가 작으면 계단현상이 나타남
	~Shadow();

	void SetPreRender();
	void SetRender();
	void PostRender();

private:
	void SetViewProjection();

private:
	UINT width, height;

	RenderTarget* renderTarget;
	DepthStencil* depthStencil;

	// viewProjection을 따로 잡음
	  ViewBuffer* viewBuffer;
	MatrixBuffer* projBuffer;

	Quad* quad; // 디버깅 용
};
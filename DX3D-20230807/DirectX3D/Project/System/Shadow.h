#pragma once
class Shadow
{
public:
	Shadow(UINT width = 2000, UINT height = 2000); // ũ�Ⱑ ������ ��������� ��Ÿ��
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

	// viewProjection�� ���� ����
	  ViewBuffer* viewBuffer;
	MatrixBuffer* projBuffer;

	Quad* quad; // ����� ��
};
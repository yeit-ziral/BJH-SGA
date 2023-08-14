#pragma once

struct Vertex
{
    Vertex(float x, float y, float z)
    {
        pos = XMFLOAT3(x, y, z);
    }

    XMFLOAT3 pos;
};

struct VertexColor
{
    VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
        :pos(pos), color(color)
    {

    }

    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct WVP
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
};


class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
    WVP wvp;

    vector<VertexColor> vertices;
    vector<UINT> indices;

    ID3D11Device* device;         // ���𰡸� ���� �� ���, CPU�� �ٷ�� ��ü
    ID3D11DeviceContext* deviceContext;  // ���𰡸� �׸� �� ���, GPU�� �ٷ�� ��ü

    IDXGISwapChain* swapChain;          // ������۸��� �����ϴ� ��ü
    ID3D11RenderTargetView* renderTargetView;   // view ���� �͵��� �� GPU���� �ϴ°͵���, ����۸� �����ϴ� ��ü


    UINT stride = 0;
    UINT offset = 0;


    /////////////////////////////////////////////////////////////////


    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;

    ID3D11InputLayout* inputLayout;

    ID3D11Buffer* vertexBuffer; // constBuffer, IndexBuffer���� �߰��� ����
    ID3D11Buffer* indexBuffer;
    ID3D11Buffer* constBuffer;


};


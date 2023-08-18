#pragma once
class Cube
{
public:
	Cube();
	~Cube();

    void Update();
    void Render();

private:
    VertexShader* vertexShader;
    PixelShader* pixelShader;

    VertexBuffer* vertexBuffer;

    IndexBuffer* indexBuffer;

    MatrixBuffer* worldBuffer;


    ///////////////////////////////////////

    vector<VertexColor> vertices;
    vector<UINT> indices;
};


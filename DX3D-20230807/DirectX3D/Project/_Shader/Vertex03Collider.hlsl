
cbuffer World : register(b0)
{
    matrix world;

};

cbuffer View : register(b1)
{
    matrix view;
};

cbuffer Proj : register(b2)
{
    matrix projection;
};

struct VertexInput
{
    float4 pos : POSITION;
};

struct VertexOutput // VertexInput�� �״�� ��ȯ�ϸ� pos�� symentic name�� SV_POSITION�� �ƴ϶� ����
{
    float4 pos : SV_POSITION;
};

VertexOutput main(VertexInput input)
{
    //float4 a = { 1, 2, 3, 4 };
	//
    //float4 b = a.xyzw;
    //float4 b1 = a.rgba; // hlsl�� �� �� �����ϰ� ��� ���� 
    
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    return output;
}
cbuffer WVP : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};


struct VertexInput
{
    float4 pos      : POSITiON; // ������ǥ�� ������ float3�� �ƴ� float4�� �� ���� �ø�
    float4 color    : COLOR;
};

struct VertexOutput // VertexInput�� �״�� ��ȯ�ϸ� pos�� symentic name�� SV_POSITION�� �ƴ϶� ����
{
    float4 pos      : SV_POSITiON; //SV_POSITION (System value position)-> main�� ��ȯ������ ���ϰ��� RS(Rasterizer : �ý���)�� ���ٴ� �� �߰��ܰ��� HS�� TS�� �����ϸ� SV_POSITION�� �ƴ� �ٸ� ���� �� �ش� �߰��ܰ�� ������
    float4 color    : COLOR;
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
    
    output.color = input.color;
    
	return output;
}
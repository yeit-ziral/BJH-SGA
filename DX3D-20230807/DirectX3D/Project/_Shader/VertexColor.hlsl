#include "Header.hlsli"


struct VertexOutput // VertexInput�� �״�� ��ȯ�ϸ� pos�� symentic name�� SV_POSITION�� �ƴ϶� ����
{
    float4 pos : SV_POSITION; //SV_POSITION (System value position)-> main�� ��ȯ������ ���ϰ��� RS(Rasterizer : �ý���)�� ���ٴ� �� �߰��ܰ��� HS�� TS�� �����ϸ� SV_POSITION�� �ƴ� �ٸ� ���� �� �ش� �߰��ܰ�� ������
    float4 color : COLOR;
    float3 normal : NORMAL;
};

VertexOutput main(VertexColorNormal input)
{
    
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.color = input.color;
    
    output.normal = normalize(mul(input.normal, (float3x3) world));
    
    
    return output;
}
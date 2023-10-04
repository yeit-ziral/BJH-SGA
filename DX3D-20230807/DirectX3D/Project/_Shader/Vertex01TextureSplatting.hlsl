#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT; // uv�� x��
    float3 binormal : BINORMAL; // uv�� y��
    float3 viewDir : VIEWDIR;
    
    float3 worldPos : POSITIONT;
    
    float4 alpha : ALPHA;
};

VertexOutput main(VertexTextureNormalTanagentAlpha input)
{
    VertexOutput output;
    
    
    output.pos = mul(input.pos, world);
        
    //ȭ�� ��ǥ�� �������� ������ ����ؼ� �� ���� �������� �ؾ� ��
    output.worldPos = output.pos;
    
    float3 cameraPos = inverseView._41_42_43;
    
    output.viewDir = normalize(output.pos.xyz - cameraPos);

    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    output.normal = normalize(mul(input.normal, (float3x3) world));

    output.tangent = normalize(mul(input.tangent, (float3x3) world));
    
    output.binormal = cross(output.normal, output.tangent);
    
    output.alpha = input.alpha;
    
    return output;
}
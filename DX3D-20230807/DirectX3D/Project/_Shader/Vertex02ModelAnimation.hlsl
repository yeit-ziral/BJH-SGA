#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT; // uv의 x축
    float3 binormal : BINORMAL; // uv의 y축
    float3 viewDir : VIEWDIR;
};

matrix SkinWorld(float4 indices, float4 weights)
{
    matrix transform = 0;
    matrix curAnim;
    
    float4 c0, c1, c2, c3;
    
    [unroll]
    for (int i = 0; i < 4; i++)
    {
        c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame, clip, 0));
        c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame, clip, 0));
        c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame, clip, 0));
        c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame, clip, 0));
        
        curAnim = matrix(c0, c1, c2, c3);
        
        transform += mul(weights[i], curAnim);
    }
    
    return transform;
}

VertexOutput
    main(VertexTextureNormalTangentBlend input)
{
    VertexOutput output;
    
    /////////////////////////
    
    matrix transform = mul(SkinWorld(input.indices, input.weight), world);
    
    output.pos = mul(input.pos, transform);
    ////////////////////////
    
    output.pos = mul(input.pos, world);
    
    float3 cameraPos = inverseView._41_42_43;
    
    output.viewDir = normalize(output.pos.xyz - cameraPos);
    
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    output.normal = normalize(mul(input.normal, (float3x3) world));

    output.tangent = normalize(mul(input.tangent, (float3x3) world));
    
    output.binormal = cross(output.normal, output.tangent);
    
    return output;
}
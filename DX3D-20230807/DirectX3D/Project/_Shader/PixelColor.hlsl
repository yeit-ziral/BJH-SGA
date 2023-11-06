#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
};


float4 main(VertexOutput input) : SV_TARGET
{
    float3 L = normalize(lights[0].direction);
    
    float diffuse = dot(input.normal, -L);
    
    return input.color * diffuse;
}